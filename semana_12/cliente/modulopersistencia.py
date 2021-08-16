from pyModbusTCP.client import ModbusClient
from dbhandler import DBHandler
from datetime import date, datetime
from time import sleep, strptime
from tabulate import tabulate
from threading import Thread

class ModbusPersistencia():
    """
    implementa a funcionalidade de persistencia de dados lidos 
    a partir do protocolo modbus e permite a busca de dados no historico
    """
    def __init__(self, server_ip, server_port, addrs,scan_time=1):
        self._cliente_modbus = ModbusClient(host=server_ip,port=server_port)
        self._scan_time = scan_time
        self._tags_addrs = addrs
        self._dbhandler = DBHandler('cliente\data\data.db',self._tags_addrs.keys(),'modbusData')
        self.guardar_dados = Thread(target=self.guardar_dados)

    def guardar_dados(self):
        try:
            print("Persistencia iniciada \n")
            self._cliente_modbus.open()
            data = {}
            while True:
                data['timestamp'] = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
                for tag in self._tags_addrs:
                    data[tag] = self._cliente_modbus.read_holding_registers(self._tags_addrs[tag],1)[0]
                self._dbhandler.inset_data(data)
                sleep(self._scan_time)

        except Exception as e:
            print("Erro na persistencia dos dados: ", e.args)


    def acesso_dados_historico(self):
        """
        metodo que permite ao usuario acessao dados historico
        """
        try:
            print("Bem vindo ao sistema de busca de dados historicos")
            while True:
                init = input("Digite o horario inicial para a busca (DD/MM/AAAA HH:MM:SS) :")
                final = input("Digite o horario final para a busca (DD/MM/AA HH:MM:SS) :")
                init =  datetime.strptime(init,'%d/%m/%Y %H:%M:%S').strftime("%Y-%m-%d %H:%M:%S")
                final =  datetime.strptime(final,'%d/%m/%Y %H:%M:%S').strftime("%Y-%m-%d %H:%M:%S")
                result = self._dbhandler.select_data(self._tags_addrs.keys(),init,final)
                print(tabulate(result['data'],headers=result['cols']))

        except Exception as e:
            print("erro na busca dos dados:", e.args)