EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr User 10039 6890
encoding utf-8
Sheet 1 1
Title "Dimmable Ceiling Light Controller"
Date "2019-08-11"
Rev "v1.1.0"
Comp "slimc"
Comment1 "Open Source Project"
Comment2 "github.com/slimcdk/smart-home-modules"
Comment3 "Smart Home Modules"
Comment4 "Auther: Christian Skjerning | slimc"
$EndDescr
$Comp
L Isolator:LTV-817 U1
U 1 1 5CD36A1B
P 3650 2500
F 0 "U1" H 3650 2825 50  0000 C CNN
F 1 "LTV-817" H 3650 2734 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 3450 2300 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 3650 2400 50  0001 L CNN
	1    3650 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5CD372F6
P 4450 2150
F 0 "R2" H 4300 2200 50  0000 R CNN
F 1 "10K" H 4350 2100 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 2150 50  0001 C CNN
F 3 "~" H 4450 2150 50  0001 C CNN
	1    4450 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5CD373D6
P 3100 2400
F 0 "R1" V 2900 2400 50  0000 C CNN
F 1 "390K" V 2984 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3030 2400 50  0001 C CNN
F 3 "~" H 3100 2400 50  0001 C CNN
	1    3100 2400
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5CD45A37
P 1350 1300
F 0 "J1" H 1350 1550 50  0000 C CNN
F 1 "Screw_Terminal_01x03" H 1430 1341 50  0001 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 1350 1300 50  0001 C CNN
F 3 "~" H 1350 1300 50  0001 C CNN
	1    1350 1300
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5CD45C5A
P 1350 4600
F 0 "J2" H 1350 4350 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1850 4500 50  0001 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1350 4600 50  0001 C CNN
F 3 "~" H 1350 4600 50  0001 C CNN
	1    1350 4600
	-1   0    0    1   
$EndComp
Text Notes 1250 1200 2    50   ~ 0
NEUTRAL
Text Notes 1250 1400 2    50   ~ 0
SWITCH
Text Notes 1250 1300 2    50   ~ 0
CONSTANT
Text Notes 1250 4600 2    50   ~ 0
NEUTRAL
Text Notes 1250 4500 2    50   ~ 0
LIVE LOAD
$Comp
L Device:Fuse F1
U 1 1 5D03534A
P 1900 4500
F 0 "F1" V 1700 4500 50  0000 C CNN
F 1 "Fuse" V 1800 4500 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuseholder5x20_horiz_open_lateral_Type-II" V 1830 4500 50  0001 C CNN
F 3 "~" H 1900 4500 50  0001 C CNN
	1    1900 4500
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5D375CC4
P 3200 3850
F 0 "C2" V 3150 3950 50  0000 C CNN
F 1 "22n" V 3250 4000 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3200 3850 50  0001 C CNN
F 3 "~" H 3200 3850 50  0001 C CNN
	1    3200 3850
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:IRF740 Q3
U 1 1 5D375FEC
P 3000 4200
F 0 "Q3" H 3300 4300 50  0000 L CNN
F 1 "IRF840" H 3200 4400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-263-3_TabPin2" H 3250 4125 50  0001 L CIN
F 3 "http://www.vishay.com/docs/91054/91054.pdf" H 3000 4200 50  0001 L CNN
	1    3000 4200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5D37DCE9
P 2650 3950
F 0 "#PWR06" H 2650 3700 50  0001 C CNN
F 1 "GND" H 2655 3777 50  0000 C CNN
F 2 "" H 2650 3950 50  0001 C CNN
F 3 "" H 2650 3950 50  0001 C CNN
	1    2650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5D3910B7
P 3950 3850
F 0 "R11" V 3850 3700 50  0000 L CNN
F 1 "1K" V 3850 3900 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3880 3850 50  0001 C CNN
F 3 "~" H 3950 3850 50  0001 C CNN
	1    3950 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5D39111A
