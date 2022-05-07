# Smart 16 channels sensors

# ESP8266 Arduino HomeKit Switch Controller

> Using an ESP8266 as a 16 channels sensors with native Apple HomeKit support

### Add to HomeKit

As soon as the ESP8266 is connected to the network, the `Home` app can be opened on the iOS device and be added as a new device.

#### Paring Code

For the paring enter the code: `041-29-338`.

## Workspace

### Local Development

#### Required

- Arduino v1.8.13
  - Additional Board Manager: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
    - esp8266 by ESP8266 Community: https://github.com/esp8266/Arduino
  - Libraries:
    - HomeKit-ESP8266 by Mixiaoxiao: `https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266`

## Author
**Fábio Tomio**

- Github: [@fabiotomio](https://github.com/fabiotomio)

## Resources
- [Arduino Board - ESP8266](https://www.esp8266.com/)
- [Arduino Library - Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [Adafruit PWM](https://learn.adafruit.com/16-channel-pwm-servo-driver/library-reference)
- [Millis (without delay)]()https://randomnerdtutorials.com/interrupts-timers-esp8266-arduino-ide-nodemcu/)
- [Schema](https://diyi0t.com/wp-content/uploads/2020/11/Servo-PCA9685-ESP8266-NodeMCU_Steckplatine.png)

## Notes
- The accessory name is the unique id, need to be different for each device (HOMEKIT_CHARACTERISTIC(NAME,...)
- The id (HOMEKIT_ACCESSORY(.id=1,..) need to be incremental sequence.
