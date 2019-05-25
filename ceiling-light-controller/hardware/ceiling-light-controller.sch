EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr User 7087 5906
encoding utf-8
Sheet 1 1
Title "Ceiling Light Controller"
Date "2019-05-09"
Rev "v01"
Comp ""
Comment1 ""
Comment2 "creativecommons.org/licenses/by/4.0"
Comment3 "License: CC BY 4.0"
Comment4 "Auther: Christian Skjerning"
$EndDescr
$Comp
L power:VAC #PWR0101
U 1 1 5CD3632C
P 1450 850
F 0 "#PWR0101" H 1450 750 50  0001 C CNN
F 1 "VAC" V 1450 1080 50  0000 L CNN
F 2 "" H 1450 850 50  0001 C CNN
F 3 "" H 1450 850 50  0001 C CNN
	1    1450 850 
	0    -1   -1   0   
$EndComp
$Comp
L power:VAC #PWR0102
U 1 1 5CD3634E
P 1350 1450
F 0 "#PWR0102" H 1350 1350 50  0001 C CNN
F 1 "VAC" V 1350 1680 50  0000 L CNN
F 2 "" H 1350 1450 50  0001 C CNN
F 3 "" H 1350 1450 50  0001 C CNN
	1    1350 1450
	0    -1   -1   0   
$EndComp
$Comp
L power:NEUT #PWR0103
U 1 1 5CD365F4
P 1350 1600
F 0 "#PWR0103" H 1350 1450 50  0001 C CNN
F 1 "NEUT" V 1368 1728 50  0000 L CNN
F 2 "" H 1350 1600 50  0001 C CNN
F 3 "" H 1350 1600 50  0001 C CNN
	1    1350 1600
	0    -1   -1   0   
$EndComp
$Comp
L Isolator:LTV-817 U1
U 1 1 5CD36A1B
P 3450 1150
F 0 "U1" H 3450 1475 50  0000 C CNN
F 1 "LTV-817" H 3450 1384 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 3250 950 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 3450 1050 50  0001 L CNN
	1    3450 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5CD372F6
P 4600 1200
F 0 "R2" V 4807 1200 50  0000 C CNN
F 1 "10k" V 4716 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4530 1200 50  0001 C CNN
F 3 "~" H 4600 1200 50  0001 C CNN
	1    4600 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5CD373D6
P 2850 1050
F 0 "R1" V 2650 1050 50  0000 C CNN
F 1 "390k" V 2734 1050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 2780 1050 50  0001 C CNN
F 3 "~" H 2850 1050 50  0001 C CNN
	1    2850 1050
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5CD377FE
P 1800 2450
F 0 "R4" H 1870 2496 50  0000 L CNN
F 1 "100" H 1870 2405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 1730 2450 50  0001 C CNN
F 3 "~" H 1800 2450 50  0001 C CNN
	1    1800 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5CD379B5
P 2800 2450
F 0 "R3" V 3007 2450 50  0000 C CNN
F 1 "10k" V 2916 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 2730 2450 50  0001 C CNN
F 3 "~" H 2800 2450 50  0001 C CNN
	1    2800 2450
	0    -1   -1   0   
$EndComp
$Comp
L Triac_Thyristor:BT136-500 Q1
U 1 1 5CD37C89
P 2450 2650
F 0 "Q1" H 2579 2696 50  0000 L CNN
F 1 "BT136-500" H 2579 2605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2650 2575 50  0001 L CIN
F 3 "http://www.micropik.com/PDF/BT136-600.pdf" H 2450 2650 50  0001 L CNN
	1    2450 2650
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5CD37ECE
P 1800 2850
F 0 "C5" H 1915 2896 50  0000 L CNN
F 1 "100nf" H 1915 2805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Axial_L10.0mm_D4.5mm_P15.00mm_Horizontal" H 1838 2700 50  0001 C CNN
F 3 "~" H 1800 2850 50  0001 C CNN
	1    1800 2850
	1    0    0    -1  
$EndComp
$Comp
L power:VAC #PWR0104
U 1 1 5CD3818E
P 1550 3200
F 0 "#PWR0104" H 1550 3100 50  0001 C CNN
F 1 "VAC" V 1550 3430 50  0000 L CNN
F 2 "" H 1550 3200 50  0001 C CNN
F 3 "" H 1550 3200 50  0001 C CNN
	1    1550 3200
	0    -1   -1   0   
