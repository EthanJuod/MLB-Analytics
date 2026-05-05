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
        stat = row["stat"]

        #Getting player stats
        games = stat["gamesPlayed"]
        atBats = stat["atBats"]
        hits = stat["hits"]
        doubles = stat["doubles"]
        triples = stat["triples"]
        homeRuns = stat["homeRuns"]
        rbi = stat["rbi"]
        

        #Getting player data
        player_id = player["id"]
        player_name = player["fullName"]
        team = row["team"]["name"]
        row = cursor.execute("SELECT * FROM Players WHERE player_id = ?;", (player_id,)).fetchone()
        if row is None:
            cursor.execute("INSERT INTO Players (player_id, team) VALUES (?,?)", (player_id,team))
        else:
                cursor.execute("UPDATE Players SET team = ? WHERE player_id = ?;",(team, player_id))

        cursor.execute("INSERT INTO Stats (player_id, team, season, games, at_bats, hits, doubles, triples, home_runs, rbi) VALUES (?,?,?,?,?,?,?,?,?,?)",
                       (player_id, team, year, games, atBats, hits, doubles, triples, homeRuns, rbi))
    

rows = cursor.execute("SELECT player_id FROM Players;").fetchall()
for (player_id,) in rows:

    person_data = requests.get(PERSON_URL + str(player_id)).json()
    person = person_data["people"][0]
    player_name = person["fullName"]
    active = person["active"]
    number = person["primaryNumber"]
    batSide = person["batSide"]["code"]
    pitchHand = person["pitchHand"]["code"]
    position = person["primaryPosition"]["abbreviation"]

    if not active:
        player_team = "N/A"

    if not active:
        cursor.execute("UPDATE Players SET player_name = ?, team = ?, player_number = ?, position = ?, bat_side = ?, throw_side = ? WHERE player_id = ?;",
                       (player_name, player_team, number, position,batSide, pitchHand, player_id))
    else:
        cursor.execute("UPDATE Players SET player_name = ?, player_number = ?, position = ?, bat_side = ?, throw_side = ? WHERE player_id = ?;",
                       (player_name, number, position,batSide, pitchHand, player_id))