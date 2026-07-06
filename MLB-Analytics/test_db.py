import sqlite3

conn = sqlite3.connect("database.db")
cursor = conn.cursor()

print("Players:", cursor.execute("SELECT COUNT(*) FROM Players").fetchone())
print("Stats:", cursor.execute("SELECT COUNT(*) FROM Stats").fetchone())

rows = cursor.execute(
    "SELECT * FROM Players LIMIT 10"
).fetchall()

for row in rows:
    print(row)

rows = cursor.execute(
    "SELECT * FROM Stats LIMIT 10"
).fetchall()

for row in rows:
    print(row)