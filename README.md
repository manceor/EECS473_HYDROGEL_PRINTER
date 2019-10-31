# Software Setup Guide

## Flashing the ATmega1284P through USB

To program the ATmega1284P, install download AVROSP.

This guide assumes that you have AVROSP added to your PATH.

1) When you first plug in the board

2) Hold RESET and SW0

3) Let go of RESET

4) Let go of SW0

5) In the terminal, enter the command "mode comx baud=57600 parity=n data=8".
    Replace the "x" in "comx" with the COM port that your board is plugged into.
    (This can be found in the "Device Manager" on windows)

6) In the folder where your .hex file is, run the following command:
    "AVROSP -dATmega1284P -cCOMx -pf -vf -if "filename.hex" -e".

## Setting up Atmel Studio for board programming

Install Atmel Studio 7

From fresh code:
Download TH3D Firmware <https://www.th3dstudio.com/knowledgebase/th3d-unified-firmware-package/>
Unzip into a folder of your choice, now referred to as "%TH3D DIRECTORY%"

1) New -> Project -> Create Project From Arduino Sketch

2) Create a new folder somewhere and select it

3) Sketch File:"%TH3D DIRECTORY%\TH3DUF_R2\Firmware\TH3DUF_R2\TH3DUF_R2.ino"

4) Arduino IDE Path: "%TH3D DIRECTORY%\TH3DUF_R2\Windows Arduino\"

5) To find the Marlin Code: see Arduino Core -> include -> variants