$EndComp
$Comp
L Relay_SolidState:MOC3021M U3
U 1 1 5CD39FB5
P 3400 2650
F 0 "U3" H 3400 2975 50  0000 C CNN
F 1 "MOC3021M" H 3400 2884 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 3200 2450 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/MO/MOC3020M.pdf" H 3375 2650 50  0001 L CNN
	1    3400 2650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3000 1050 3150 1050
$Comp
L Device:CP C1
U 1 1 5CD3CE67
P 4100 1200
F 0 "C1" H 4218 1246 50  0000 L CNN
F 1 "1µf" H 4218 1155 50  0000 L CNN
F 2 "Capacitor_THT:CP_Axial_L10.0mm_D4.5mm_P15.00mm_Horizontal" H 4138 1050 50  0001 C CNN
F 3 "~" H 4100 1200 50  0001 C CNN
	1    4100 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5CD3CE6E
P 4100 1450
F 0 "#PWR0106" H 4100 1200 50  0001 C CNN
F 1 "GND" H 4105 1277 50  0000 C CNN
F 2 "" H 4100 1450 50  0001 C CNN
F 3 "" H 4100 1450 50  0001 C CNN
	1    4100 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1900 5100 1900
Wire Wire Line
	5100 1700 4600 1700
Connection ~ 4100 1050
Wire Wire Line
	3750 1050 4100 1050
$Comp
L power:GND #PWR0107
U 1 1 5CD4B035
P 4750 1850
F 0 "#PWR0107" H 4750 1600 50  0001 C CNN
F 1 "GND" H 4755 1677 50  0000 C CNN
F 2 "" H 4750 1850 50  0001 C CNN
F 3 "" H 4750 1850 50  0001 C CNN
	1    4750 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2200 1800 2300
Wire Wire Line
	1800 2600 1800 2700
Wire Wire Line
	1600 3000 1650 3000
Wire Wire Line
	1800 3000 2450 3000
Wire Wire Line
	2450 3000 2450 2800
Connection ~ 1800 3000
Wire Wire Line
	1800 2200 2450 2200
Wire Wire Line
	2450 2200 2450 2450
Connection ~ 1800 2200
Wire Wire Line
	2450 2450 2650 2450
Connection ~ 2450 2450
Wire Wire Line
	2450 2450 2450 2500
Wire Wire Line
	2950 2450 3050 2450
Wire Wire Line
	3050 2450 3050 2550
Wire Wire Line
	3050 2550 3100 2550
Wire Wire Line
	3100 2750 2600 2750
$Comp
L Device:R R5
U 1 1 5CD79098
P 4000 2550
F 0 "R5" V 4207 2550 50  0000 C CNN
F 1 "330" V 4116 2550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 3930 2550 50  0001 C CNN
F 3 "~" H 4000 2550 50  0001 C CNN
	1    4000 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 2550 3850 2550
Wire Wire Line
	4150 2550 4900 2550
Wire Wire Line
	4900 2550 4900 2000
Wire Wire Line
	4900 2000 5100 2000
$Comp
L power:GND #PWR0109
U 1 1 5CD7F5B0
P 3800 2850
F 0 "#PWR0109" H 3800 2600 50  0001 C CNN
F 1 "GND" H 3805 2677 50  0000 C CNN
F 2 "" H 3800 2850 50  0001 C CNN
F 3 "" H 3800 2850 50  0001 C CNN
	1    3800 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2750 3800 2750
Wire Wire Line
	3800 2750 3800 2850
Wire Wire Line
	4600 1350 4600 1700
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5CD45A37
P 1350 1150
F 0 "J1" H 1430 1100 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 1430 1191 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 1350 1150 50  0001 C CNN
F 3 "~" H 1350 1150 50  0001 C CNN
	1    1350 1150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5CD45C5A
P 1400 2900
F 0 "J2" H 1550 2900 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 1900 2800 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1400 2900 50  0001 C CNN
F 3 "~" H 1400 2900 50  0001 C CNN
	1    1400 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1550 1150 1650 1150
Wire Wire Line
	1550 2200 1800 2200
Wire Wire Line
	1550 1250 1550 1450
Wire Wire Line
	1650 2900 1600 2900
Wire Wire Line
	1550 1450 1350 1450
Wire Wire Line
	1450 850  1650 850 
