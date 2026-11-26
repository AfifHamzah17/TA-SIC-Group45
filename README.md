# TA-SIC Group 45 — IoT Weather Station

Final-project prototype that streams temperature and humidity readings from physical
sensors to a web dashboard.

**Arduino (C++) · Flask · Python · HTML**

---

## Contents

| File | Purpose |
|---|---|
| `tech_assignment.ino` | Arduino sketch reading the sensors |
| `Data.py` | Flask server — receives readings and serves the dashboard |
| `templates/index.html` | Live dashboard |
| `Preview.png` | Screenshot of the running dashboard |
| `RangkaianFisik.jpg` | Photo of the hardware wiring |

---

## How it works

1. The Arduino sketch polls the sensors (temperature + humidity) and sends readings over
   HTTP to the Flask server.
2. `Data.py` keeps the latest reading in memory (`sensor_data`) and exposes:
   - `GET /` — dashboard page
   - a JSON endpoint the page polls for fresh values
3. The HTML page updates the displayed values without a reload.

---

## Running

### Server

```bash
pip install flask
python Data.py
```

### Hardware

Open `tech_assignment.ino` in the Arduino IDE, set your Wi-Fi credentials and the
server's IP address, then upload to the board.

> Readings are stored in memory only — restarting the server clears them.
