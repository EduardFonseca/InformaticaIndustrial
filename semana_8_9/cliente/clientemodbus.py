from pyModbusTCP.client import ModbusClient
from time import sleep
from pymodbus.constants import Endian
from pymodbus.payload import BinaryPayloadDecoder
from pymodbus.payload import BinaryPayloadBuilder
from collections import OrderedDict

class ClientModbus():
    '''
    Classe Cliente Modbus
    '''
    def __init__(self, server_ip, port, scan_time=1):
        self._client = ModbusClient(host=server_ip,port= port)
        self._scan_time = scan_time

    def atendimento(self):
        self._client.open()
        try:
            atendimento = True
            while atendimento:
                sel = input(f'Deseja realizar uma leitura escrita ou configuracao? (1- Leitura | 2-Escrita | 3-Configuracao | 4-Sair): ')
                if sel == "1":
                    tipo = input(f'Qual tipo de dado que deseja ler? (1-Holding Resgister | 2-Coil | 3-Input Register | 4- Discrete Input): ')
                    addr = input('digite o endereco da tabela: ')
                    n = input('Numero de leituras: ')
                    cont = 0
                    for i in range(0,int(n)):
                        print(f'Leitura {i+1}: {self.lerDado(int(tipo),int(addr),cont)}')
                        cont+=1
                        sleep(self._scan_time)

                elif sel == "2":
                    tipo = input(f'Qual tipo de dado que deseja escrever? (1-Holding Resgister | 2-Coil): ')
                    addr = input('digite o endereco da tabela: ')
                    self.escreveDado(int(tipo),int(addr))
                elif sel == "3":
                    scant = input("digite o tempo de varredura: ")
                    self._scan_time = float(scant)
                elif sel == '4':
                    self._client.close()
                    atendimento = False
                else:
                    print("comando invalido")
        except Exception as e:
            print("Erro:",e.args)


    def lerDado(self, tipo, addr,cont):
        if tipo == 1:
            if cont==0:
                self.formato = input("Qual o formato do dado?(1-int | 2-string | 3-Float): ")
            if self.formato == "1":
                return self._client.read_holding_registers(addr,1)[0]
            elif self.formato == "2":
                if cont ==0:
                    self.tam = input("qual o tamanho da string?")
                result = self._client.read_holding_registers(addr,int(self.tam))
                return BinaryPayloadDecoder.fromRegisters(result, wordorder=Endian.Big).decode_string(int(self.tam))
            elif self.formato == "3":
                result = self._client.read_holding_registers(addr,8)
                return BinaryPayloadDecoder.fromRegisters(result, wordorder=Endian.Big).decode_32bit_float()
        elif tipo == 2:
            return self._client.read_coils(addr,1)[0]
        elif tipo == 3:
            return self._client.read_input_registers(addr,1)[0]
        elif tipo == 4:
            return self._client.read_discrete_inputs(addr,1)[0]

    def escreveDado(self, tipo, addr):
        if tipo == 1:
            formato = input ('qual tipo do valor?(1-int | 2-string | 3-Float): ')
            if formato == '1':
                valor = input("qual valor deseja escrever?")
                return self._client.write_single_register(addr,int(valor))
            elif formato == '2':
                builder = BinaryPayloadBuilder()
                valor = input("qual a string desejada?")
                builder.add_string(valor)
                payload = builder.to_registers()
                return self._client.write_multiple_registers(addr,payload)
            elif formato == '3':
                builder = BinaryPayloadBuilder()
                valor = float(input("qual o valor desejada?"))
                builder.add_32bit_float(valor)
                payload = builder.to_registers()
                return self._client.write_multiple_registers(addr,payload)
        elif tipo == 2:
            valor = input("qual valor deseja escrever?")
            return self._client.write_single_coil(addr,valor)[0]

