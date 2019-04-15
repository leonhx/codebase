"""
Utilities about database.
"""

from contextlib import contextmanager
import MySQLdb


@contextmanager
def connect(host, user, passwd, database, charset='utf8'):
    """
    Connect database and hold the connection until leaving the block.
    """
    try:
        conn = MySQLdb.connect(host=host, user=user, passwd=passwd,
                               db=database, charset=charset)
        yield conn
        conn.commit()
    finally:
        conn.close()


@contextmanager
def cursor(database_connection):
    """
    Get cursor and hold it until leaving the block.
    """
    try:
        cur = database_connection.cursor()
        yield cur
    finally:
        cur.close()
