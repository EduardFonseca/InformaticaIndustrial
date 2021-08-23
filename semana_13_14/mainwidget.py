from copy import Error

from sqlalchemy import engine
from popups import ModbusPopup, ScanTimePopup, DataGraphPopup, HistGraphPopup
from kivy.uix.boxlayout import BoxLayout
from pyModbusTCP.client import ModbusClient
from kivy.core.window import Window
from threading import Thread,Lock
from time import sleep
from datetime import datetime
import random 
from timeseriesgraph import TimeSeriesGraph
from db import Session,Base, engine
from models import DadoRefinaria
from kivy_garden.graph import LinePlot

class MainWidget(BoxLayout):
    _updateTread = None
    _updateWidget = True
    _tags = {}
    _max_points = 20

    def __init__(self, **kwargs):
        super().__init__()
        self._scan_time = kwargs.get('scan_time')
        self._serverIP = kwargs.get('server_ip')
        self._port = kwargs.get('server_port')
        self._modbusPopup = ModbusPopup(self._serverIP,self._port)
        self._scanPopup = ScanTimePopup(scantime=self._scan_time)
        self._modbusClient = ModbusClient(host=self._serverIP, port=self._port)
        self._meas={}
        self._meas['timestamp'] = None
        self._meas['values'] = {}
        self._lock=Lock()

        for key,value in kwargs.get('modbus_addr').items():
            if key == 'fornalha':
                plot_color = (1,0,0,1)
            else:
                plot_color = (random.random(),random.random(),random.random(),1)
            self._tags[key] = {'addr': value, 'color':plot_color}
        self._graph = DataGraphPopup(self._max_points,self._tags['fornalha']['color'])
        self._hgraph = HistGraphPopup(tags=self._tags)
        self._session = Session()
        Base.metadata.create_all(engine)


    def startDataRead(self,ip,port):
        """
        Metodo utilixado para a configuracao do IP e porta do servidor MODBUS e
        inicializar uma thread para a leitura dos dados e atualizacao da interface
        """
        self._serverIP = ip
        self._port = port
        self._modbusClient.host = self._serverIP
        self._modbusClient.port = self._port
        try:
            Window.set_system_cursor('wait')
            self._modbusClient.open()
            Window.set_system_cursor('arrow')
            if self._modbusClient.is_open():
                self._updateTread = Thread(target=self.updater)
                self._updateTread.start()
                self.ids.img_con.source = 'imgs/conectado.png'
                self._modbusPopup.dismiss()
            else:
                self._modbusPopup.setInfo("Falha na conexao com o servidor")
        except Exception as e:
            print("Erro: ",e.args)

    def updater(self):
        """
        Invoca leitura de dados, atualizacao da interface e insercao de dados na DB
        """
        try:
            while self._updateWidget:
                self.readData()
                self.updateGUI()
                self._lock.acquire()
                dado = DadoRefinaria(**self._meas['values'])
                dado.timestamp = self._meas['timestamp']
                self._session.add(dado)
                self._session.commit()
                self._lock.release()

                sleep(self._scan_time/1000)
        except Exception as e:
            self._modbusClient.close()
            print("Erro:",e.args)

    def readData(self):
        """
        Metodo para a leitura dos dados por meio do protocolo MODBUS
        """
        self._meas['timestamp'] = datetime.now()
        for key,value in self._tags.items():
            self._meas['values'][key] = self._modbusClient.read_holding_registers(value['addr'],1)[0]

    def updateGUI(self):
        #atualizacao dos labels das temperaturas
        for key,value in self._tags.items():
            self.ids[key].text = str(self._meas['values'][key]) + ' C'


        #atualizar o nivel do termometro
        self.ids.lb_temp.size=(self.ids.lb_temp.size[0],self._meas['values']['fornalha']/450*self.ids.termometro.size[1])

        #atualizacao grafico:
        self._graph.ids.graph.updateGraph((self._meas['timestamp'],self._meas['values']['fornalha']),0)

    def stopRefresh(self):
        self._updateWidget=False
    
    def getDataDB(self):
        try:
            init_t = self.parseDTString(self._hgraph.ids.txt_init_time.text)
            final_t = self.parseDTString(self._hgraph.ids.txt_final_time.text)
            cols = []
            for sensor in self._hgraph.ids.sensores.children:
                if sensor.ids.checkbox.active:
                    cols.append(sensor.id)
            if init_t is None or final_t is None or len(cols)==0:
                return
            cols.append('timestamp')
            self._lock.acquire()
            dados = self._session.query(DadoRefinaria).filter(DadoRefinaria.timestamp.between(init_t,final_t))
            self._lock.release()
            if dados is None:
                return
            self._hgraph.ids.graph.clearPlots()
            result = [obj.get_attr_printable_list() for obj in dados]
            d=0
            for key,value in result[0].items():
                aux = []
                if key in cols:
                    for i in range(len(result)):
                        if key in cols:
                            if key == 'timestamp':
                                continue
                            p = LinePlot(line_width=1.5, color= self._tags[key]['color'])
                            aux.append((i,result[i][key]))
                            p.points = aux
                            self._hgraph.ids.graph.add_plot(p)
                d+=1
            self._hgraph.ids.graph.xmax = len(result[d])
            timestamp = []
            for j in range(d):
                timestamp.append(datetime.strptime(result[d]['timestamp'],"%d/%m/%Y %H:%M:%S.%f"))
            self._hgraph.ids.graph.update_x_labels(timestamp)

        except Exception as e:
            print("Erro:",e.args)

    def parseDTString(self, datetime_str):
        try:
            d = datetime.strptime(datetime_str, '%d/%m/%Y %H:%M:%S')
            return d
        except Exception as e:
            print("Erro: ", e.args)
