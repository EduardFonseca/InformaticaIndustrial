from sqlalchemy.engine import interfaces
from db import Base
from sqlalchemy import Column , Integer,DateTime

class DadoRefinaria(Base):
    __tablename__ = 'dadosRefinaria'
    id = Column(Integer, primary_key=True,autoincrement=True)
    timestamp = Column(DateTime)
    fornalha = Column(Integer)
    gas_ref = Column(Integer)
    gasolina = Column(Integer)
    nafta = Column(Integer)
    querosene = Column(Integer)
    diesel = Column(Integer)
    oleo_lub = Column(Integer)
    oleo_comb = Column(Integer)
    residuos = Column(Integer)

    def get_attr_printable_list(self):
        return{
            'timestamp':self.timestamp.strftime('%d/%m/%Y %H:%M:%S.%f'),
            'fornalha': self.fornalha,
            'gas_ref': self.gas_ref,
            'gasolina': self.gasolina,
            'nafta': self.nafta,
            'querosene': self.querosene,
            'diesel': self.diesel,
            'oleo_lub': self.oleo_lub,
            'oleo_comb': self.oleo_comb,
            'residuos':self.residuos
        }