from os import X_OK
import socket
import threading
from yahooquery import Ticker

class Servidor():
    """
    Classe servidor - Claculadora remota
    """
    def __init__(self, host , port):
        """
        Inicializacao do servidor
        """
        self._host=host
        self._port=port
        self._tcp = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    def start(self):
        """
        Inicia a execucao do servico
        """
        endpoint = (self._host,self._port)
        try:
            self._tcp.bind(endpoint)
            self._tcp.listen(1)
            print("servidor iniciado em ", self._host, ":", self._port)
            while True:
                con, client = self._tcp.accept() #con = socket do cliente
                self._service(con,client)
        except Exception as e:
            print("Erro ao iniciar servidor ", e.args)

    def _service(self,con,client):
        """
        Metodo q implementa o servico

        Args:
            con : objeto socket utilizado para enviar e receber os dados
            cliente : endereco da porta do cliente
        """
        print("atendendo cliente ", client)
        while True:
            try:
                msg = con.recv(1024)
                op = str(msg.decode('ascii'))
                if op == "1":
                    tickers =  self.get_action(con)
                    cotacao = Ticker(tickers)
                    resp = f"cotacao atual: {cotacao.quotes[tickers.upper()]['ask']}"
                elif op == "2":
                    history = Ticker(self.get_action(con))
                    resp = str(history.history(period="7d"))
                elif op == "3":
                    tickers =  self.get_action(con)
                    marketCap = Ticker(tickers)
                    resp = f"Valor de mercado: {marketCap.quotes[tickers.upper()]['marketCap']}"
                elif op == "4":
                    tickers = self.get_action(con)
                    summury = Ticker(tickers)
                    aux = summury.asset_profile[tickers]['longBusinessSummary']
                    resp = ""
                    for i in range(len(aux)):
                        resp+=aux[i]
                        if aux[i] == "." and aux[i-3]!="I" and len(resp) > 50:
                            break
                else:
                    resp= "Operacao invalida"
                con.send(bytes(resp,'ascii'))
                print(client, "-> requisicao atendida")

            except OSError as e:#OSError serve para verificar problemas de coneccao
                print("erro na conecacao", client, ":", e.args)
                return
            except Exception as e:
                print("Erro nos dados recebidos do cliente", client, ":", e.args)
                con.send(bytes("Erro",'ascii'))

    def get_action(self,con):
        msg = "qual acao deseja consultar:"
        con.send(bytes(msg,'ascii'))
        action = con.recv(1024)
        action_s = str(action.decode('ascii'))
        return action_s

class ServidorMT(Servidor):
    """
    Servidor com multithreading

    Args:
        Servidor :
    """

    def __init__(self, host, port):
        """
        construtor da Classe ServidorMT
        """
        super().__init__(host,port)
        self.__threadPool = {} #criacao de um thread para cada cliente novo conectado

    def start(self):
        """
        Inicia a execucao do servico
        """
        endpoint = (self._host,self._port)
        try:
            self._tcp.bind(endpoint)
            self._tcp.listen(1)
            print("servidor iniciado em ", self._host, ":", self._port)
            while True:
                con, client = self._tcp.accept() #con = socket do cliente
                self.__threadPool[client] = threading.Thread(target=self._service, args=(con,client)) #cria novo nucleo q requisita a utilisacao de um novo servico para o cliente novo conectado
                self.__threadPool[client].start()
        except Exception as e:
            print("Erro ao iniciar servidor ", e.args)