Wire Wire Line
	1650 850  1650 1050
Wire Wire Line
	1650 1050 1550 1050
Wire Wire Line
	1350 1600 1650 1600
Connection ~ 1550 1450
Connection ~ 1650 1600
Wire Wire Line
	1650 3000 1650 3200
Wire Wire Line
	1650 3200 1550 3200
Connection ~ 1650 3000
Wire Wire Line
	1650 3000 1800 3000
Wire Wire Line
	1650 1600 1650 1700
Wire Wire Line
	2600 1800 1550 1800
$Comp
L power:GND #PWR0105
U 1 1 5CEA5DBB
P 3300 1900
F 0 "#PWR0105" H 3300 1650 50  0001 C CNN
F 1 "GND" H 3305 1727 50  0000 C CNN
F 2 "" H 3300 1900 50  0001 C CNN
F 3 "" H 3300 1900 50  0001 C CNN
	1    3300 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1800 4750 1800
Wire Wire Line
	4750 1800 4750 1850
Wire Wire Line
	3200 1800 3300 1800
Wire Wire Line
	3300 1800 3300 1900
Wire Wire Line
	3200 1700 4600 1700
Wire Wire Line
	2600 1700 1650 1700
$Comp
L Power_Supplies:HLK-PM03 U2
U 1 1 5CE9C5F6
P 2900 1750
F 0 "U2" H 2900 1992 40  0000 C CNN
F 1 "HLK-PM03" H 2900 1916 40  0000 C CNN
F 2 "Power_Supply:HLK-PM01" H 2000 3100 60  0001 C CNN
F 3 "" H 2000 3100 60  0000 C CNN
	1    2900 1750
	1    0    0    -1  
$EndComp
$Comp
L wemos_mini:WeMos_mini U4
U 1 1 5CE9DED8
P 5600 2050
F 0 "U4" H 5600 2793 60  0000 C CNN
F 1 "WeMos_mini" H 5600 2687 60  0000 C CNN
F 2 "wemos-d1-mini:wemos-d1-mini-embedded" H 6150 1350 60  0001 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 5600 2581 60  0000 C CNN
	1    5600 2050
	1    0    0    -1  
$EndComp
$Comp
L DB107-BP:DB107-BP BR1
U 1 1 5CE9FEBA
P 2550 1050
F 0 "BR1" H 3000 1315 50  0000 C CNN
F 1 "DB107-BP" H 3000 1224 50  0000 C CNN
F 2 "DB107-BP:DIP825W56P510L828H330Q4N" H 3300 1150 50  0001 L CNN
F 3 "http://www.mccsemi.com/up_pdf/DB101-DB107(DB-1).pdf" H 3300 1050 50  0001 L CNN
F 4 "Bridge Rectifiers 1.0A 1000V" H 3300 950 50  0001 L CNN "Description"
F 5 "3.3" H 3300 850 50  0001 L CNN "Height"
F 6 "Micro Commercial Components (MCC)" H 3300 750 50  0001 L CNN "Manufacturer_Name"
F 7 "DB107-BP" H 3300 650 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "833-DB107-BP" H 3300 550 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=833-DB107-BP" H 3300 450 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 3300 350 50  0001 L CNN "RS Part Number"
F 11 "" H 3300 250 50  0001 L CNN "RS Price/Stock"
	1    2550 1050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1550 1450 1550 1800
Wire Wire Line
	1650 1150 1650 1600
Connection ~ 1650 1050
Connection ~ 1650 1150
Wire Wire Line
	2550 1150 2900 1150
Wire Wire Line
	2900 1150 2900 1250
Wire Wire Line
	2900 1250 3150 1250
Wire Wire Line
	2550 1050 2700 1050
Connection ~ 4600 1700
Wire Wire Line
	4100 1350 4100 1450
Connection ~ 4600 1050
Wire Wire Line
	4600 1050 4900 1050
Wire Wire Line
	4100 1050 4600 1050
Wire Wire Line
	3750 1250 3850 1250
Wire Wire Line
	3850 1250 3850 1350
Wire Wire Line
	3850 1350 4100 1350
Connection ~ 4100 1350
Connection ~ 1550 1800
Connection ~ 1650 1700
Wire Wire Line
	1550 1800 1550 2200
Wire Wire Line
	1650 1700 1650 2900
Wire Wire Line
	4900 1900 4900 1050
$EndSCHEMATC