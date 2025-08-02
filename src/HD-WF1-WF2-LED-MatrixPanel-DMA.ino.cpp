#define WF1
#include "hd-wf1-esp32s2-config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Adafruit_GFX.h>
#include <Bounce2.h>

#define PANEL_RES_X 96
#define PANEL_RES_Y 16
#define PANEL_CHAIN 1
#define START_BUTTON PUSH_BUTTON_PIN // GPIO 11
#define RESET_BUTTON 12 // GPIO 12 for reset button

const char *wifi_ssid = "YOUR_SSID"; // Client must replace
const char *wifi_pass = "YOUR_PASSWORD"; // Client must replace

MatrixPanel_I2S_DMA *dma_display = nullptr;
AsyncWebServer server(80);
Bounce2::Button startButton = Bounce2::Button();
Bounce2::Button resetButton = Bounce2::Button();
unsigned long startTime = 0, duration = 0;
String message = "Done!";
bool counting = false;

void setup() {
  Serial.begin(115200); // Standard Serial for debugging

  // HUB75 Setup
  HUB75_I2S_CFG::i2s_pins _pins_x1 = {WF1_R1_PIN, WF1_G1_PIN, WF1_B1_PIN, WF1_R2_PIN, WF1_G2_PIN, WF1_B2_PIN, WF1_A_PIN, WF1_B_PIN, WF1_C_PIN, WF1_D_PIN, WF1_E_PIN, WF1_LAT_PIN, WF1_OE_PIN, WF1_CLK_PIN};
  HUB75_I2S_CFG mxconfig(PANEL_RES_X, PANEL_RES_Y, PANEL_CHAIN, _pins_x1);
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_20M;
  mxconfig.latch_blanking = 4;
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(128);
  dma_display->clearScreen();
  dma_display->setTextSize(1);
  dma_display->setTextColor(dma_display->color565(255, 255, 255));

  // Button Setup
  startButton.attach(START_BUTTON, INPUT);
  startButton.interval(5);
  startButton.setPressedState(LOW);
  resetButton.attach(RESET_BUTTON, INPUT);
  resetButton.interval(5);
  resetButton.setPressedState(LOW);

  // Wi-Fi Setup
  WiFi.begin(wifi_ssid, wifi_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    dma_display->setCursor(0, 0);
    dma_display->print("Connecting");
  }
  Serial.println(WiFi.localIP());
  dma_display->clearScreen();
  dma_display->setCursor(0, 0);
  dma_display->print(WiFi.localIP());
  delay(3000);
  dma_display->clearScreen();

  // Web Server Setup
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<!DOCTYPE html><html><body><h2>Countdown Timer</h2>"
                  "<form action='/set' method='POST'>"
                  "Time (sec): <input type='number' name='time' min='1' required><br>"
                  "Message: <input type='text' name='msg' maxlength='15' required><br>"
                  "<input type='submit' value='Go'>"
                  "</form></body></html>";
    request->send(200, "text/html", html);
  });
  server.on("/set", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("time", true)) duration = request->getParam("time", true)->value().toInt() * 1000;
    if (request->hasParam("msg", true)) message = request->getParam("msg", true)->value();
    counting = true;
    startTime = millis();
    request->redirect("/");
  });
  server.begin();
}

void loop() {
  startButton.update();
  resetButton.update();
  server.handleClient();

  if (startButton.pressed()) {
    counting = true;
    startTime = millis();
  }
  if (resetButton.pressed()) {
    counting = false;
    dma_display->clearScreen();
  }

  if (counting && duration > 0) {
    unsigned long elapsed = millis() - startTime;
    if (elapsed < duration) {
      int seconds = (duration - elapsed) / 1000;
      dma_display->clearScreen();
      dma_display->setCursor(10, 4); // Adjusted for 96x16
      dma_display->print(String(seconds / 60) + ":" + (seconds % 60 < 10 ? "0" : "") + String(seconds % 60));
    } else {
      dma_display->clearScreen();
      dma_display->setCursor(0, 4); // Adjusted for 96x16
      dma_display->print(message);
      counting = false;
    }
  }
  delay(10);
}