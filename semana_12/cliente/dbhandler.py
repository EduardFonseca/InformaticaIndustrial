from os import execlp
import sqlite3
from sqlite3.dbapi2 import Timestamp, sqlite_version
from threading import Lock

class DBHandler():
    def __init__(self, dbpath, tags_names,table_name='dataTable'):
        self._con = sqlite3.connect(dbpath,check_same_thread=False)
        self._cursor = self._con.cursor()
        self._lock = Lock()
        self._table_name = table_name
        self.create_table(tags_names)


    def create_table(self,tags_names):
        try:
            sql_real_cols = ' REAL,'.join(tags_names)
            sql_str = f"""
            CREATE TABLE IF NOT EXISTS {self._table_name} (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT NOT NULL, {sql_real_cols} REAL);
            """
            self._lock.acquire()
            self._cursor.execute(sql_str)
            self._con.commit()
            self._lock.release()
        except Exception as e:
            print("error na criacao da tabela:", e.args)

    def inset_data(self,data):
        """metodo para insercao de dados

        Args:
            data ([type]): dicionario contendo os dados a serem inseridos com as chaves
        """
        try:
            data['timestamp'] = f"'{data['timestamp']}'"
            str_cols = ','.join(data.keys())
            str_values = ','.join([str(data[tag]) for tag in data.keys()])
            sql_str = f'INSERT INTO {self._table_name} ({str_cols}) VALUES ({str_values});'
            self._lock.acquire()
            self._cursor.execute(sql_str)
            self._con.commit()
            self._lock.release()
        except Exception as e:
            print("erro na insercao de dados na database", e.args)

    def select_data(self,tags, init_t, final_t):
        """metodo de busca de dados na DB entre 2 horarios especificados

        Args:
            tags ([type]): [description]
            init_t ([type]): [description]
            final_t ([type]): [description]
        """
        cols = list(tags)
        cols.insert(0,'timestamp')
        try:
            sql_str = f"SELECT {','.join(cols)} FROM {self._table_name} WHERE timestamp BETWEEN '{init_t}' AND '{final_t}'"
            self._lock.acquire()
            self._cursor.execute(sql_str)
            self._con.commit()
            self._lock.release()
            selected_data = {'cols': cols, 'data': []}
            for reg in self._cursor.fetchall():
                selected_data['data'].append(reg)
            return selected_data

        except Exception as e:
            print("Erro na busca dos dados", e.args)


