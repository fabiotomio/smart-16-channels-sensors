#include <Arduino.h>
#include <homekit/types.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>
#include <port.h>

#define PIN_LED_BUILD_IN D4  // Build in LED

static uint8_t port_state[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//--------------------------------
// MOTION SENSORS
//--------------------------------
homekit_characteristic_t motion_sensor_0_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);
homekit_characteristic_t motion_sensor_1_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);
homekit_characteristic_t motion_sensor_2_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);
homekit_characteristic_t motion_sensor_3_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);
homekit_characteristic_t motion_sensor_4_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);
homekit_characteristic_t motion_sensor_5_detected  = HOMEKIT_CHARACTERISTIC_(MOTION_DETECTED, false);

bool update_motion_sensor_state_and_check_diff(uint8_t port, uint8_t state) {
  if(port_state[port] == state) {
    return false;
  } else {
    port_state[port] = state;
    return true;
  }
}

void update_motion_sensor(uint8_t port, uint8_t state) {
  bool trigger = update_motion_sensor_state_and_check_diff(port, state);
  
  switch (port)
  {
  case 0:
    if(trigger) {
      motion_sensor_0_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_0_detected, HOMEKIT_BOOL(state));
    }
    break;
  case 1:
    if(trigger) {
      motion_sensor_1_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_1_detected, HOMEKIT_BOOL(state));
    }
    break;
  case 2:
    if(trigger) {
      motion_sensor_2_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_2_detected, HOMEKIT_BOOL(state));
    }
    break;
  case 3:
    if(trigger) {
      motion_sensor_3_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_3_detected, HOMEKIT_BOOL(state));
    }
    break;
  case 4:
    if(trigger) {
      motion_sensor_4_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_4_detected, HOMEKIT_BOOL(state));
    }
    break;
  case 5:
    if(trigger) {
      motion_sensor_5_detected.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&motion_sensor_5_detected, HOMEKIT_BOOL(state));
    }
    break;
  default:
    break;
  }
}

//--------------------------------
// SWITCHES
//--------------------------------

bool update_switch_state_and_check_diff(uint8_t port, uint8_t state) {
  if(port_state[port] == state) {
    return false;
  } else {
    port_state[port] = state;
    return true;
  }
}

void switch_1_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(6, value.bool_value ? 1 : 0);
}

void switch_2_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(7, value.bool_value ? 1 : 0);
}

void switch_3_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(8, value.bool_value ? 1 : 0);
}

void switch_4_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(9, value.bool_value ? 1 : 0);
}

void switch_5_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(10, value.bool_value ? 1 : 0);
}

void switch_6_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(11, value.bool_value ? 1 : 0);
}

void switch_7_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(12, value.bool_value ? 1 : 0);
}

void switch_8_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(13, value.bool_value ? 1 : 0);
}

void switch_9_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(14, value.bool_value ? 1 : 0);
}

void switch_10_on_set(homekit_value_t value) {
  if (value.format != homekit_format_bool) {
    printf("Invalid on-value format: %d\n", value.format);
    return;
  }
  update_switch_state_and_check_diff(15, value.bool_value ? 1 : 0);
}


homekit_value_t switch_1_on_get() {
  return HOMEKIT_BOOL(port_state[7]);
}

homekit_value_t switch_2_on_get() {
  return HOMEKIT_BOOL(port_state[8]);
}

homekit_value_t switch_3_on_get() {
  return HOMEKIT_BOOL(port_state[9]);
}

homekit_value_t switch_4_on_get() {
  return HOMEKIT_BOOL(port_state[10]);
}

homekit_value_t switch_5_on_get() {
  return HOMEKIT_BOOL(port_state[11]);
}

homekit_value_t switch_6_on_get() {
  return HOMEKIT_BOOL(port_state[12]);
}

homekit_value_t switch_7_on_get() {
  return HOMEKIT_BOOL(port_state[13]);
}

homekit_value_t switch_8_on_get() {
  return HOMEKIT_BOOL(port_state[14]);
}

homekit_value_t switch_9_on_get() {
  return HOMEKIT_BOOL(port_state[15]);
}

homekit_value_t switch_10_on_get() {
  return HOMEKIT_BOOL(port_state[16]);
}


homekit_characteristic_t switch_1_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_1_on_get,
  .setter=switch_1_on_set
);

homekit_characteristic_t switch_2_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_2_on_get,
  .setter=switch_2_on_set
);

homekit_characteristic_t switch_3_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_3_on_get,
  .setter=switch_3_on_set
);

homekit_characteristic_t switch_4_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_4_on_get,
  .setter=switch_4_on_set
);

homekit_characteristic_t switch_5_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_5_on_get,
  .setter=switch_5_on_set
);

homekit_characteristic_t switch_6_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_6_on_get,
  .setter=switch_6_on_set
);

homekit_characteristic_t switch_7_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_7_on_get,
  .setter=switch_7_on_set
);

homekit_characteristic_t switch_8_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_8_on_get,
  .setter=switch_8_on_set
);

homekit_characteristic_t switch_9_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_9_on_get,
  .setter=switch_9_on_set
);

homekit_characteristic_t switch_10_changed = HOMEKIT_CHARACTERISTIC_(ON, false,
  .getter=switch_10_on_get,
  .setter=switch_10_on_set
);

void change_switch_state(uint8_t port) {
  update_switch(port, port_state[port] == 0 ? 1 : 0);
}

void update_switch(uint8_t port, uint8_t state) {
  bool trigger = update_switch_state_and_check_diff(port, state);

  switch (port) {
  case 6:
    if(trigger) {
      switch_1_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_1_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 7:
    if(trigger) {
      switch_2_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_2_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 8:
    if(trigger) {
      switch_3_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_3_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 9:
    if(trigger) {
      switch_4_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_4_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 10:
    if(trigger) {
      switch_5_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_5_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 11:
    if(trigger) {
      switch_6_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_6_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 12:
    if(trigger) {
      switch_7_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_7_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 13:
    if(trigger) {
      switch_8_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_8_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 14:
    if(trigger) {
      switch_9_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_9_changed,  HOMEKIT_BOOL(state));
    }
    break;
  case 15:
    if(trigger) {
      switch_10_changed.value = HOMEKIT_BOOL(state);
      homekit_characteristic_notify(&switch_10_changed,  HOMEKIT_BOOL(state));
    }
    break;

  default:
    break;
  }
}

//--------------------------------
// HOMEKIT ACCESSORY
//--------------------------------

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

// SERVICES
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
            &motion_sensor_0_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 1"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=3, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 2"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &motion_sensor_1_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 2"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=4, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 3"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &motion_sensor_2_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 3"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=5, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 4"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &motion_sensor_3_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 4"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=6, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 5"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &motion_sensor_4_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 5"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=7, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Sensor Channel 6"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(MOTION_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &motion_sensor_5_detected,
            HOMEKIT_CHARACTERISTIC(NAME, "Motion sensor 6"),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=8, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 1"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {            
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 1"),
            &switch_1_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=9, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 2"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 2"),
            &switch_2_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=10, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 3"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 3"),
            &switch_3_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=11, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 4"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 4"),
            &switch_4_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=12, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 5"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 5"),
            &switch_5_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=13, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 6"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 6"),
            &switch_6_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=14, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 7"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 7"),
            &switch_7_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=15, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 8"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 8"),
            &switch_8_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=16, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 9"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 9"),
            &switch_9_changed,
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=17, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Smart Switch 10"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Switch 10"),
            &switch_10_changed,
            NULL
        }),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "041-29-338",
    .setupId = "ABCD"
};
