import requests

def fetch_tle():
    url = "https://celestrak.org/NORAD/elements/gp.php?GROUP=active&FORMAT=tle"
    response = requests.get(url)

    if response.status_code == 200:
        with open("tle_data.txt", "w") as file:
            file.write(response.text)
        print("TLE data updated!")
    else:
        print("Failed to fetch TLE data:", response.status_code)

fetch_tle()