P 3950 3600
F 0 "R10" V 3850 3450 50  0000 L CNN
F 1 "2M2" V 3850 3650 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P12.70mm_Horizontal" V 3880 3600 50  0001 C CNN
F 3 "~" H 3950 3600 50  0001 C CNN
	1    3950 3600
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q4
U 1 1 5D3B2EAE
P 4550 4500
F 0 "Q4" V 4800 4500 50  0000 C CNN
F 1 "KSP44" V 4900 4500 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4750 4425 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 4550 4500 50  0001 L CNN
	1    4550 4500
	0    -1   1    0   
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 5D3C0D31
P 3450 4600
F 0 "D2" H 3450 4750 50  0000 C CNN
F 1 "1N4007" H 3450 4850 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3450 4425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3450 4600 50  0001 C CNN
	1    3450 4600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 5D3C1036
P 3950 4350
F 0 "R5" V 3850 4200 50  0000 L CNN
F 1 "330K" V 3850 4400 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3880 4350 50  0001 C CNN
F 3 "~" H 3950 4350 50  0001 C CNN
	1    3950 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 5D421A86
P 3950 3350
F 0 "R13" V 3850 3200 50  0000 L CNN
F 1 "2M2" V 3850 3400 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P12.70mm_Horizontal" V 3880 3350 50  0001 C CNN
F 3 "~" H 3950 3350 50  0001 C CNN
	1    3950 3350
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5D430426
P 3950 4600
F 0 "R9" V 3850 4450 50  0000 L CNN
F 1 "33K" V 3850 4650 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3880 4600 50  0001 C CNN
F 3 "~" H 3950 4600 50  0001 C CNN
	1    3950 4600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5D47AA03
P 8700 4750
F 0 "#PWR08" H 8700 4500 50  0001 C CNN
F 1 "GND" H 8705 4577 50  0000 C CNN
F 2 "" H 8700 4750 50  0001 C CNN
F 3 "" H 8700 4750 50  0001 C CNN
	1    8700 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5D682098
P 3950 4100
F 0 "R12" V 3850 3950 50  0000 L CNN
F 1 "2M2" V 3850 4150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P12.70mm_Horizontal" V 3880 4100 50  0001 C CNN
F 3 "~" H 3950 4100 50  0001 C CNN
	1    3950 4100
	0    1    1    0   
$EndComp
$Comp
L Device:CP C3
U 1 1 5D5E10BF
P 5400 4600
F 0 "C3" V 5250 4600 50  0000 C CNN
F 1 "4µ7" V 5150 4600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5438 4450 50  0001 C CNN
F 3 "~" H 5400 4600 50  0001 C CNN
	1    5400 4600
	0    -1   -1   0   
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32D U6
U 1 1 5D68100C
P 8700 2900
F 0 "U6" H 8200 4400 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 8200 4300 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 8700 1400 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 8400 2950 50  0001 C CNN
	1    8700 2900
	-1   0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5D6ECCD4
P 7250 1700
F 0 "SW1" H 7250 2000 50  0000 C CNN
F 1 "SW_Push" H 7250 1900 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Tactile_Straight_KSA0Axx1LFTR" H 7250 1900 50  0001 C CNN
F 3 "" H 7250 1900 50  0001 C CNN
	1    7250 1700
	1    0    0    -1  
$EndComp
$Comp
L Power_Supplies:HLK-PM05 U2
U 1 1 5D965BB1
P 2750 1250
F 0 "U2" H 2750 1492 40  0000 C CNN
F 1 "HLK-PM05" H 2750 1416 40  0000 C CNN
F 2 "Power_Supply:HLK-PM01" H 1850 2600 60  0001 C CNN
F 3 "" H 1850 2600 60  0000 C CNN
	1    2750 1250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U3
U 1 1 5D9D89A0
P 4050 1200
F 0 "U3" H 4050 1500 50  0000 C CNN
F 1 "AMS1117-3.3" H 4050 1400 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4050 1400 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4150 950 50  0001 C CNN
	1    4050 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5D47292B
