from typing import Text
from kivymd.app import MDApp
from kivymd.uix.screen import MDScreen
from kivymd.uix.snackbar import Snackbar
from datacards import *
from pyModbusTCP.client import ModbusClient
from kivy.clock import Clock




class MyWidget(MDScreen):
    """
    Construtor
    """
    def __init__(self,tags,**kw):
        super().__init__(**kw)
        self._tags = tags
        self._modclient = ModbusClient()

        for tag in self._tags:
            if tag["type"] == "input":
                self.ids.modbus_data.add_widget(CardInputRegister(tag, self._modclient))
            elif tag["type"] == "holding":
                self.ids.modbus_data.add_widget(CardHoldingRegister(tag, self._modclient))
            elif tag["type"] == "coil":
                self.ids.modbus_data.add_widget(CardCoil(tag, self._modclient))

    def connect(self):
        if self.ids.bt_con.text == "CONECTAR":
            self.ids.bt_con.text = "DESCONECTAR"
            try:
                self._modclient.host = self.ids.hostname.text
                self._modclient.port = int(self.ids.port.text)
                self._modclient.open()
                Snackbar(text="Conexao realizada com sucesso",bg_color=(0,1,0,1)).open()
                self._ev = []
                for card in self.ids.modbus_data.children:
                    if card.tag['type'] == "holding" or card.tag['type'] == 'coil':
                        self._ev.append(Clock.schedule_once(card.update_data))
                    else:
                        self._ev.append(Clock.schedule_interval(card.update_data,1))
            except Exception as e:
                print(f"Erro ao conecatar com servidor: ",e.args)
        else:
            self.ids.bt_con.text = "CONECTAR"
            for event in self._ev:
                event.cancel()
            self._modclient.close()
            Snackbar(text="Cliente desconectado",bg_color=(1,0,0,1)).open()


class BasicApp(MDApp):
    __tags = [
        {'nome': "TempForno",'description':"Temperatura Do Forno",'unit':'C','address':1000,'type': 'input'},
        {'nome': "setpoint",'description':"Temperatura Desejada",'unit':'C','address':2000,'type': 'holding'},
        {'nome': "status",'description':"estado do atuador",'unit':'','address':1000,'type': 'coil'}
    ]
    def build(self):
        self.theme_cls.primary_palette = "Blue"
        self.theme_cls.primary_hue = "500"
        self.theme_cls.accent_palette = "Blue"
        return MyWidget(self.__tags)


if __name__ == "__main__":
    BasicApp().run()