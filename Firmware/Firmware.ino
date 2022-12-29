#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "secrets.h"

#define TFT_CS        5
#define TFT_RST        15 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         32

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // put your setup code here, to run once:

  //Set up Serial
  Serial.begin(115200);
  delay(1000);
  //Set up Wifi
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PASS);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  //Initialize the LCD
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("This is only a test");

}

void loop() {
  // put your main code here, to run repeatedly:

}
