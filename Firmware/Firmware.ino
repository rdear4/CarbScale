#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "HX711.h"

#include "config.h"
#include "secrets.h"

#define TFT_CS        5
#define TFT_RST        -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         32

#define UP_Button_pin 27
#define DOWN_Button_pin 26
#define SELECT_Button_pin 25

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 14;
const int LOADCELL_SCK_PIN = 13;

double measuredWeight = 0.0;

HX711 scale;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int selectedFoodIndex = 0;
bool buttonPressed = false;
bool shouldUpdateDisplay = true;
bool selectPressed = false;

void setup() {
  //Set up pins
  pinMode(UP_Button_pin, INPUT_PULLUP);
  pinMode(DOWN_Button_pin, INPUT_PULLUP);
  pinMode(SELECT_Button_pin, INPUT_PULLUP);

  //Set up Serial
  Serial.begin(115200);
  delay(1000);

  //Initialize the Load Cell ADC
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(LOAD_CELL_CALIBRATION_VALUE / KNOWN_CALIBRATION_WEIGHT);
  scale.tare();
  
  //Initialize the LCD
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  tft.setRotation(1);
  
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("Connecting to Wifi");
  
  //Set up Wifi
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PASS);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }

  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 0);
  tft.print("Connected to: ");
  tft.print(SSID_NAME);

  tft.setCursor(0, 50);
  tft.print("IP Address: ");
  tft.print(WiFi.localIP());

  delay(3000);

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  

  

}



void loop() {

  if (!buttonPressed) {

    //Check for up button being pressed
    if (digitalRead(UP_Button_pin) == LOW) {
      buttonPressed = true;
      delay(100);
      selectedFoodIndex++;
      shouldUpdateDisplay = true;
    }

    if (digitalRead(DOWN_Button_pin) == LOW) {
      buttonPressed = true;
      delay(100);
      selectedFoodIndex--;
      shouldUpdateDisplay = true;
    }

    if (digitalRead(SELECT_Button_pin) == LOW) {
      buttonPressed = true;
      delay(100);
      selectPressed = !selectPressed;
      shouldUpdateDisplay = true;
    }

    //Check for down button being pressed

    //Check for select button being pressed
  } else {

    if (digitalRead(UP_Button_pin) == HIGH && digitalRead(DOWN_Button_pin) == HIGH && digitalRead(SELECT_Button_pin) == HIGH) {

      buttonPressed = false;

    }
  }

  if (shouldUpdateDisplay) {
    tft.setCursor(0, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.print("Food ");
    tft.print(selectedFoodIndex);

    tft.setCursor(0, 100);
    tft.print("Weight: ");
    tft.setCursor(50, 100);
    tft.print(measuredWeight, 1);
      tft.print(" g   ");

    if (selectPressed) {

      tft.setCursor(0, 50);
      tft.print("SELECT");

    }
    shouldUpdateDisplay = false;

  }

  //If new weight is available, update it on screen
  if (scale.is_ready()) {

    double newWeight = scale.get_units(2);
    if (abs(newWeight - measuredWeight) > 0.12) {
      measuredWeight = newWeight;
      //Draw over the last weight reading
      tft.fillRect(48, 98, 50, 20, ST77XX_BLACK);

      tft.setCursor(50, 100);

      tft.print(newWeight, 1);
      tft.print(" g   ");
      //Draw the new weight
    }
    }
  

}
