#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "ESPButton.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

extern "C" homekit_server_config_t config;
extern "C" void accessory_init();
extern "C" void motion_sensor_1_callback(uint8_t status);

#define PIN_BUTTON D5

static uint32_t next_heap_millis = 0;
static uint32_t next_wifi_check_millis = 0;
static bool last_wifi_state = false;
static uint8_t wifi_connection_errors = 1;

WiFiManager wifiManager;

//----------------------------------
// Micro controller functions
//----------------------------------
void setup() {
  Serial.begin(115200);

  wifiManager.setConfigPortalTimeout(120);
  if(!wifiManager.autoConnect("Rancho P&R - Smart Sensor")) {
      printf("Failed to connect and hit timeout");
      ESP.restart();
  }

  last_wifi_state = true;

  // Setup the reset switch button
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  ESPButton.add(0, PIN_BUTTON, LOW, true, true);
  ESPButton.setCallback([&](uint8_t id, ESPButtonEvent event) {
    printf("Button %d Event: %s\n", id, ESPButton.getButtonEventDescription(event));

    if (event == ESPBUTTONEVENT_SINGLECLICK) {
      motion_sensor_1_callback(1);
    }
    
    if (event == ESPBUTTONEVENT_LONGCLICK) {
      printf("Cleanning and rebooting...\n");
      wifiManager.resetSettings();
      delay(10);
      ESP.eraseConfig();
      delay(10);
      homekit_storage_reset();
      delay(10);
      ESP.restart();
    }
  });
  ESPButton.begin();

  accessory_init();
  arduino_homekit_setup(&config);
}

void loop() {
  ESPButton.loop();
  arduino_homekit_loop();

  const uint32_t t = millis();

  if (t > next_heap_millis) {
    next_heap_millis = t + 10 * 1000;
    printf("Free heap: %d, HomeKit clients: %d\n", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }

  if (t > next_wifi_check_millis) {
    next_wifi_check_millis = t + 10 * 1000;

    // Verifica se a conexao esta ativa
    if(WiFi.status() != WL_CONNECTED) {
      last_wifi_state = false;
      if(wifi_connection_errors <= 10) {
        printf("Waiting wifi connection: %d/10.\n", wifi_connection_errors);
        wifi_connection_errors++;
      } else {
        printf("Wifi connection fail, restarting...\n");
        ESP.restart();
      }      
    } else if (last_wifi_state == false){
      printf("Wifi connection reestablished, restarting...\n");
      ESP.restart();
    }
  }
}
