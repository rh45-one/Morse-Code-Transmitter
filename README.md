# ESP32 Morse Code Transmitter

A wireless communication system built with ESP32 modules that allows for Morse code signaling between devices using ESP-NOW protocol. Pressing a button on one ESP32 triggers a vibration motor on another ESP32, providing a simple way to send Morse code signals.

## Overview

This project creates a direct device-to-device communication system using:
- **Sender ESP32**: Monitors button presses and transmits signals
- **Receiver ESP32**: Receives signals and activates vibration motor

ESP-NOW is a lightweight communication protocol developed by Espressif that enables direct device-to-device communication without requiring a WiFi router/access point.

## Wiring Instructions

### Sender ESP32 Setup
- Connect one side of push button to GPIO 5
- Connect other side of push button to GND
- Connect a 10kΩ resistor between GPIO 5 and 3.3V (pull-up)

### Receiver ESP32 Setup
- Connect transistor collector to vibration motor (+)
- Connect vibration motor (-) to GND
- Connect transistor emitter to GND
- Connect transistor base to GPIO 5 through a 1kΩ resistor
- Connect diode across motor terminals (cathode to +, anode to -)

## Software Setup

1. Download and install the Arduino IDE
2. Install the ESP32 board package through the Board Manager:
   - Go to File > Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools > Board > Board Manager and install ESP32
3. Upload `morse_sender.ino` to the sender ESP32
4. Upload `morse_receiver.ino` to the receiver ESP32

## How It Works

1. When powered on, both ESP32s initialize the ESP-NOW protocol
2. The sender ESP32 registers the receiver's MAC address as a peer
3. When the button is pressed on the sender:
   - Short press: Sends a "dot" signal
   - Long press: Sends a "dash" signal
4. The receiver ESP32 activates the vibration motor for:
   - Short duration for dots
   - Longer duration for dashes

The ESP-NOW protocol enables ultra-low-latency communication, making the system feel responsive and immediate.

## Usage

1. Power on both ESP32 devices
2. Wait for initialization (blue LED will blink once when ready)
3. Press the button on the sender ESP32 to transmit signals:
   - Press and quickly release for a dot (short vibration)
   - Press and hold for a dash (long vibration)
   - Use combinations of dots and dashes to create Morse code messages

## Morse Code Reference
```
| Letter | Morse Code | Letter | Morse Code |
|--------|------------|--------|------------|
| A      | .-         | N      | -.         |
| B      | -...       | O      | ---        |
| C      | -.-.       | P      | .--.       |
| D      | -..        | Q      | --.-       |
| E      | .          | R      | .-.        |
| F      | ..-.       | S      | ...        |
| G      | --.        | T      | -          |
| H      | ....       | U      | ..-        |
| I      | ..         | V      | ...-       |
| J      | .---       | W      | .--        |
| K      | -.-        | X      | -..-       |
| L      | .-..       | Y      | -.--       |
| M      | --         | Z      | --..       |
```
## Customization

- Adjust vibration durations in the code to match your preference
- Add LEDs for visual feedback
- Incorporate multiple buttons for predefined messages
- Add a buzzer for audible feedback
- Implement a translation system to convert text to Morse code

## Troubleshooting

- If devices fail to communicate, check the MAC addresses in the code
- Ensure both devices are powered and within range (ESP-NOW has a range of ~200m line of sight)
- Check the serial monitor output for debugging information
- Verify wiring connections, especially for the vibration motor circuit

## License

This project is open source and available under the MIT License.

