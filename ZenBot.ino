#include "Adafruit_GFX.h"// Hardware-specific library
#include <SPI.h>
#include <WiFi101.h>
#include "sensors.h"
#include "utils.h" 
#include "network.h" 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

#include <avr/dtostrf.h>

// LCD

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

void setup() {
  Serial.begin(9600);
  
  // BME680
  initializeBME680();

  // WIFI
  initializeWIFI();

  uint16_t ID = tft.readID();
  if (ID == 0xD3) ID = 0x9481;
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  showmsgXY(10, 20, 1, &FreeSans9pt7b, "Sensors:");
  showmsgXY(30, 40, 1, &FreeSans9pt7b, "Temperature");
  showmsgXY(30, 60, 1, &FreeSans9pt7b, "Pressure");
  showmsgXY(30, 80, 1, &FreeSans9pt7b, "Humidity");
  showmsgXY(30, 100, 1, &FreeSans9pt7b, "Gas resistance");
  showmsgXY(30, 120, 1, &FreeSans9pt7b, "Altitude");
  showmsgXY(10, 140, 1, &FreeSans9pt7b, "Network:");
  showmsgXY(30, 160, 1, &FreeSans9pt7b, "SSID:");
  showmsgXY(30, 180, 1, &FreeSans9pt7b, "IP:");
  showmsgXY(100, 160, 1, &FreeSans9pt7b, WiFi.SSID());
  char IP[] = "xxx.xxx.xxx.xxx";
  IPAddress ip = WiFi.localIP();
  ipAddressToStr(ip).toCharArray(IP, 16);
  showmsgXY(100, 180, 1, &FreeSans9pt7b, IP);
}

void loop() {
  // WIFI
  // printCurrentNet();
  
  tft.fillRect(180, 20, 500, 120, BLACK);

  // Temperature
  unsigned long endTime = bme.beginReading();

  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }

  Serial.print(F("Reading started at "));
  Serial.print(millis());
  Serial.print(F(" and will finish at "));
  Serial.println(endTime);

  Serial.println(F("You can do other work during BME680 measurement."));
  delay(50); // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  
  Serial.print(F("Reading completed at "));
  Serial.println(millis());

  Serial.print(F("Temperature = "));
  char Temperature[] = "10.0";
  char Pressure[] = "10.0";
  char Humidity[] = "10.0";
  char Gas[] = "10.0";
  char Altitude[] = "10.0";

 
  showmsgXY(180, 40, 1, &FreeSans9pt7b, dtostrf(bme.temperature, 2, 2, Temperature));
  Serial.print(bme.temperature);
  Serial.println(F(" *C"));

  Serial.print(F("Pressure = "));

  showmsgXY(180, 60, 1, &FreeSans9pt7b, dtostrf((bme.pressure / 100.0), 2, 2, Pressure));
  Serial.print(bme.pressure / 100.0);
  Serial.println(F(" hPa"));
  
  showmsgXY(180, 80, 1, &FreeSans9pt7b, dtostrf(bme.humidity, 2, 2, Humidity));
  Serial.print(F("Humidity = "));
  Serial.print(bme.humidity);
  Serial.println(F(" %"));

  showmsgXY(180, 100, 1, &FreeSans9pt7b, dtostrf(bme.gas_resistance / 1000.0, 2, 2, Gas));
  Serial.print(F("Gas = "));
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(F(" KOhms"));

  showmsgXY(180, 120, 1, &FreeSans9pt7b, dtostrf(bme.readAltitude(SEALEVELPRESSURE_HPA), 2, 2, Altitude));
  Serial.print(F("Approx. Altitude = "));
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(F(" m"));

  Serial.println();
  Serial.println();
  Serial.println();
  delay(5000);
}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    // tft.drawFastHLine(0, y, tft.width(), WHITE);
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(GREEN);
    tft.setTextSize(sz);
    tft.print(msg);
}
