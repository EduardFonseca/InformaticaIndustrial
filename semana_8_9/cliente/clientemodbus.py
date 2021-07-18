from pyModbusTCP.client import ModbusClient
from time import sleep

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
                sel = input(f'Deseja realizar uma leitura escrita ou configuracao? (1- Leitura | 2-Escrita | 3-Configuracao | 4-Sair)')
                if sel == "1":
                    tipo = input(f'Qual tipo de dado que deseja ler? (1-Holding Resgister | 2-Coil | 3-Input Register | 4- Discrete Input)')
                    addr = input('digite o endereco da tabela:')
                    n = input('Numero de leituras:')
                    for i in range(0,int(n)):
                        print(f'Leitura {i+1}: {self.lerDado(int(tipo),int(addr))}')
                        sleep(self._scan_time)
                elif sel == "2":
                    tipo = input(f'Qual tipo de dado que deseja escrever? (1-Holding Resgister | 2-Coil)')
                    addr = input('digite o endereco da tabela:')
                    valor = input ('qual valor deseja escrever')
                    self.escreveDado(int(tipo),int(addr), int(valor))
                elif sel == "3":
                    scant = input("digite o tempo de varredura:")
                    self._scan_time = float(scant)
                elif sel == '4':
                    self._client.close()
                    atendimento = False
                else:
                    print("comando invalido")
        except:
            pass

    def lerDado(self, tipo, addr):
        if tipo == 1:
            return self._client.read_holding_registers(addr,1)[0]
        elif tipo == 2:
            return self._client.read_coils(addr,1)[0]
        elif tipo == 3:
            return self._client.read_input_registers(addr,1)[0]
        elif tipo == 4:
            return self._client.read_discrete_inputs(addr,1)[0]

    def escreveDado(self, tipo, addr, valor):
        if tipo == 1:
            return self._client.write_holding_registers(addr,valor)[0]
        elif tipo == 2:
            return self._client.write_coils(addr,valor)[0]