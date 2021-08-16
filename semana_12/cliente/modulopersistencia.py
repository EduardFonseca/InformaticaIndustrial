from pyModbusTCP.client import ModbusClient
from datetime import date, datetime
from time import sleep, strptime
from tabulate import tabulate
from threading import Thread, Lock
from db import Session, Base,engine
from models import DadoCLP
class ModbusPersistencia():
    """
    implementa a funcionalidade de persistencia de dados lidos 
    a partir do protocolo modbus e permite a busca de dados no historico
    """
    def __init__(self, server_ip, server_port, addrs,scan_time=1):
        self._cliente_modbus = ModbusClient(host=server_ip,port=server_port)
        self._scan_time = scan_time
        self._tags_addrs = addrs
        self._session = Session()
        Base.metadata.create_all(engine)
        self._lock = Lock()
        self.guardar_dados = Thread(target=self.guardar_dados)

    def guardar_dados(self):
        try:
            print("Persistencia iniciada \n")
            self._cliente_modbus.open()
            data = {}
            while True:
                data['timestamp'] = datetime.now()
                for tag in self._tags_addrs:
                    data[tag] = self._cliente_modbus.read_holding_registers(self._tags_addrs[tag],1)[0]
                dado = DadoCLP(**data)
                self._lock.acquire()
                self._session.add(dado)
                self._session.commit()
                self._lock.release()
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
                init =  datetime.strptime(init,'%d/%m/%Y %H:%M:%S')
                final =  datetime.strptime(final,'%d/%m/%Y %H:%M:%S')
                self._lock.acquire()
                result = self._session.query(DadoCLP).filter(DadoCLP.timestamp.between(init,final))
                self._lock.release()
                result_fmt_list = [obj.get_attr_printable_list() for obj in result]
                print(tabulate(result_fmt_list,headers=DadoCLP.__table__.columns.keys()))

        except Exception as e:
            print("erro na busca dos dados:", e.args)