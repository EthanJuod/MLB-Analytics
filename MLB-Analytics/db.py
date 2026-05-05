import sqlite3

db_name = "database.db"
sql_file = "database.sql"
db_flag = False

def create_db():
	conn = sqlite3.connect(db_name)
    
	with open(sql_file, 'r') as sql_startup:
		init_db = sql_startup.read()
	cursor = conn.cursor()
	cursor.executescript(init_db)
	conn.commit()
	conn.close()
	global db_flag
	db_flag = True
	return conn

def get_db():
	if not db_flag:
		create_db()
	conn = sqlite3.connect(db_name)
	conn.execute("PRAGMA foreign_keys = ON;")
	return conn