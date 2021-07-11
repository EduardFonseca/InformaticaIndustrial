import socket

class Cliente():
    """
    Classe cliente
    """
    def __init__(self,ip,port):
        """costrutor da classe cliente

        Args:
            ip : ip do servidor
            port : [porta do servidor
        """
        self.__server_ip = ip
        self.__port = port
        self.__tcp = socket.socket (socket.AF_INET,socket.SOCK_STREAM)

    def start(self):
        """
        Metodo de inicializacao do cliente
        """
        endpoint = (self.__server_ip,self.__port)
        try:
            self.__tcp.connect(endpoint)
            print("conexao realizada com sucesso!")
            self.__method()
        except Exception as e:
            print("Erro de conecacao com o servidor ",e.args)

    def __method(self):
        """
        metodod que implementa o requerimento do cliente e a IHN
        """
        try:
            msg=''
            while msg != 'x':
                msg = input("\n\nOperacoes disponiveis:\n1 -> Cotacao atual;\n2 -> Historico dos precos dos ultimos 7 dias;\n3 -> Valor de mercado;\n4 -> Sumario da empresa;\nx ->Sair.\nDigite a operacao desejada: ")
                if msg == '':
                    continue
                elif msg == 'x':
                    break
                self.__tcp.send(bytes(msg,'ascii'))
                resp = self.__tcp.recv(1024)
                if resp.decode('ascii')!="Operacao invalida":
                    action = input(resp.decode('ascii'))
                    self.__tcp.send(bytes(action,'ascii'))
                    resp = self.__tcp.recv(1024)
                print("\n"+resp.decode('ascii'))

            self.__tcp.close()
        except Exception as e:
            print("Erro ao realizar comunicacao com o servidor ", e.args)

