import sqlite3
import db


def batting_average(season=None):
    conn = db.get_db()
    cursor = conn.cursor()

    if season:
        row = cursor.execute("SELECT player_name, (hits * 1.0 / NULLIF(at_bats, 0)) AS avg FROM Players AS p JOIN Stats AS s ON p.player_id = s.player_id WHERE season = ? ORDER BY avg DESC;", (season,)).fetchall()
    else:
        row = cursor.execute("SELECT player_name, (SUM(hits) * 1.0 / NULLIF(SUM(at_bats), 0)) AS avg FROM Players AS p JOIN Stats AS s ON p.player_id = s.player_id GROUP BY p.player_id, p.player_name ORDER BY avg DESC;").fetchall()

    conn.close()

    return row

def top_homerun_hitters(season=None):
    conn = db.get_db()
    cursor = conn.cursor()

    if season:
        row = cursor.execute("SELECT player_name, home_runs FROM Players AS p JOIN Stats AS s ON p.player_id = s.player_id WHERE season = ? ORDER BY home_runs DESC LIMIT 10;", (season,)).fetchall()
    else: 
        row = cursor.execute("SELECT player_name, SUM(home_runs) AS home_runs AS total_hrs FROM Players AS p JOIN Stats AS s ON p.player_id = s.player_id GROUP BY p.player_id, p.player_name ORDER BY total_hrs DESC LIMIT 10;").fetchall()

    conn.close()
    return row

def player_comparison(player1, player2, season=None):
    conn = db.get_db()
    cursor = conn.cursor()

    if season:
        row = cursor.execute("SELECT player_name,(hits * 1.0 / NULLIF(at_bats, 0)) AS avg, hits, home_runs, rbi, games FROM Players AS p JOIN Stats AS s ON p.player_id = s.player_id WHERE (player_name = ? OR player_name = ?) AND season = ?;", (player1, player2, season)).fetchall()
    else:
        row = cursor.execute("SELECT player_name, SUM(at_bats) AS at_bats, (SUM(hits) * 1.0 / NULLIF(SUM(at_bats), 0)) AS avg, SUM(hits) AS hits, SUM(home_runs) AS home_runs, SUM(rbi), SUM(games) AS GAMES FROM Players as p JOIN Stats AS s On p.player_id = s.player_id WHERE player_name = ? or player_name = ? GROUP BY p.player_id, p.player_name", (player1, player2)).fetchall()

    conn.close()
    return row
