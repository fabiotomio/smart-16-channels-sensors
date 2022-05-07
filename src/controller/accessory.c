#include <Arduino.h>
#include <homekit/types.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>
#include <port.h>

#define PIN_LED_BUILD_IN D4  // Build in LED


//-------------------------------------------------------------------
// Bulb 1
//-------------------------------------------------------------------

homekit_characteristic_t motion_sensor_1_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);

void motion_sensor_1_callback(uint8_t status) {
  motion_sensor_1_detected.value = HOMEKIT_BOOL(status);
  homekit_characteristic_notify(&motion_sensor_1_detected,  HOMEKIT_BOOL(status));
}


//-------------------------------------------------------------------
// END Bulb 1
//-------------------------------------------------------------------


void accessory_init() {  
}

void builtInLed_set_status(bool on) {
  digitalWrite(PIN_LED_BUILD_IN, on ? LOW : HIGH);
}

void builtInLed_blink(int intervalInMs, int count) {
  for (int i = 0; i < count; i++) {
    builtInLed_set_status(true);
    delay(intervalInMs);
    builtInLed_set_status(false);
    delay(intervalInMs);
  }
}

void accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
  builtInLed_blink(500, 3);
}

// Accessories

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart 16 Channels Switches"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Rancho P&R Smart Experience by fabiotomio"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "7890000000004"),
            HOMEKIT_CHARACTERISTIC(MODEL, "16 channels sensors"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.4.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=2, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 1"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 1"),
            &motion_sensor_1_detected,
            NULL
        }),
        NULL
    }),
    // HOMEKIT_ACCESSORY(.id=3, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 2"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_2_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 2"),
    //         &bulb_2_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=4, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 3"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_3_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 3"),
    //         &bulb_3_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=5, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 4"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_4_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 4"),
    //         &bulb_4_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=6, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 5"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 5"),
    //         &bulb_5_status,
    //         &bulb_5_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=7, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 6"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 6"),
    //         &bulb_6_status,
    //         &bulb_6_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=8, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 7"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 7"),
    //         &bulb_7_status,
    //         &bulb_7_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=9, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 8"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 8"),
    //         &bulb_8_status,
    //         &bulb_8_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=10, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 8"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 9"),
    //         &bulb_9_status,
    //         &bulb_9_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=11, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 10"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_10_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 10"),
    //         &bulb_10_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=12, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 11"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_11_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 11"),
    //         &bulb_11_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=13, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 12"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_12_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 12"),
    //         &bulb_12_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=14, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 13"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_13_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 13"),
    //         &bulb_13_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=15, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 14"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_14_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 14"),
    //         &bulb_14_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=16, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 15"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_15_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 15"),
    //         &bulb_15_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    // HOMEKIT_ACCESSORY(.id=17, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
    //     HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
    //         HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 16"),
    //         HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
    //         NULL
    //     }),
    //     HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
    //         &bulb_16_status,
    //         HOMEKIT_CHARACTERISTIC(NAME, "Bulb 16"),
    //         &bulb_16_brightness,
    //         NULL
    //     }),
    //     NULL
    // }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "041-29-338",
    .setupId = "ABCD"
};