P 6050 4250
F 0 "C4" H 6100 4700 50  0000 R CNN
F 1 "100n" H 6150 4800 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6050 4250 50  0001 C CNN
F 3 "~" H 6050 4250 50  0001 C CNN
	1    6050 4250
	-1   0    0    1   
$EndComp
$Comp
L Transistor_FET:IRF740 Q2
U 1 1 5D363A45
P 3000 3500
F 0 "Q2" H 3300 3450 50  0000 L CNN
F 1 "IRF840" H 3200 3350 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-263-3_TabPin2" H 3250 3425 50  0001 L CIN
F 3 "http://www.vishay.com/docs/91054/91054.pdf" H 3000 3500 50  0001 L CNN
	1    3000 3500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5E004460
P 7550 1450
F 0 "R6" H 7700 1500 50  0000 R CNN
F 1 "10K" H 7750 1400 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7480 1450 50  0001 C CNN
F 3 "~" H 7550 1450 50  0001 C CNN
	1    7550 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E017ACD
P 5800 2750
F 0 "#PWR01" H 5800 2500 50  0001 C CNN
F 1 "GND" H 5805 2577 50  0000 C CNN
F 2 "" H 5800 2750 50  0001 C CNN
F 3 "" H 5800 2750 50  0001 C CNN
	1    5800 2750
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D1
U 1 1 5E99C50F
P 6950 4000
F 0 "D1" H 6600 3800 50  0000 L CNN
F 1 "WS2812B" H 6500 3700 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 7000 3700 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7050 3625 50  0001 L TNN
	1    6950 4000
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5D5510C7
P 6250 4250
F 0 "C1" H 6300 4700 50  0000 R CNN
F 1 "100n" H 6350 4800 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6250 4250 50  0001 C CNN
F 3 "~" H 6250 4250 50  0001 C CNN
	1    6250 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 2500 3200 2500
Wire Wire Line
	3200 2500 3200 2600
Wire Wire Line
	3200 2600 3350 2600
Wire Wire Line
	2850 2400 2950 2400
Wire Wire Line
	3250 2400 3350 2400
Wire Wire Line
	2900 3700 2900 3850
Wire Wire Line
	3100 3850 2900 3850
Wire Wire Line
	2650 3850 2650 3950
Connection ~ 2900 3850
Wire Wire Line
	2900 3850 2900 4000
Wire Wire Line
	2900 3850 2650 3850
Wire Wire Line
	3200 4200 3500 4200
Wire Wire Line
	3500 4200 3500 3850
Wire Wire Line
	3500 3500 3200 3500
Wire Wire Line
	3300 3850 3500 3850
Connection ~ 3500 3850
Wire Wire Line
	3500 3850 3500 3500
Wire Wire Line
	3600 4100 3800 4100
Wire Wire Line
	3500 3850 3800 3850
Wire Wire Line
	4100 3850 4900 3850
Wire Wire Line
	3600 3600 3800 3600
Wire Wire Line
	4100 3600 4300 3600
Wire Wire Line
	4300 3600 4300 3750
Wire Wire Line
	4300 3750 4900 3750
Wire Wire Line
	4100 4100 4300 4100
Wire Wire Line
	4300 4100 4300 3950
Wire Wire Line
	4300 3950 4900 3950
Wire Wire Line
	5900 3750 5800 3750
Wire Wire Line
	1550 4500 1750 4500
Wire Wire Line
	1650 4600 1550 4600
Wire Wire Line
	1550 1200 1650 1200
Wire Wire Line
	1650 1200 2450 1200
Wire Wire Line
	1750 1300 1750 3200
Wire Wire Line
	3050 1300 3650 1300
Wire Wire Line
	3650 1300 3650 1600
Wire Wire Line
	3650 1600 4050 1600
Wire Wire Line
	4050 1600 4050 1500
Connection ~ 4050 1600
Wire Wire Line
	3050 1200 3650 1200
Wire Wire Line
	1850 1400 1550 1400
