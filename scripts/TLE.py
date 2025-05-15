import requests

def fetch_tle():
    url = "https://celestrak.org/NORAD/elements/gp.php?GROUP=active&FORMAT=tle"
    response = requests.get(url)

    if response.status_code == 200:
        # Save raw response
        with open("tle_data.txt", "w") as file:
            file.write(response.text)

        # Read it back and remove empty lines
        with open("tle_data.txt", "r") as file:
            lines = [line.strip() for line in file if line.strip() != ""]

        # Optionally overwrite with cleaned version
        with open("tle_data.txt", "w") as file:
            for line in lines:
                file.write(line + "\n")
            print("TLE data updated!")
    else:
        print("Failed to fetch TLE data:", response.status_code)
def parse_tle():
    with open("tle_data.txt", "r") as f:
        lines = [line.strip() for line in f if line.strip()]
    with open("parsed_data.txt", "w") as out:
        for i in range(0, len(lines), 3):
            name = lines[i]
            line1 = lines[i + 1]
            line2 = lines[i + 2]

            # Extract necessary components
            inclination_deg = float(line2[8:16])
            raan_deg = float(line2[17:25])
            eccentricity = float(f"0.{line2[26:33]}")
            arg_perigee_deg = float(line2[34:42])
            mean_anomaly_deg = float(line2[43:51])
            mean_motion = float(line2[52:63])
            epoch = float(line1[18:32])
            line = f"{name} {inclination_deg} {raan_deg} {eccentricity} {arg_perigee_deg} {mean_anomaly_deg} {mean_motion} {epoch}\n"
            out.write(line)
def starlink_tle():
    def is_valid(line):
        parts = line.strip().split()
        if len(parts) < 8:
            return False
        try:
            # Try converting all 7 fields after the name to float
            [float(p) for p in parts[1:8]]
            return True
        except ValueError:
            return False

    with open("parsed_data.txt", "r") as f:
        lines = [line for line in f if "STARLINK" in line and is_valid(line)]

    with open("starlink.txt", "w") as out:
        out.writelines(lines)
# fetch_tle()
# parse_tle()
starlink_tle()
