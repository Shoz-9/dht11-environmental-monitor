# ESP32 Environmental Monitor (DHT11)

Embedded environmental monitoring system built on an ESP32, reading live
temperature/humidity from a DHT11 sensor and displaying readings on a
16x2 I2C LCD. WiFi connectivity and an HTTP dashboard are in progress.

## Status
- [x] DHT11 sensor read over GPIO, with failure detection (isnan checks)
- [x] WiFi connection (DHCP)
- [x] I2C LCD displaying live sensor readings
- [ ] HTTP web server with live readings
- [ ] Web-adjustable temperature setpoint + status LEDs
- [ ] Closed-loop fan control (v2)

## Hardware
- ESP32 Dev Module
- DHT11 temperature/humidity sensor (GPIO 4)
- 16x2 I2C LCD (address 0x27, custom I2C pins 13/12)

## Setup
1. Copy `secret.h.example` to `secret.h` and fill in your WiFi credentials.
2. Flash with Arduino IDE (ESP32 board package required).

## Known issues / notes
- DHT11 has a ±2°C systematic accuracy limit — not something averaging fixes.