Wire Wire Line
	1950 2500 1650 2500
Wire Wire Line
	1650 1200 1650 2500
Connection ~ 1650 2500
Connection ~ 1650 1200
Wire Wire Line
	3950 2600 4050 2600
Wire Wire Line
	4050 1600 4050 2600
Connection ~ 1750 1300
Wire Wire Line
	1750 1300 2450 1300
Wire Wire Line
	1550 1300 1750 1300
Wire Wire Line
	3600 3200 2900 3200
Wire Wire Line
	3600 3200 3600 3600
Wire Wire Line
	2900 3300 2900 3200
Connection ~ 2900 3200
Wire Wire Line
	2900 3200 1750 3200
Wire Wire Line
	2900 4400 2900 4500
Wire Wire Line
	2900 4500 3600 4500
Wire Wire Line
	3600 4100 3600 4500
Wire Wire Line
	2900 4500 2050 4500
Connection ~ 2900 4500
Wire Wire Line
	3800 4350 3700 4350
Wire Wire Line
	4100 4350 4400 4350
Wire Wire Line
	4400 4350 4400 4050
Wire Wire Line
	4850 4600 4750 4600
Wire Wire Line
	4850 4150 4850 4600
Wire Wire Line
	4850 4600 5250 4600
Connection ~ 4850 4600
Wire Wire Line
	5550 4600 5900 4600
Wire Wire Line
	6050 4350 6050 4600
Connection ~ 6050 4600
Wire Wire Line
	4100 4600 4350 4600
Wire Wire Line
	3600 4600 3700 4600
Wire Wire Line
	3700 4350 3700 4600
Connection ~ 3700 4600
Wire Wire Line
	3700 4600 3800 4600
Wire Wire Line
	1650 4600 3300 4600
Connection ~ 1650 4600
Wire Wire Line
	4400 4050 4550 4050
Wire Wire Line
	4550 4300 4550 4050
Connection ~ 4550 4050
Wire Wire Line
	4550 4050 4900 4050
Wire Wire Line
	1650 2500 1650 3100
Wire Wire Line
	1650 3100 3750 3100
Connection ~ 1650 3100
Wire Wire Line
	1650 3100 1650 4600
Wire Wire Line
	3750 3100 3750 3350
Wire Wire Line
	3750 3350 3800 3350
Wire Wire Line
	4100 3350 5900 3350
Wire Wire Line
	5900 3350 5900 3750
Connection ~ 4050 2600
Wire Wire Line
	5800 4150 5900 4150
Wire Wire Line
	5900 4150 5900 4600
Connection ~ 5900 4600
Wire Wire Line
	5800 3850 6250 3850
Wire Wire Line
	6250 4350 6250 4600
Connection ~ 6250 4600
Wire Wire Line
	6250 3850 6250 3500
Wire Wire Line
	6350 4050 6350 3600
Wire Wire Line
	5800 4050 6350 4050
Wire Wire Line
	5800 3950 6050 3950
Wire Wire Line
	6050 3950 6050 4150
Wire Wire Line
	6250 4150 6250 3850
Connection ~ 6250 3850
Wire Wire Line
	1850 2400 1950 2400
Wire Wire Line
	1850 1400 1850 2400
Wire Wire Line
	5800 2600 5800 2750
Wire Wire Line
	7550 1700 8100 1700
Wire Wire Line
	7450 1700 7550 1700
Connection ~ 7550 1700
Wire Wire Line
	7550 1700 7550 1600
Wire Wire Line
	6350 3600 8100 3600
Wire Wire Line
	8100 3500 6250 3500
Connection ~ 7550 1200
Wire Wire Line
	7550 1300 7550 1200
Wire Wire Line
	8700 4600 8700 4750
NoConn ~ 6650 4000
Wire Wire Line
	8700 4600 8700 4300
Connection ~ 8700 4600
Wire Wire Line
	8700 1200 8700 1500
Wire Wire Line
	6050 4600 6250 4600
