import sqlite3
import requests
import db


STATS_URL = "https://statsapi.mlb.com/api/v1/stats"
PERSON_URL = "https://statsapi.mlb.com/api/v1/people/"

conn = db.get_db()
cursor = conn.cursor()

for year in range(2000, 2026):
    params = {"stats":"season",
              "group":"hitting",
              "season":year,
              "limit":5000}
    
    stats_data = requests.get(STATS_URL, params=params).json()

    splits = stats_data["stats"][0]["splits"]

    for row in splits:
        player = row["player"]
        stats = row["stats"]
        position = row["position"]

        player_id = player["id"]
        player_name = player["fullName"]
        position = position["abbreviation"]
        team = row["team"]["name"]

        row = cursor.execute("SELECT * FROM Players WHERE player_id = ?", (player_id,)).fetchone()

        if row is None:
            person_data = requests.get(PERSON_URL + player_id)
            person = person_data["people"][0]

            number = person["primaryNumber"]
            active = person["active"]
            batSide = person["batSide"]["code"]
            pitchHand = person["pitchHand"]["code"]
    