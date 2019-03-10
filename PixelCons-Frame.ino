#include <ESP8266WiFi.h>
#include "src/utils.h"
#include "src/storage.h"
#include "src/ethereum.h"
#include "src/display.h"
#include "src/network.h"

#include "src/rendering.h"
#include "src/pageConfig.h"

// Setup
void setup() {
  pinMode(0, INPUT);
  Serial.begin(115200);
  Serial.println("PixelCon Frame v1.0");
  Serial.println();
  storage::init();
  display::init();
  
  rendering::init();
  pageConfig::setup();

  display::drawLoadingScreen();
  display::flush();

  network::connect();
  if(network::isWifiSaved()) {
    if(network::checkConnection()) {
      rendering::setWiFiRenderMode(true);
    } else {
      if(!storage::getIsStaticMode()) {
        display::drawErrorScreen();
        display::flush();
        delay(5000);
      }
    }
  }
}

// Loop
int buttonHold = 0;
void loop() {
  bool wifiConnected = network::checkConnection();

  // run render routine
  rendering::process(wifiConnected);

  // check for button press
  if(digitalRead(0) == LOW) {
    buttonHold++;
    rendering::showIPAddress();
  } else buttonHold = 0;

  // check for wifi reset
  if(buttonHold > 100000) {
    network::resetWifi();
    display::drawBlankScreen();
    display::flush();
    
    // loop forever until user resets
    Serial.println(FS("Please reset device"));
    while(true) delay(100);
  }
}