Wire Wire Line
	5900 4600 6050 4600
Wire Wire Line
	7250 4000 8100 4000
$Comp
L Device:CP C5
U 1 1 5F37F544
P 6350 2250
F 0 "C5" H 6450 2600 50  0000 C CNN
F 1 "0.1µ" H 6400 2700 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6388 2100 50  0001 C CNN
F 3 "~" H 6350 2250 50  0001 C CNN
	1    6350 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	6950 4300 6950 4600
Connection ~ 6950 4600
Wire Wire Line
	6950 4600 8700 4600
NoConn ~ 8100 3400
NoConn ~ 8100 3300
NoConn ~ 8100 3100
NoConn ~ 9300 3400
NoConn ~ 9300 3300
NoConn ~ 9300 3200
NoConn ~ 9300 3100
NoConn ~ 9300 3000
NoConn ~ 9300 2900
NoConn ~ 8100 3000
NoConn ~ 8100 2900
NoConn ~ 8100 2800
NoConn ~ 8100 2700
NoConn ~ 8100 2600
NoConn ~ 8100 2500
NoConn ~ 8100 2400
NoConn ~ 8100 2300
NoConn ~ 8100 2200
NoConn ~ 8100 2100
Wire Wire Line
	7550 1200 8700 1200
Wire Wire Line
	6150 1200 7550 1200
Connection ~ 6150 1200
Wire Wire Line
	7550 2500 7450 2500
Connection ~ 4450 1200
Wire Wire Line
	4350 1200 4450 1200
$Comp
L Sensor_Temperature:TMP36xS U5
U 1 1 5EEF4982
P 6950 2500
F 0 "U5" H 7200 2000 50  0000 L CNN
F 1 "TMP36xS" H 7100 2100 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6950 2050 50  0001 C CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf" H 6950 2500 50  0001 C CNN
	1    6950 2500
	1    0    0    1   
$EndComp
Wire Wire Line
	6150 2500 6350 2500
Wire Wire Line
	6950 1700 6950 2000
Wire Wire Line
	6950 1700 7050 1700
Wire Wire Line
	6950 2000 6350 2000
Wire Wire Line
	6350 2000 6350 2100
Connection ~ 6950 2000
Wire Wire Line
	6950 2000 6950 2100
Wire Wire Line
	6350 2400 6350 2500
Connection ~ 6350 2500
Wire Wire Line
	6350 2500 6450 2500
Wire Wire Line
	6250 4600 6950 4600
Wire Wire Line
	3950 2400 4450 2400
Wire Wire Line
	4450 2300 4450 2400
$Comp
L power:+3V3 #PWR0101
U 1 1 5FB47EC7
P 8700 1050
F 0 "#PWR0101" H 8700 900 50  0001 C CNN
F 1 "+3V3" H 8715 1223 50  0000 C CNN
F 2 "" H 8700 1050 50  0001 C CNN
F 3 "" H 8700 1050 50  0001 C CNN
	1    8700 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1200 8700 1050
Connection ~ 8700 1200
Wire Wire Line
	7450 3900 8100 3900
Wire Wire Line
	7450 3100 7450 3900
Wire Wire Line
	7550 3800 8100 3800
Wire Wire Line
	7550 2500 7550 3800
NoConn ~ 8100 3700
Wire Wire Line
	4450 1200 4450 2000
$Comp
L Device:R R4
U 1 1 5FC0D009
P 5000 2350
F 0 "R4" H 5150 2250 50  0000 L CNN
F 1 "6K8" H 5100 2350 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4930 2350 50  0001 C CNN
F 3 "~" H 5000 2350 50  0001 C CNN
	1    5000 2350
	-1   0    0    1   
$EndComp
$Comp
L Sensor_Optical:LDR03 R3
U 1 1 5FC0D156
P 5000 1900
F 0 "R3" H 4650 1900 50  0000 L CNN
F 1 "LDR03" H 4650 2000 50  0000 L CNN
F 2 "OptoDevice:R_LDR_5.0x4.1mm_P3mm_Vertical" V 5175 1900 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 5000 1850 50  0001 C CNN
	1    5000 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2900 6950 3000
