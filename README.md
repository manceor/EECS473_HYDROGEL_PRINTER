To program the ATmega1284P, download AVROSP. When you first plug in the
board, you must hold RESET and SW0, then let go of RESET, then let go of SW0.
Then, in the terminal, enter the command "mode comx baud=57600 parity=n data=8".
Replace the "x" in "comx" with the COM port that your board is plugged into.
Then, in the folder where your .hex file is, run the following command:
"AVROSP -dATmega1284P -cCOMx -pf -vf -if"filename.hex" -e".