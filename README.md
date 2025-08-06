## Overview
This firmware runs on the HD-WF1 (ESP32-S2) controller with a **96x16 HUB75 LED panel**. It implements a countdown timer with:
- **Web Interface**: Set timer duration (seconds) and custom message (max 15 characters) via phone/PC browser.
- **Buttons**: Start countdown (GPIO 11, existing button) and reset timer/display (GPIO 12, optional wiring).
- **Display**: Shows countdown in MM:SS format; displays message when timer reaches zero.

## Requirements
### Hardware
- HD-WF1 controller with a **96x16 HUB75 LED panel** (e.g., 96x20cm display, 16-pin ribbon cable to 75EX1 port).
- Push button on GPIO 11 (pre-installed).
- Push button for GPIO 12 (reset, optional; requires wiring).
- 5V 4A power supply (Micro-USB or 5V connector, AU plug).
- USB-A to USB-A cable for flashing (data-capable, included with sign).
- 2.4GHz Wi-Fi network (ESP32-S2 does not support 5GHz).

### Software
- Visual Studio Code with PlatformIO extension.
- Project files (in this repository).

## Setup Instructions
1. **Install Software**:
   - Download Visual Studio Code: [https://code.visualstudio.com/](https://code.visualstudio.com/).
   - Install PlatformIO: In VS Code, go to Extensions, search “PlatformIO,” install.
   - Open project: `File > Open Folder`, select this repository.

2. **Update Wi-Fi Credentials**:
   - Open `src/HD-WF1-WF2-LED-MatrixPanel-DMA.ino.cpp`.
   - Replace placeholders with your 2.4GHz Wi-Fi SSID/password:
     ```cpp
     const char *wifi_ssid = "YOUR_WIFI_NAME";
     const char *wifi_pass = "YOUR_WIFI_PASSWORD";

Save the file.


Wire Hardware:

HUB75 Panel: Connect 96x16 panel to 75EX1 port (16-pin ribbon cable).
Start Button: Use pre-installed button (GPIO 11).
Reset Button (Optional):

Find GPIO 12 and 3.3V pins (see wf1_pcb_pins_1.jpg, wf1_pcb_pins_2.jpg in repository or board pinout).
Connect one leg of push button to GPIO 12, other to GND.
Add 10kΩ resistor between GPIO 12 and 3.3V (pull-up).
Skip if pins are unclear; test with web interface and GPIO 11.


Power: Use 5V 4A supply (Micro-USB or 5V connector, AU plug).


Flash Firmware:

Enter download mode: Bridge pads near MicroUSB port or hold GPIO 11 button while powering on, then release.
Connect HD-WF1 to PC with USB-A to USB-A cable (USB-A port on HD-WF1).
Install CP2102 driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers.
In PlatformIO, select huidu_hd_wf1 board, click “Build” then “Upload.”
Open Serial Monitor (115200 baud) to view IP address (e.g., 192.168.1.100).



Testing Instructions

Verify Wi-Fi:

Power on HD-WF1; panel shows “Connecting” then IP address.
If no IP, check Wi-Fi credentials, router (2.4GHz), or restart HD-WF1.


Test Web Interface:

On phone/PC (same Wi-Fi), open IP in browser (e.g., http://192.168.1.100).
Verify form: “Countdown Timer” heading, “Time (sec)” (number, min 1), “Message” (max 15 characters), “Go” button.
Submit time (e.g., 60) and message (e.g., Done!); check panel for countdown (MM:SS) and message at zero.


Test Buttons:

Press GPIO 11 (start) to begin countdown.
Press GPIO 12 (reset, if wired) to clear timer/display.
Ensure reliable button response.


Test Edge Cases:

Negative/zero time (should not start).
Message >15 characters (should truncate).
Reconnect Wi-Fi; restart HD-WF1.


Troubleshooting:

No IP: Check Wi-Fi, router, Serial Monitor logs.
Flashing Fails: Ensure USB-A cable, CP2102 driver, correct COM port, download mode.
Display Issues: Confirm 96x16 panel, 16-pin cable to 75EX1.
Button Issues: Verify GPIO 11; check GPIO 12 wiring if used.


Feedback:

Report web interface, timer, button, and display functionality.
Share Serial Monitor logs for errors.
Confirm panel is 96x16, 16-pin ribbon.



Optional: Access Point Mode
Contact developer for a version where HD-WF1 creates its own Wi-Fi (HD-WF1-Timer, password Timer1234, access at 192.168.4.1).