Wire Wire Line
	6150 2500 6150 3000
Wire Wire Line
	6150 3000 6950 3000
Connection ~ 6150 2500
Connection ~ 6950 3000
Wire Wire Line
	6950 3000 6950 3700
Wire Wire Line
	6050 3950 6050 1050
Wire Wire Line
	6050 1050 3650 1050
Wire Wire Line
	3650 1050 3650 1200
Connection ~ 6050 3950
Connection ~ 3650 1200
Wire Wire Line
	3650 1200 3750 1200
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5FD1E150
P 5700 1400
F 0 "J3" V 5900 1350 50  0000 C CNN
F 1 "Conn_01x04" V 5800 1350 50  0000 C CNN
F 2 "" H 5700 1400 50  0001 C CNN
F 3 "~" H 5700 1400 50  0001 C CNN
	1    5700 1400
	0    1    -1   0   
$EndComp
Connection ~ 6950 1700
Wire Wire Line
	7900 1900 8000 2000
Wire Wire Line
	8000 2000 8100 2000
Wire Wire Line
	5800 1700 5800 2600
Wire Wire Line
	5800 1700 6950 1700
Connection ~ 5800 2600
Wire Wire Line
	4900 4150 4850 4150
Wire Wire Line
	5500 1900 5500 1600
Wire Wire Line
	5500 1900 7900 1900
Wire Wire Line
	5600 1800 5600 1600
Wire Wire Line
	5600 1800 8100 1800
Wire Wire Line
	6150 1200 6150 2500
Connection ~ 5800 1700
Wire Wire Line
	4450 2400 4450 3200
Connection ~ 4450 2400
NoConn ~ 8100 1900
Wire Wire Line
	5000 2050 5000 2150
Wire Wire Line
	4050 2600 5000 2600
Wire Wire Line
	4450 1200 5000 1200
Wire Wire Line
	5000 2500 5000 2600
Connection ~ 5000 2600
Wire Wire Line
	5000 2600 5800 2600
Wire Wire Line
	5000 1750 5000 1700
Connection ~ 5000 1200
Wire Wire Line
	5000 1200 6150 1200
Wire Wire Line
	5000 1700 5700 1700
Connection ~ 5000 1700
Wire Wire Line
	5000 1700 5000 1200
Wire Wire Line
	5000 2150 5150 2150
Wire Wire Line
	5150 2150 5150 3100
Connection ~ 5000 2150
Wire Wire Line
	5000 2150 5000 2200
Wire Wire Line
	5150 3100 7450 3100
Wire Wire Line
	4450 3200 8100 3200
Wire Wire Line
	5700 1600 5700 1700
Wire Wire Line
	5800 1600 5800 1700
Wire Notes Line
	4550 1950 4550 2750
Wire Notes Line
	4550 2750 1900 2750
Wire Notes Line
	1900 2750 1900 1950
Wire Notes Line
	1900 1950 4550 1950
Wire Notes Line
	4600 1600 4600 2750
Wire Notes Line
	4600 2750 5300 2750
Wire Notes Line
	5300 2750 5300 1600
Wire Notes Line
	5300 1600 4600 1600
Wire Notes Line
	2400 1650 4550 1650
Wire Notes Line
	2400 1650 2400 800 
Wire Notes Line
	2400 800  4550 800 
Wire Notes Line
	4550 800  4550 1650
Wire Notes Line
	5350 2000 5950 2000
Wire Notes Line
	7000 1150 7750 1150
Wire Notes Line
	7750 1750 7000 1750
Wire Notes Line
	6100 3050 6100 1950
Wire Notes Line
	6100 1950 7500 1950
Wire Notes Line
	7500 1950 7500 3050
Wire Notes Line
	7500 3050 6100 3050
Wire Notes Line
	6500 3650 6500 4400
