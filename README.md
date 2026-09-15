# ⌚ ESP32-S3 Internet-Connected Smart Clock

> Wi-Fi smart clock using ESP32-S3, 16×2 LCD, DS18B20 temperature sensing, NTP time synchronization, and live weather data.

## 🎯 Overview

The Smart Clock combines local sensor data with internet services in a compact embedded system. It displays synchronized time, indoor temperature, and live outdoor weather information on a 16×2 LCD.

## ✨ Features

- 🕐 NTP-synchronized date and time
- 🌡️ Indoor temperature using DS18B20
- 🌤️ Outdoor weather using OpenWeatherMap
- 🔄 Automatic LCD information rotation
- 🌐 Wi-Fi connectivity
- ⏱️ Periodic weather updates to reduce API requests

## 🏗️ System Architecture

```text
                    Wi-Fi
                      │
                      ▼
ESP32-S3 ───────── OpenWeatherMap
   │
   ├── DS18B20 ─────► Indoor Temperature
   ├── NTP ─────────► Date / Time
   └── 1602A LCD ───► User Interface
```

## 🧰 Hardware

| Component | Purpose |
|---|---|
| ESP32-S3 N16R8 | Main controller + Wi-Fi |
| 1602A LCD | Display |
| DS18B20 module | Indoor temperature |
| 1kΩ resistor | Contrast configuration used in prototype |
| Arduino Uno | 5V supply used for LCD in prototype |
| Breadboard + jumpers | Prototyping |

## 🔌 GPIO Map

| GPIO | Function |
|---|---|
| GPIO 4 | LCD EN |
| GPIO 5 | LCD D6 |
| GPIO 10 | DS18B20 DATA |
| GPIO 16 | LCD RS |
| GPIO 17 | LCD D7 |
| GPIO 18 | LCD D5 |
| GPIO 19 | LCD D4 |

## 🔧 Software Setup

Install **esp32 by Espressif Systems** and select **ESP32S3 Dev Module**. For the N16R8 board, configure 16 MB flash and the appropriate OPI PSRAM setting.

Required libraries:

- OneWire
- DallasTemperature
- ArduinoJson

Configure credentials locally using placeholders such as:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey   = "YOUR_OPENWEATHERMAP_API_KEY";
const char* city     = "YOUR_CITY";
const char* country  = "IN";
```

Never commit real Wi-Fi credentials or API keys.

## 🖥️ Display Concept

```text
14:32:05  27/06
In: 31.2°C

Out: 29.5°C
Clouds
```

The information rotates automatically on the LCD.

## 🐛 Troubleshooting

| Problem | Check |
|---|---|
| No COM port | USB cable, driver, board and port |
| LCD blank | Power, RW, contrast and wiring |
| Sensor not detected | DS18B20 wiring and GPIO 10 |
| Weather unavailable | Wi-Fi, city and API key |
| `ledcSetup` errors | ESP32 Arduino core 3.x API changes |

## 🗺️ Future Improvements

- Dedicated 5V power solution
- 3D-printed enclosure
- Air-quality data
- Improved LCD UI
- Button-based navigation
- Lower-power operation

## 📌 Status

**Working prototype / active development.**

## 👨‍💻 Author

**Mohammed Yusuf Khatai**  
Electronics & Telecommunication Engineering Student, RAIT

## 📄 License

MIT License
