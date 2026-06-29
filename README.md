# ESP32-S3 Smart Clock 🕐🌤️

A smart clock built with the ESP32-S3 N16R8 DevBoard that displays real-time clock, indoor temperature (via DS18B20 sensor), outdoor temperature and live weather conditions (via OpenWeatherMap API) on a 1602A LCD display.

---

## Features

- Real-time clock synced via NTP (IST timezone)
- Indoor room temperature via DS18B20 sensor
- Outdoor temperature and weather via OpenWeatherMap API
- Auto-rotating display every 4 seconds
- Weather refreshes every 10 minutes

---

## Hardware Required

| Component | Details |
|---|---|
| ESP32-S3 DevBoard | Otronic N16R8 (16MB Flash, 8MB PSRAM) |
| LCD Display | 1602A 16x2 Character LCD |
| Temperature Sensor | DS18B20 module (from 37-in-1 kit) |
| Resistor | 1kΩ (for LCD contrast on V0) |
| Arduino Uno | Used only as 5V power supply for LCD |
| Jumper wires | |
| Breadboard | |

---

## Wiring

### Power Rails
| Rail | Source |
|---|---|
| 3.3V rail | ESP32-S3 3.3V pin |
| 5V rail | Arduino Uno 5V pin |
| GND rail | ESP32-S3 GND + Arduino Uno GND (common) |

### LCD 1602A
| LCD Pin | Signal | Connect To |
|---|---|---|
| 1 (VSS) | GND | GND rail |
| 2 (VDD) | VCC | 5V rail |
| 3 (V0) | Contrast | 5V rail via 1kΩ resistor |
| 4 (RS) | Register Select | GPIO 16 |
| 5 (RW) | Read/Write | GND rail |
| 6 (EN) | Enable | GPIO 4 |
| 7–10 | D0–D3 | Not connected |
| 11 (D4) | Data 4 | GPIO 19 |
| 12 (D5) | Data 5 | GPIO 18 |
| 13 (D6) | Data 6 | GPIO 5 |
| 14 (D7) | Data 7 | GPIO 17 |
| 15 (A) | Backlight + | 5V rail |
| 16 (K) | Backlight − | GND rail |

### DS18B20 Module (flat face forward)
| Module Pin | Connect To |
|---|---|
| LEFT (GND) | GND rail |
| MIDDLE (VCC) | 3.3V rail |
| RIGHT (DATA) | GPIO 10 |

> No external pull-up resistor needed — the module has one built in.

### GPIO Summary
| GPIO | Function |
|---|---|
| GPIO 2 | Contrast PWM (LEDC, software only) |
| GPIO 4 | LCD EN |
| GPIO 5 | LCD D6 |
| GPIO 10 | DS18B20 DATA |
| GPIO 16 | LCD RS |
| GPIO 17 | LCD D7 |
| GPIO 18 | LCD D5 |
| GPIO 19 | LCD D4 |

---

## Software Setup

### Step 1 — Install ESP32 board support
- Open Arduino IDE → File → Preferences
- Add to "Additional boards manager URLs":
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
- Go to Tools → Board → Boards Manager
- Search **esp32** → install **esp32 by Espressif Systems**
- Select: Tools → Board → **ESP32S3 Dev Module**
- Set Flash: **16MB**, PSRAM: **OPI PSRAM**

### Step 2 — Install libraries
Go to Sketch → Library Manager and install:
- **OneWire** by Paul Stoffregen
- **DallasTemperature** by Miles Burton
- **ArduinoJson** by Benoit Blanchon
- LiquidCrystal, WiFi, HTTPClient are built-in

### Step 3 — Get OpenWeatherMap API key
- Sign up free at https://openweathermap.org
- Go to your profile → API Keys
- Copy your key
- Free tier: 60 calls/minute (this project uses 1 call per 10 minutes)

### Step 4 — Configure the code
Open `src/smart_clock.ino` and fill in:
```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey   = "YOUR_OPENWEATHERMAP_API_KEY";
const char* city     = "Thane";       // change to your city
const char* country  = "IN";
```

### Step 5 — Upload
- Connect ESP32-S3 via UART port (CH343P side)
- If no COM port appears, install CH343P driver:
  https://www.wch-ic.com/downloads/CH343SER_EXE.html
- Use a USB 2.0 port (black port) if AMD USB 3.0 causes issues
- Upload and open Serial Monitor at **115200 baud**

---

## Display Layout

```
Line 1:  14:32:05 27/06       ← time and date (always)
Line 2:  In:  31.2°C          ← rotates every 4 seconds
         Out: 29.5°C
         Clouds
```

---

## Troubleshooting

| Problem | Fix |
|---|---|
| No COM port | Install CH343P driver, use USB 2.0 port |
| LCD blank | Check V0 wiring, adjust contrast resistor |
| LCD faint | LCD needs 5V — use Arduino Uno as 5V supply |
| Sensor not found | Check DS18B20 pinout (LEFT=GND, MID=VCC, RIGHT=DATA) |
| ledcSetup error | You have ESP32 core 3.x — use ledcAttach() not ledcSetup() |
| Weather not fetching | Check API key and WiFi credentials |

---

## Built By

Mohammed Yusuf — Electronics & Telecommunications Engineering Student  
Ramrao Adik Institute of Technology (RAIT), D.Y. Patil Deemed University, Navi Mumbai

---

## License

MIT License — free to use, modify and share.
