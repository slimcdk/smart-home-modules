EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AC_Drivers:FL51xxMX U1
U 1 1 5DAD29E3
P 1550 1400
F 0 "U1" V 2300 1650 50  0000 C CNN
F 1 "FL51xxMX" V 2200 1650 50  0000 C CNN
F 2 "AC_Drivers:FL51xxMX" H 1200 1800 50  0001 C CNN
F 3 "" H 1200 1800 50  0001 C CNN
	1    1550 1400
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5DAD3048
P 2400 1400
F 0 "J2" H 2400 1850 50  0000 L CNN
F 1 "Conn_01x05" H 2200 1750 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2400 1400 50  0001 C CNN
F 3 "~" H 2400 1400 50  0001 C CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5DAD3118
P 700 1400
F 0 "J1" H 620 975 50  0000 C CNN
F 1 "Conn_01x05" H 620 1066 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 700 1400 50  0001 C CNN
F 3 "~" H 700 1400 50  0001 C CNN
	1    700  1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1350 1850 1200 1850
Wire Wire Line
	1200 1850 1200 1500
Wire Wire Line
	1200 1500 900  1500
Wire Wire Line
	1450 1850 1450 1950
Wire Wire Line
	1450 1950 1100 1950
Wire Wire Line
	1100 1950 1100 1600
Wire Wire Line
	1100 1600 900  1600
Wire Wire Line
	1550 1850 1550 2050
Wire Wire Line
	1550 2050 1000 2050
Wire Wire Line
	1000 2050 1000 1400
Wire Wire Line
	1000 1400 900  1400
Wire Wire Line
	1350 950  1200 950 
Wire Wire Line
	1200 950  1200 1300
Wire Wire Line
	1200 1300 900  1300
Wire Wire Line
	1450 950  1450 850 
Wire Wire Line
	1450 850  1100 850 
Wire Wire Line
	1100 850  1100 1200
Wire Wire Line
	1100 1200 900  1200
Wire Wire Line
	1750 1850 2000 1850
Wire Wire Line
	2000 1850 2000 1500
Wire Wire Line
	2000 1500 2200 1500
Wire Wire Line
	1650 1850 1650 1950
Wire Wire Line
	1650 1950 2100 1950
Wire Wire Line
	2100 1950 2100 1600
Wire Wire Line
	2100 1600 2200 1600
Wire Wire Line
	1750 950  2000 950 
Wire Wire Line
	2000 950  2000 1300
Wire Wire Line
	2000 1300 2200 1300
Wire Wire Line
	1650 950  1650 850 
Wire Wire Line
	1650 850  2100 850 
Wire Wire Line
	2100 850  2100 1200
Wire Wire Line
	2100 1200 2200 1200
Wire Wire Line
	1550 950  1550 750 
Wire Wire Line
	1550 750  1900 750 
Wire Wire Line
	1900 750  1900 1400
Wire Wire Line
	1900 1400 2200 1400
$EndSCHEMATC
