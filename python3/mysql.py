import pymysql

'''
mysql class
'''


class MySql(object):
    def __init__(self, host, port, user, passwd, db):
        self.__host = host
        self.__port = port
        self.__user = user
        self.__passwd = passwd
        self.__db = db
        self.__charset = 'utf8'
        try:
            self.__conn = pymysql.connect(host=self.__host, port=self.__port, user=self.__user, passwd=self.__passwd,
                                          db=self.__db, charset=self.__charset)
        except Exception as e:
            print("mysql连接出错 ", e)

    def __getcursor(self):
        return self.__conn.cursor(cursor=pymysql.cursors.DictCursor)

    def query(self, sql):
        cursor = self.__getcursor()
        try:
            index = cursor.execute(sql)
            self.__conn.commit()
            return index
        except Exception as e:
            print(e)
        finally:
            cursor.close()

    def queryall(self, sql, args=None):
        cursor = self.__getcursor()
        try:
            cursor.execute(sql, args)
            return cursor.fetchall()
        except Exception as e:
            print("执行sql出错 ", e, "sql为: " + sql)
        finally:
            cursor.close()
