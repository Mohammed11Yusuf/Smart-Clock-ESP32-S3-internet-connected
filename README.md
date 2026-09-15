# ⌚ ESP32-S3 Internet-Connected Smart Clock

> A Wi-Fi-enabled desk clock built with ESP32-S3, a 16×2 LCD, DS18B20 temperature sensing, NTP time synchronization, and live weather data.

## 📸 Project

The Smart Clock combines a local indoor temperature sensor with internet-based time and weather information in a compact embedded system.

## ✨ Features

- 🕐 Real-time clock synchronized using NTP
- 🌡️ Indoor temperature using DS18B20
- 🌤️ Outdoor temperature and weather conditions using OpenWeatherMap
- 🔄 Automatic information rotation on the LCD
- 🌐 Wi-Fi connectivity
- ⏱️ Periodic weather updates to avoid unnecessary API requests

## 🏗️ System Architecture

```text
                 Wi-Fi
                   │
                   ▼
ESP32-S3 ─────── OpenWeatherMap
   │
   ├──── DS18B20 ───► Indoor temperature
   │
   ├──── NTP ───────► Date / time
   │
   └──── 1602A LCD ─► User display
```

## 🧰 Hardware

| Component | Purpose |
|---|---|
| ESP32-S3 N16R8 | Main controller and Wi-Fi |
| 1602A LCD | User interface |
| DS18B20 module | Indoor temperature |
| 1kΩ resistor | LCD contrast configuration used in this build |
| Arduino Uno | 5V supply for the LCD in this prototype |
| Breadboard + jumpers | Prototyping |

## 🔌 Wiring

### Power

| Rail | Source |
|---|---|
| 3.3V | ESP32-S3 |
| 5V | Arduino Uno in the prototype |
| GND | Common ground between supplies |

### LCD 1602A

| LCD Pin | Signal | ESP32-S3 |
|---|---|---|
| 1 | VSS / GND | GND |
| 2 | VDD / +5V | 5V rail |
| 3 | V0 / Contrast | 5V through 1kΩ in this build |
| 4 | RS | GPIO 16 |
| 5 | RW | GND |
| 6 | EN | GPIO 4 |
| 7–10 | D0–D3 | Not connected |
| 11 | D4 | GPIO 19 |
| 12 | D5 | GPIO 18 |
| 13 | D6 | GPIO 5 |
| 14 | D7 | GPIO 17 |
| 15 | Backlight + | 5V |
| 16 | Backlight − | GND |

### DS18B20 Module

| Module Pin | ESP32-S3 |
|---|---|
| GND | GND |
| VCC | 3.3V |
| DATA | GPIO 10 |

> The module used in this build includes its pull-up circuitry.

## 📌 GPIO Map

| GPIO | Function |
|---|---|
| GPIO 4 | LCD EN |
| GPIO 5 | LCD D6 |
| GPIO 10 | DS18B20 DATA |
| GPIO 16 | LCD RS |
| GPIO 17 | LCD D7 |
| GPIO 18 | LCD D5 |
| GPIO 19 | LCD D4 |

## 💻 Software Setup

### 1. ESP32 board support

Install **esp32 by Espressif Systems** and select **ESP32S3 Dev Module**.

For this N16R8 board, configure the board with **16 MB flash** and the appropriate **OPI PSRAM** setting.

### 2. Libraries

Install:

- OneWire
- DallasTemperature
- ArduinoJson

`WiFi`, `HTTPClient`, and related networking functionality are provided by the ESP32 Arduino core.

### 3. Configure credentials

Create your own local configuration and never commit real credentials:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey   = "YOUR_OPENWEATHERMAP_API_KEY";
const char* city     = "YOUR_CITY";
const char* country  = "IN";
```

### 4. Upload

Connect the ESP32-S3, select the correct serial port, compile, and upload. Open Serial Monitor at **115200 baud** for diagnostics.

## 🖥️ Display Concept

```text
Line 1:  14:32:05 27/06
Line 2:  In: 31.2°C

        Out: 29.5°C
        Clouds
```

The second-line information rotates periodically.

## 🐛 Troubleshooting

| Problem | Check |
|---|---|
| No COM port | USB cable, driver, and correct board/port |
| LCD blank | Power, RW, contrast, and wiring |
| Sensor not detected | DS18B20 pinout and GPIO 10 |
| Weather unavailable | Wi-Fi, city configuration, and API key |
| `ledcSetup` errors | ESP32 core 3.x uses the newer LEDC API |

## 🔐 Security

Never commit:

- Wi-Fi passwords
- API keys
- OAuth credentials
- Personal configuration files

Use placeholders in the repository and keep private configuration local.

## 🗺️ Future Improvements

- Dedicated 5V power solution
- Enclosure / 3D-printed case
- More weather information
- Air-quality data
- Better LCD UI
- Button-based navigation
- Lower-power operation

## 👨‍💻 Author

**Mohammed Yusuf Khatai**  
Electronics & Telecommunication Engineering Student  
RAIT, D.Y. Patil Deemed University

## 📄 License

MIT License — free to use, modify, and share.
