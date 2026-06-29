#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

// ── CONFIG — fill these in ────────────────────────────
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey   = "YOUR_OPENWEATHERMAP_API_KEY";
const char* city     = "Thane";
const char* country  = "IN";
// ─────────────────────────────────────────────────────

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(16, 4, 19, 18, 5, 17);

// Contrast PWM
#define CONTRAST_PIN 2

// DS18B20
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// State
float indoorTemp   = 0.0;
float outdoorTemp  = 0.0;
String weatherDesc = "---";
int displayMode    = 0;  // 0=indoor, 1=outdoor, 2=weather

unsigned long lastWeatherFetch  = 0;
unsigned long lastTempRead      = 0;
unsigned long lastDisplaySwitch = 0;

const unsigned long WEATHER_INTERVAL = 10UL * 60 * 1000;
const unsigned long TEMP_INTERVAL    = 2000;
const unsigned long DISPLAY_INTERVAL = 4000;

// IST = UTC+5:30 = 19800 seconds
const long UTC_OFFSET = 19800;

void fetchWeather() {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = "http://api.openweathermap.org/data/2.5/weather?q="
               + String(city) + "," + String(country)
               + "&appid=" + String(apiKey)
               + "&units=metric";
  http.begin(url);
  if (http.GET() == 200) {
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, http.getString());
    outdoorTemp = doc["main"]["temp"].as<float>();
    weatherDesc = doc["weather"][0]["main"].as<String>();
    if (weatherDesc.length() > 16) weatherDesc = weatherDesc.substring(0, 16);
  }
  http.end();
}

String getTimeStr() {
  time_t now = time(nullptr) + UTC_OFFSET;
  struct tm* t = gmtime(&now);
  char buf[17];
  snprintf(buf, sizeof(buf), "%02d:%02d:%02d %02d/%02d",
           t->tm_hour, t->tm_min, t->tm_sec,
           t->tm_mday, t->tm_mon + 1);
  return String(buf);
}

void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print(getTimeStr());

  lcd.setCursor(0, 1);
  switch (displayMode) {
    case 0:
      lcd.print("In:  ");
      lcd.print(indoorTemp, 1);
      lcd.print((char)223);
      lcd.print("C       ");
      break;
    case 1:
      lcd.print("Out: ");
      lcd.print(outdoorTemp, 1);
      lcd.print((char)223);
      lcd.print("C       ");
      break;
    case 2:
      lcd.print(weatherDesc);
      lcd.print("                ");
      break;
  }
}

void setup() {
  Serial.begin(115200);

  ledcAttach(CONTRAST_PIN, 5000, 8);
  ledcWrite(CONTRAST_PIN, 120);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  sensors.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  lcd.clear();
  lcd.print("Syncing time...");
  delay(2000);

  lcd.clear();
  lcd.print("Fetching weather");
  fetchWeather();

  lcd.clear();
  Serial.println("Ready!");
}

void loop() {
  unsigned long now = millis();

  if (now - lastTempRead >= TEMP_INTERVAL) {
    sensors.requestTemperatures();
    float t = sensors.getTempCByIndex(0);
    if (t != -127.00) indoorTemp = t;
    lastTempRead = now;
  }

  if (now - lastWeatherFetch >= WEATHER_INTERVAL) {
    fetchWeather();
    lastWeatherFetch = now;
  }

  if (now - lastDisplaySwitch >= DISPLAY_INTERVAL) {
    displayMode = (displayMode + 1) % 3;
    lastDisplaySwitch = now;
  }

  updateDisplay();
  delay(1000);
}
