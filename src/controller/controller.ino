#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "ESPButton.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

#define PIN_BUTTON 0

#define MUX_S0 13
#define MUX_S1 12
#define MUX_S2 14
#define MUX_S3 4

extern "C" homekit_server_config_t config;
extern "C" void accessory_init();
extern "C" void update_switch(uint8_t port, uint8_t state);
extern "C" void update_motion_sensor(uint8_t port, uint8_t state);

static uint8_t  motion_sensor_states[6] = { 0, 0, 0, 0, 0, 0 };
static uint8_t  switch_states[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static int mux_control_pin[] = {MUX_S0, MUX_S1, MUX_S2, MUX_S3};

static int mux_channel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

static uint32_t next_heap_millis = 0;
static uint32_t next_wifi_check_millis = 0;
static uint32_t next_motion_sensors_check_millis = 0;
static bool     last_wifi_state = false;
static uint8_t  wifi_connection_errors = 1;




WiFiManager wifiManager;

//----------------------------------
// Micro controller functions
//----------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  digitalWrite(MUX_S0, LOW);
  digitalWrite(MUX_S1, LOW);
  digitalWrite(MUX_S2, LOW);
  digitalWrite(MUX_S3, LOW);

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
      update_switch(7, 1);
    }

     if (event == ESPBUTTONEVENT_DOUBLECLICK) {
      update_switch(7, 0);
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
  const uint32_t t = millis();

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

  for (uint8_t i = 0; i < 16; i++) {
//    printf("Port %d content: %d.\n", i+1, read_mux(i));
//    read_mux(i);
//    int port_content = readMux(i);
//     int port_content = readMux(i);
//    // Motion Sensor
//    if( i <= 5) {
//      int state = motion_sensor_state(port_content);
//      if(motion_sensor_states[i] != state) {
//        update_motion_sensor(i, state);
//        motion_sensor_states[i] = state;
//      }
//    }
  }

  if (t > next_heap_millis) {
    next_heap_millis = t + 1800 * 1000;
    printf("Free heap: %d, HomeKit clients: %d\n", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }

  ESPButton.loop();
  arduino_homekit_loop();
}


int read_mux(int channel){
  for(int i = 0; i < 4; i ++){
    digitalWrite(mux_control_pin[i], mux_channel[channel][i]);
  }
  return analogRead(A0);
}

int motion_sensor_state(int val) {
  if( val > 512) {
    return 0;
  } else {
    return 1;
  }
}
