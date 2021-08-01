from typing import Text
from kivy.uix.boxlayout import BoxLayout
from kivymd.uix.list import OneLineAvatarIconListItem
from kivymd.app import MDApp
from kivymd.uix import dialog
from kivymd.uix.screen import MDScreen
from kivymd.uix.snackbar import Snackbar
from datacards import *
from pyModbusTCP.client import ModbusClient
from kivy.clock import Clock
import pickle5 as pickle
from kivymd.uix.button import MDFlatButton
from kivymd.uix.dialog import MDDialog




class MyWidget(MDScreen):
    """
    Construtor
    """
    def __init__(self,**kw):
        super().__init__(**kw)
        self._modclient = ModbusClient()
        self.create_cards()

    def create_cards(self):
        self.ids.modbus_data.clear_widgets()
        a_file = open("tags.pkl", "rb")
        self._tags = pickle.load(a_file)
        a_file.close()
        for tag in self._tags:
            if tag["type"] == "input":
                self.ids.modbus_data.add_widget(CardInputRegister(tag, self._modclient))
            elif tag["type"] == "holding":
                self.ids.modbus_data.add_widget(CardHoldingRegister(tag, self._modclient))
            elif tag["type"] == "coil":
                self.ids.modbus_data.add_widget(CardCoil(tag, self._modclient))

    def call_back(self,dt):
        self.create_cards()

    def card_check(self,dt):
        self.last_tags = len(self._tags)
        a_file = open("tags.pkl", "rb")
        self._tags = pickle.load(a_file)
        a_file.close()
        if self.last_tags != len(self._tags):
            self.create_cards()


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
                self._ev.append(Clock.schedule_interval(self.card_check,0.5))
            except Exception as e:
                print(f"Erro ao conecatar com servidor: ",e.args)
        else:
            self.ids.bt_con.text = "CONECTAR"
            for event in self._ev:
                event.cancel()
            self._modclient.close()
            Snackbar(text="Cliente desconectado",bg_color=(1,0,0,1)).open()

class BasicApp(MDApp):
    def build(self):
        self.theme_cls.primary_palette = "Blue"
        self.theme_cls.primary_hue = "500"
        self.theme_cls.accent_palette = "Blue"
        self.MyWidget = MyWidget()
        return self.MyWidget

    def show_dialog(self):
        close_button = MDFlatButton(text = 'Fechar', on_release=self.close_dialog)
        add_button = MDFlatButton(text='Adicionar',on_release=self.create_new_tag)
        self.content = Content()
        self.dialog = MDDialog(title='Adicionar nova tag',type="custom",content_cls=self.content,buttons=[close_button,add_button])
        self.dialog.open()

    def close_dialog(self,obj):
        self.dialog.dismiss()

    def create_new_tag(self,obj):
        new_tag={}
        new_tag['nome'] = str(self.content.ids.name.text)
        new_tag['description'] = str(self.content.ids.description.text)
        new_tag['address'] = int(self.content.ids.address.text)
        if self.content.ids.input.active:
            new_tag['type']= "input"
        elif self.content.ids.holding.active:
            new_tag['type']= "holding"
        elif self.content.ids.coil.active:
            new_tag['type']= "coil"

        a_file = open("tags.pkl", "rb")
        tags = pickle.load(a_file)
        a_file.close()
        a_file = open("tags.pkl", "wb")
        tags.append(new_tag)
        pickle.dump(tags, a_file)
        a_file.close()
        self.MyWidget.create_cards()
        self.dialog.dismiss()
        print(new_tag)

if __name__ == "__main__":
    BasicApp().run()