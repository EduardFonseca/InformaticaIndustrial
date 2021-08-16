from pyModbusTCP.server import DataBank, ModbusServer
from time import sleep
import random


class ServidorMODBUS():
    '''
    Classe Servidor modbus
    '''
    def __init__(self,host_ip,port):
        '''
        construtor
        '''
        self._server = ModbusServer(host=host_ip,port=port, no_block=True)
        self._db = DataBank

    def run(self):
        '''
        Execucao do servidor
        '''
        self._server.start()
        print("servidor em execucao")
        while True:
            self._db.set_words(1000,[random.randrange(400,500)]) #temperatura
            self._db.set_words(1001,[random.randrange(100000,1200000)]) #pressao
            self._db.set_words(1002,[random.randrange(20,40)]) #umidade
            self._db.set_words(1003,[random.randrange(40,100)]) #consumo
            sleep(1)