Wire Notes Line
	6500 4400 7400 4400
Wire Notes Line
	7400 4400 7400 3650
Wire Notes Line
	7400 3650 6500 3650
Wire Notes Line
	2500 3050 4250 3050
Wire Notes Line
	4250 3050 4250 3300
Wire Notes Line
	2500 3050 2500 4900
Wire Notes Line
	6400 3300 6400 4900
Wire Notes Line
	4250 3300 6400 3300
Wire Notes Line
	6400 4900 2500 4900
Wire Notes Line
	2100 4900 2100 4250
Wire Notes Line
	2100 4250 750  4250
Wire Notes Line
	750  4250 750  4900
Wire Notes Line
	750  4900 2100 4900
Wire Notes Line
	750  1000 1950 1000
Wire Notes Line
	7000 1750 7000 1150
Wire Notes Line
	7750 1150 7750 1750
Wire Notes Line
	5350 2000 5350 1100
Wire Notes Line
	5350 1100 5950 1100
Wire Notes Line
	5950 1100 5950 2000
Text Notes 5350 2000 0    39   ~ 0
FTDI
Text Notes 2400 1650 0    39   ~ 0
POWER SUPPLY
Text Notes 1900 2750 0    39   ~ 0
AC SENSE (ZERO CROSSING)
Text Notes 2500 4900 0    39   ~ 0
LOAD CONTROL (DIMMABLE)
Text Notes 6500 4400 0    39   ~ 0
RGB STATUS LED
Text Notes 6100 3050 0    39   ~ 0
PCB TEMP MONITOR
Text Notes 750  1550 0    39   ~ 0
LAMP SOCKET INPUT
Text Notes 750  4900 0    39   ~ 0
AC LOAD OUTPUT
Text Notes 4600 2750 0    39   ~ 0
LIGHT LEVEL SENSE
Wire Notes Line
	750  1550 1950 1550
Wire Notes Line
	1950 1000 1950 1550
Wire Notes Line
	750  1000 750  1550
Wire Notes Line
	7950 1350 9500 1350
Wire Notes Line
	9500 1350 9500 4350
Wire Notes Line
	9500 4350 7950 4350
Wire Notes Line
	7950 4350 7950 1350
Text Notes 7950 4350 0    39   ~ 0
MCU (ESP32)
NoConn ~ 9300 2000
NoConn ~ 9300 1900
NoConn ~ 9300 1700
$Comp
L Diode_Bridge_slimc:DB107-BP BR1
U 1 1 5D50CDEA
P 2850 2400
F 0 "BR1" H 3300 2665 50  0000 C CNN
F 1 "DB107-BP" H 3300 2574 50  0000 C CNN
F 2 "DIP825W56P510L828H330Q4N" H 3600 2500 50  0001 L CNN
F 3 "http://www.mccsemi.com/up_pdf/DB101-DB107(DB-1).pdf" H 3600 2400 50  0001 L CNN
F 4 "Bridge Rectifiers 1.0A 1000V" H 3600 2300 50  0001 L CNN "Description"
F 5 "3.3" H 3600 2200 50  0001 L CNN "Height"
F 6 "Micro Commercial Components (MCC)" H 3600 2100 50  0001 L CNN "Manufacturer_Name"
F 7 "DB107-BP" H 3600 2000 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "833-DB107-BP" H 3600 1900 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=833-DB107-BP" H 3600 1800 50  0001 L CNN "Mouser Price/Stock"
	1    2850 2400
	-1   0    0    -1  
$EndComp
$Comp
L AC_Drivers_slimc:FL51xxMX U4
U 1 1 5D513BFF
P 5350 3950
F 0 "U4" H 5350 4375 50  0000 C CNN
F 1 "FL51xxMX" H 5350 4284 50  0000 C CNN
F 2 "" H 5000 4350 50  0001 C CNN
F 3 "" H 5000 4350 50  0001 C CNN
	1    5350 3950
	-1   0    0    -1  
$EndComp
$EndSCHEMATC