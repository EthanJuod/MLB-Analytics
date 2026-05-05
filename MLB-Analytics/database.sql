DROP TABLE IF EXISTS Players;


CREATE TABLE Players (player_id INTEGER PRIMARY KEY,
                    player_name TEXT,
                    team TEXT,
                    player_number TEXT,
                    position TEXT,
                    bat_side TEXT
                    throw_side TEXT);

CREATE TABLE Stats (player_id INTEGER,
                    team TEXT,
                    season INTEGER,
                    games INTEGER,
                    at_bats INTEGER,
                    hits INTEGER,
                    doubles INTEGER,
                    triples INTEGER,
                    home_runs INTEGER,
                    rbi INTEGER,
                    PRIMARY KEY(player_id, season),
                    FOREIGN KEY(player_id) REFERENCES Players(player_id));