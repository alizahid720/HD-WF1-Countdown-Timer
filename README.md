HD-WF1 Countdown Timer Firmware
Overview
This firmware runs on the HD-WF1 (ESP32-S2) controller with a 64x32 HUB75 LED panel. It implements a countdown timer with the following features:

Web Interface: Set timer duration (in seconds) and a custom message via a phone browser.
Buttons: Start the countdown (GPIO 11, existing button) and reset the timer/display (GPIO 12, to be wired).
Display: Shows the countdown in MM:SS format; displays the custom message when the timer reaches zero.

Requirements
Hardware

HD-WF1 controller with a 64x32 HUB75 LED panel connected to the 75EX1 port (16-pin ribbon cable).
Existing push button on GPIO 11 (start).
Additional push button for GPIO 12 (reset) with a 10kΩ pull-up resistor.
5V 4A power supply (Micro-USB or 5V connector).
USB-A to USB-A cable for flashing.
2.4GHz Wi-Fi network (ESP32-S2 does not support 5GHz).

Software

Visual Studio Code with PlatformIO extension.
Project files (provided in this folder).

Setup Instructions

Install Software:

Download and install Visual Studio Code: https://code.visualstudio.com/
Install the PlatformIO extension: In VS Code, go to Extensions, search for “PlatformIO,” and install.
Open the project: In VS Code, select File > Open Folder and choose this project directory.


Update Wi-Fi Credentials:

Open src/HD-WF1-WF2-LED-MatrixPanel-DMA.ino.cpp in VS Code.
Replace the placeholders with your 2.4GHz Wi-Fi network’s SSID and password:
cppconst char *wifi_ssid = "YOUR_WIFI_NAME"; // Replace with your Wi-Fi name
const char *wifi_pass = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi password

Save the file.


Wire Hardware:

HUB75 Panel: Ensure the 64x32 LED panel is connected to the 75EX1 port (16-pin ribbon cable).
Reset Button: Connect a push button to GPIO 12:

One leg to GPIO 12, the other to ground.
Add a 10kΩ resistor between GPIO 12 and 3.3V (pull-up configuration).


Start Button: GPIO 11 already has a button on the HD-WF1.
Power: Connect a 5V 4A power supply via Micro-USB or the 5V connector.


Flash Firmware:

Enter download mode: Bridge the two pads near the MicroUSB port on the HD-WF1.
Connect the HD-WF1 to your computer using a USB-A to USB-A cable (plugged into the USB-A port on the HD-WF1).
In PlatformIO (VS Code), click the “Build” button (checkmark icon) to compile the code.
Click the “Upload” button (arrow icon) to flash the firmware.
Open the Serial Monitor (115200 baud) to view the IP address (e.g., 192.168.1.100).



Testing Instructions

Verify Wi-Fi Connection:

Power on the HD-WF1.
The LED panel displays “Connecting” followed by the IP address.
If “Connecting” persists or no IP appears, check:

Wi-Fi credentials are correct (2.4GHz network).
Router is in range and operational.
Restart the HD-WF1 by unplugging and replugging the power.


Note the IP address from the LED panel or Serial Monitor.


Test Web Interface:

Connect your phone to the same Wi-Fi network as the HD-WF1.
Open a browser and enter the IP address (e.g., http://192.168.1.100).
You should see:

A heading: “Countdown Timer”
A form with:

“Time (sec)” number input (minimum 1 second, required).
“Message” text input (max 20 characters, required).
“Go” button.




Test form submission:

Enter a time (e.g., 60 for 1 minute).
Enter a message (e.g., Time's Up!).
Click “Go.”
Verify the LED panel shows the countdown (e.g., 1:00, 0:59, ..., 0:00).
Confirm the message displays when the timer reaches zero.




Test Buttons:

Press the start button (GPIO 11) to begin the countdown (same as clicking “Go”).
Press the reset button (GPIO 12) to stop the timer and clear the LED panel.
Ensure buttons respond reliably without multiple triggers.


Test Edge Cases:

Enter a negative or zero time (should not start the countdown).
Enter a long message (>20 characters) to verify it truncates or displays correctly.
Disconnect and reconnect Wi-Fi to ensure the web interface remains accessible.
Restart the HD-WF1 to confirm consistent behavior.


Troubleshooting:

No IP Address: Verify Wi-Fi credentials, router settings, and 2.4GHz compatibility. Check Serial Monitor for errors.
Web Interface Not Loading: Ensure phone is on the same Wi-Fi network; retry the IP address.
Display Issues: Confirm the HUB75 panel is 64x32 with a 16-pin ribbon cable connected to 75EX1.
Button Issues: Check GPIO 12 wiring (pull-up resistor) and ensure GPIO 11 button is functional.
Serial Output: Use PlatformIO’s Serial Monitor to view debug messages.


Feedback:

Report the following to the developer:

Does the web interface load and submit correctly?
Does the timer display in MM:SS format and update smoothly?
Does the message appear correctly when the timer reaches zero?
Do the start and reset buttons work reliably?
Any display alignment, text size, or button response issues?
Confirm the HUB75 panel type (model, 16-pin connector).
Share Serial Monitor logs if errors occur.





Optional: Access Point Mode
If you prefer not to use your Wi-Fi network or face connection issues, contact the developer for a version where the HD-WF1 creates its own Wi-Fi network (e.g., HD-WF1-Timer, password Timer1234). You would connect your phone to this network and access the web interface at 192.168.4.1.
Notes

The web interface is minimal for efficiency but can be styled if desired (contact the developer).
Ensure the HUB75 panel is compatible (64x32, 16-pin ribbon cable).
For issues or enhancements (e.g., larger font, different colors), provide detailed feedback.