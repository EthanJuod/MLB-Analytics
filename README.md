MLB Hitter Statistics Database
Overview

This is an in-progress personal project focused on collecting, storing, and analyzing historical Major League Baseball hitter statistics.

The project uses the MLB Stats API to collect player and season data from 2000–2026 and stores the collected information in a custom SQLite database. The goal is to create a database that can be queried and used to perform statistical analysis on MLB hitters across multiple seasons.

Project Status

In Progress

The database and data collection functionality are currently being developed. Additional statistical queries, analysis features, and improvements to the application are planned.

Features
Collects MLB hitter data using the MLB Stats API
Covers historical seasons from 2000–2026
Stores collected data in a custom SQLite database
Organizes player and statistical information using relational database structures
Provides SQL queries for retrieving and analyzing player statistics
Python application for interacting with the database and API
Statistical analysis functionality currently under development
Technologies
Python
SQLite
SQL
MLB Stats API
Git/GitHub
Data Collection

The project uses the MLB Stats API as the source for historical baseball data.

The Python application communicates with the API, retrieves player and season statistics, and processes the returned data before storing it in the project's SQLite database.

The database is intended to provide a centralized dataset that can be queried without repeatedly requesting the same information from the API.

Database

A relational SQLite database is used to store the collected MLB data.

The database currently focuses on hitter statistics and player information, with data organized by player and season.

Example statistics include:

Games played
At-bats
Hits
Home runs
Runs batted in
Batting average

The database structure and queries are being expanded as development continues.

Analysis

The project is being developed to allow statistical comparisons between MLB hitters across different seasons.

Planned and current functionality includes queries for:

Player statistics
Season statistics
Batting averages
Historical player performance
Comparisons between players and seasons
Aggregate statistics across multiple seasons
Project Structure
MLB-Analytics/
│
├── bd.py
├── database.sql
├── queries.py
├── database.db
└── README.md
Goals

The long-term goal of the project is to create a flexible MLB statistics database and analysis tool that can be used to explore historical hitter performance.

Future development may include:

Additional player statistics
More advanced statistical queries
Improved data visualization
Player-to-player comparisons
Season-to-season analysis
Additional MLB data beyond hitting statistics

