print ("""CREATE DATABASE db;
USE db;
CREATE TABLE a (col1 INT(100), col2 FLOAT, col3 VARCHAR(10));
CREATE TABLE b (col1 INT(100));""")

sa = "INSERT INTO a VALUES (%i, %s, '%s');"
sb = "INSERT INTO b VALUES (%i);"
for i in range(1000):
    print(sa % (i, '2.0', 'shit'))
    # print(sb % (i))



print("""SELECT * FROM a, b WHERE a.col1=b.col1;
DROP DATABASE db;""")
