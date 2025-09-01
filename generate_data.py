import csv
import random
from datetime import datetime, timedelta
import os

# Ensure data directory exists
os.makedirs("data", exist_ok=True)

# Remove old CSV files if they exist
for filename in ["data/aircraft.csv", "data/flights.csv"]:
    if os.path.exists(filename):
        os.remove(filename)

# Airports
airports = ["ATH", "LHR", "CDG", "FRA", "JFK", "MAD", "DXB", "SIN", "NRT", "SYD"]

# Generate Aircraft CSV
with open("data/aircraft.csv", "w", newline="") as f:
    writer = csv.writer(f)
    for i in range(1, 11):  # 10 aircraft
        model = random.choice(["Boeing737", "AirbusA320", "Boeing777", "AirbusA350"])
        capacity = random.randint(150, 300)
        writer.writerow([i, model, capacity])

# Generate Flights CSV
start_time = datetime(2025, 1, 1, 6, 0)  # start at 06:00
with open("data/flights.csv", "w", newline="") as f:
    writer = csv.writer(f)
    for i in range(1, 101):  # 100 flights
        origin = random.choice(airports)
        dest = random.choice([a for a in airports if a != origin])
        dep_time = (start_time + timedelta(minutes=random.randint(0, 720))).strftime("%H:%M")
        writer.writerow([i, origin, dest, dep_time])

print("Generated fresh aircraft.csv and flights.csv in the data/ folder.")
