import codecs
import sys
from second import *

conn = mysql.MySql(host='127.0.0.1', port=3306, user='root', passwd='root', db='test')

# index=conn.query("insert into user(id,name) values(101, '香香2')")
# print("index=", index)
id = 100
name = '香香'
name.encode('utf8')
sql = "select * from user where id=%s and name=%s "
res = conn.queryall(sql, (id, name))
for ls in res:
    print(ls['id'])

with codecs.open("test.txt", 'r', encoding='utf8') as f:
    for line in f:
        print(line, end="")

print(sys.byteorder)
