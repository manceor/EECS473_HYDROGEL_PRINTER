M140 S0
M105
M190 S0
M104 S60
M105
M109 S60
M82 ;absolute extrusion mode
M201 X500.00 Y500.00 Z100.00 E5000.00 ;Setup machine max acceleration
M203 X500.00 Y500.00 Z10.00 E200.00 ;Setup machine max feedrate
M204 P500.00 R1000.00 T500.00 ;Setup Print/Retract/Travel acceleration
M205 X8.00 Y8.00 Z0.40 E5.00 ;Setup Jerk
M220 S100 ;Reset Feedrate
M221 S100 ;Reset Flowrate

G28 ;Home

G92 E0 ;Reset Extruder
G1 Z20 F3000 ;Move Z Axis up

G1 X145 Y135 ;Move to center
G1 Z0 ;Move needle into bath

G1 X155 E300 F1000
G1 Y125 E300 F1000
G1 X145 E300 F1000
G1 Y135 E300 F1000
G1 Z15
G1 X50

G91 ;Relative positionning
G1 E-50 F2700 ;Retract a bit

G90
M104 S0 ;Turn-off hotend
M84 X Y E ;Disable all steppers but Z

M82 ;absolute extrusion mode
M104 S0
;End of Gcode

