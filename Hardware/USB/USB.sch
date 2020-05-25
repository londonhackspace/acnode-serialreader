EESchema Schematic File Version 4
LIBS:USB-cache
EELAYER 29 0
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
L Connector:RJ45_Shielded J3
U 1 1 5D736B58
P 10200 1400
F 0 "J3" H 9870 1347 50  0000 R CNN
F 1 "RJ45_Shielded" H 9870 1438 50  0000 R CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 10200 1425 50  0001 C CNN
F 3 "~" V 10200 1425 50  0001 C CNN
	1    10200 1400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5D7220FD
P 9650 2100
F 0 "#PWR0101" H 9650 1850 50  0001 C CNN
F 1 "GND" H 9655 1927 50  0000 C CNN
F 2 "" H 9650 2100 50  0001 C CNN
F 3 "" H 9650 2100 50  0001 C CNN
	1    9650 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0102
U 1 1 5D722517
P 9650 950
F 0 "#PWR0102" H 9650 800 50  0001 C CNN
F 1 "+12V" H 9665 1123 50  0000 C CNN
F 2 "" H 9650 950 50  0001 C CNN
F 3 "" H 9650 950 50  0001 C CNN
	1    9650 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 950  9650 1400
Wire Wire Line
	9800 1400 9650 1400
Wire Wire Line
	9800 1700 9650 1700
Wire Wire Line
	9650 1700 9650 1800
Wire Wire Line
	9800 1800 9650 1800
Connection ~ 9650 1800
Wire Wire Line
	9650 1800 9650 2100
Wire Wire Line
	9800 1500 9650 1500
Wire Wire Line
	9650 1500 9650 1400
Connection ~ 9650 1400
$Comp
L Device:R R9
U 1 1 5D7237EC
P 9000 1450
F 0 "R9" H 9070 1496 50  0000 L CNN
F 1 "100R" H 9070 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8930 1450 50  0001 C CNN
F 3 "~" H 9000 1450 50  0001 C CNN
	1    9000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1600 9000 1600
Wire Wire Line
	9800 1300 9000 1300
$Comp
L ExtraParts:ISL8489EIBZ U3
U 1 1 5D7242F8
P 7600 1750
F 0 "U3" H 7600 2631 50  0000 C CNN
F 1 "ISL8489EIBZ" H 7600 2540 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 7600 1750 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/0e27/0900766b80e27986.pdf" H 7600 1750 50  0001 C CNN
	1    7600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1350 8800 1350
Wire Wire Line
	8800 1350 8800 1300
Wire Wire Line
	8800 1300 9000 1300
Connection ~ 9000 1300
Wire Wire Line
	9000 1600 8800 1600
Wire Wire Line
	8800 1600 8800 1550
Wire Wire Line
	8800 1550 8100 1550
Connection ~ 9000 1600
Wire Wire Line
	9800 1100 8400 1100
Wire Wire Line
	8400 1100 8400 1850
Wire Wire Line
	8400 1850 8100 1850
Wire Wire Line
	8100 2050 8550 2050
Wire Wire Line
	8550 2050 8550 1200
Wire Wire Line
	8550 1200 9800 1200
$Comp
L power:GND #PWR0103
U 1 1 5D729046
P 7750 2600
F 0 "#PWR0103" H 7750 2350 50  0001 C CNN
F 1 "GND" H 7755 2427 50  0000 C CNN
F 2 "" H 7750 2600 50  0001 C CNN
F 3 "" H 7750 2600 50  0001 C CNN
	1    7750 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2450 7700 2600
Wire Wire Line
	7700 2600 7750 2600
Wire Wire Line
	7800 2450 7800 2600
Wire Wire Line
	7800 2600 7750 2600
Connection ~ 7750 2600
$Comp
L power:+5V #PWR0104
U 1 1 5D729A66
P 7500 750
F 0 "#PWR0104" H 7500 600 50  0001 C CNN
F 1 "+5V" H 7515 923 50  0000 C CNN
F 2 "" H 7500 750 50  0001 C CNN
F 3 "" H 7500 750 50  0001 C CNN
	1    7500 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1050 7500 750 
$Comp
L power:GND #PWR0105
U 1 1 5D72A0B3
P 6750 1650
F 0 "#PWR0105" H 6750 1400 50  0001 C CNN
F 1 "GND" H 6755 1477 50  0000 C CNN
F 2 "" H 6750 1650 50  0001 C CNN
F 3 "" H 6750 1650 50  0001 C CNN
	1    6750 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5D72A22C
P 6800 2150
F 0 "#PWR0106" H 6800 2000 50  0001 C CNN
F 1 "+5V" H 6815 2323 50  0000 C CNN
F 2 "" H 6800 2150 50  0001 C CNN
F 3 "" H 6800 2150 50  0001 C CNN
	1    6800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1650 6750 1650
Wire Wire Line
	7100 2150 6800 2150
$Comp
L Connector:USB_B J1
U 1 1 5D72B341
P 3300 1650
F 0 "J1" H 3357 2117 50  0000 C CNN
F 1 "USB_B" H 3357 2026 50  0000 C CNN
F 2 "Connector_USB:USB_B_OST_USB-B1HSxx_Horizontal" H 3450 1600 50  0001 C CNN
F 3 " ~" H 3450 1600 50  0001 C CNN
	1    3300 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 5D72CD0F
P 4100 1300
F 0 "#PWR0107" H 4100 1150 50  0001 C CNN
F 1 "+5V" H 4115 1473 50  0000 C CNN
F 2 "" H 4100 1300 50  0001 C CNN
F 3 "" H 4100 1300 50  0001 C CNN
	1    4100 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5D72CEE4
P 3250 2200
F 0 "#PWR0108" H 3250 1950 50  0001 C CNN
F 1 "GND" H 3255 2027 50  0000 C CNN
F 2 "" H 3250 2200 50  0001 C CNN
F 3 "" H 3250 2200 50  0001 C CNN
	1    3250 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1450 4100 1300
Wire Wire Line
	3200 2050 3200 2200
Wire Wire Line
	3200 2200 3250 2200
Wire Wire Line
	3250 2200 3300 2200
Wire Wire Line
	3300 2200 3300 2050
Connection ~ 3250 2200
$Comp
L Interface_USB:FT230XS U1
U 1 1 5D730204
P 5400 1800
F 0 "U1" H 5400 2681 50  0000 C CNN
F 1 "FT230XS" H 5400 2590 50  0000 C CNN
F 2 "Package_SO:SSOP-16_3.9x4.9mm_P0.635mm" H 5850 1150 50  0001 C CNN
F 3 "http://www.ftdichip.com/Products/ICs/FT230X.html" H 5400 1800 50  0001 C CNN
	1    5400 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1400 6200 1400
Wire Wire Line
	6650 1400 6650 1950
Wire Wire Line
	6650 1950 7100 1950
Wire Wire Line
	6100 1500 6500 1500
Wire Wire Line
	6800 1500 6800 1450
Wire Wire Line
	6800 1450 6950 1450
$Comp
L power:GND #PWR0109
U 1 1 5D73507C
P 5400 2550
F 0 "#PWR0109" H 5400 2300 50  0001 C CNN
F 1 "GND" H 5405 2377 50  0000 C CNN
F 2 "" H 5400 2550 50  0001 C CNN
F 3 "" H 5400 2550 50  0001 C CNN
	1    5400 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5D735424
P 5300 850
F 0 "#PWR0110" H 5300 700 50  0001 C CNN
F 1 "+5V" H 5315 1023 50  0000 C CNN
F 2 "" H 5300 850 50  0001 C CNN
F 3 "" H 5300 850 50  0001 C CNN
	1    5300 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 850  5300 900 
Wire Wire Line
	5300 2500 5400 2500
Wire Wire Line
	5400 2500 5400 2550
Wire Wire Line
	5500 2500 5400 2500
Connection ~ 5400 2500
$Comp
L power:+3.3V #PWR0111
U 1 1 5D73CFB0
P 4650 1300
F 0 "#PWR0111" H 4650 1150 50  0001 C CNN
F 1 "+3.3V" H 4665 1473 50  0000 C CNN
F 2 "" H 4650 1300 50  0001 C CNN
F 3 "" H 4650 1300 50  0001 C CNN
	1    4650 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0112
U 1 1 5D73D758
P 5500 850
F 0 "#PWR0112" H 5500 700 50  0001 C CNN
F 1 "+3.3V" H 5515 1023 50  0000 C CNN
F 2 "" H 5500 850 50  0001 C CNN
F 3 "" H 5500 850 50  0001 C CNN
	1    5500 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1100 5500 850 
Wire Wire Line
	4700 1400 4650 1400
Wire Wire Line
	4650 1400 4650 1300
$Comp
L Regulator_Switching:MC34063AD U2
U 1 1 5D7411B2
P 6450 3850
F 0 "U2" H 6450 4317 50  0000 C CNN
F 1 "MC34063AD" H 6450 4226 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6500 3400 50  0001 L CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MC34063A-D.PDF" H 6950 3750 50  0001 C CNN
	1    6450 3850
	1    0    0    -1  
$EndComp
Text Notes 5350 4800 0    50   ~ 0
SP34063A is an alternative that uses the same pinout\n
$Comp
L power:GND #PWR0113
U 1 1 5D741BA5
P 6450 4450
F 0 "#PWR0113" H 6450 4200 50  0001 C CNN
F 1 "GND" H 6455 4277 50  0000 C CNN
F 2 "" H 6450 4450 50  0001 C CNN
F 3 "" H 6450 4450 50  0001 C CNN
	1    6450 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5D74274B
P 5800 3650
F 0 "#PWR0114" H 5800 3500 50  0001 C CNN
F 1 "+5V" H 5815 3823 50  0000 C CNN
F 2 "" H 5800 3650 50  0001 C CNN
F 3 "" H 5800 3650 50  0001 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3650 5950 3650
Wire Wire Line
	6450 4450 6450 4350
$Comp
L Device:C C5
U 1 1 5D744FDC
P 5550 4200
F 0 "C5" H 5665 4246 50  0000 L CNN
F 1 "1n5" H 5665 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5588 4050 50  0001 C CNN
F 3 "~" H 5550 4200 50  0001 C CNN
	1    5550 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4050 5550 4050
Wire Wire Line
	5550 4350 6450 4350
Connection ~ 6450 4350
$Comp
L Device:R R4
U 1 1 5D74C9F3
P 6450 3250
F 0 "R4" V 6243 3250 50  0000 C CNN
F 1 "0R22" V 6334 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 3250 50  0001 C CNN
F 3 "~" H 6450 3250 50  0001 C CNN
	1    6450 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3250 5950 3250
Wire Wire Line
	5950 3250 5950 3650
Connection ~ 5950 3650
Wire Wire Line
	5950 3650 5800 3650
Wire Wire Line
	6850 3650 6850 3250
Wire Wire Line
	6850 3250 6600 3250
$Comp
L Device:R R7
U 1 1 5D752125
P 7250 3750
F 0 "R7" V 7043 3750 50  0000 C CNN
F 1 "180R" V 7134 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7180 3750 50  0001 C CNN
F 3 "~" H 7250 3750 50  0001 C CNN
	1    7250 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 3750 7100 3750
Wire Wire Line
	7400 3750 7400 3250
Wire Wire Line
	7400 3250 6850 3250
Connection ~ 6850 3250
$Comp
L Device:L L1
U 1 1 5D757B42
P 7250 3850
F 0 "L1" V 7100 3850 50  0000 C CNN
F 1 "180uH" V 7200 3850 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H8mm" H 7250 3850 50  0001 C CNN
F 3 "~" H 7250 3850 50  0001 C CNN
	1    7250 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6850 3850 7000 3850
Wire Wire Line
	7400 3850 7400 3750
Connection ~ 7400 3750
$Comp
L power:GND #PWR0115
U 1 1 5D75D1B2
P 7000 4550
F 0 "#PWR0115" H 7000 4300 50  0001 C CNN
F 1 "GND" H 7005 4377 50  0000 C CNN
F 2 "" H 7000 4550 50  0001 C CNN
F 3 "" H 7000 4550 50  0001 C CNN
	1    7000 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4050 6850 4050
$Comp
L Diode:1N5819 D1
U 1 1 5D75F5E7
P 7650 3950
F 0 "D1" H 7650 3734 50  0000 C CNN
F 1 "1N5819" H 7650 3825 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 7650 3775 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 7650 3950 50  0001 C CNN
	1    7650 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	7000 3850 7000 3950
Wire Wire Line
	7000 3950 7500 3950
Connection ~ 7000 3850
Wire Wire Line
	7000 3850 7100 3850
$Comp
L Device:R R8
U 1 1 5D764373
P 8000 4100
F 0 "R8" H 8070 4146 50  0000 L CNN
F 1 "24k" H 8070 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7930 4100 50  0001 C CNN
F 3 "~" H 8000 4100 50  0001 C CNN
	1    8000 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5D766610
P 7200 4300
F 0 "R6" H 7130 4254 50  0000 R CNN
F 1 "2k7" H 7130 4345 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7130 4300 50  0001 C CNN
F 3 "~" H 7200 4300 50  0001 C CNN
	1    7200 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	7000 4050 7000 4450
Wire Wire Line
	7200 4450 7000 4450
Connection ~ 7000 4450
Wire Wire Line
	7000 4450 7000 4550
Wire Wire Line
	6850 4150 7200 4150
Wire Wire Line
	8000 4250 7400 4250
Wire Wire Line
	7400 4250 7400 4150
Wire Wire Line
	7400 4150 7200 4150
Connection ~ 7200 4150
Wire Wire Line
	7800 3950 8000 3950
$Comp
L power:+12V #PWR0116
U 1 1 5D771B2B
P 8300 3850
F 0 "#PWR0116" H 8300 3700 50  0001 C CNN
F 1 "+12V" H 8315 4023 50  0000 C CNN
F 2 "" H 8300 3850 50  0001 C CNN
F 3 "" H 8300 3850 50  0001 C CNN
	1    8300 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3950 8300 3950
Wire Wire Line
	8300 3950 8300 3850
Connection ~ 8000 3950
$Comp
L Device:R R1
U 1 1 5D792A4A
P 4200 1650
F 0 "R1" V 3993 1650 50  0000 C CNN
F 1 "27R" V 4084 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 1650 50  0001 C CNN
F 3 "~" H 4200 1650 50  0001 C CNN
	1    4200 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5D7930FB
P 4200 1950
F 0 "R2" V 4407 1950 50  0000 C CNN
F 1 "27R" V 4316 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 1950 50  0001 C CNN
F 3 "~" H 4200 1950 50  0001 C CNN
	1    4200 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 1650 4400 1650
Wire Wire Line
	4400 1650 4400 1800
Wire Wire Line
	4400 1800 4700 1800
Wire Wire Line
	4050 1750 4050 1950
Wire Wire Line
	4350 1950 4550 1950
Wire Wire Line
	4550 1950 4550 1700
Wire Wire Line
	4550 1700 4700 1700
$Comp
L power:+3.3V #PWR0117
U 1 1 5D79CB51
P 4450 2200
F 0 "#PWR0117" H 4450 2050 50  0001 C CNN
F 1 "+3.3V" H 4465 2373 50  0000 C CNN
F 2 "" H 4450 2200 50  0001 C CNN
F 3 "" H 4450 2200 50  0001 C CNN
	1    4450 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2200 4550 2200
Wire Wire Line
	4700 2200 4700 2000
$Comp
L Device:C C3
U 1 1 5D79F8BF
P 4750 2500
F 0 "C3" V 4498 2500 50  0000 C CNN
F 1 "100n" V 4589 2500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4788 2350 50  0001 C CNN
F 3 "~" H 4750 2500 50  0001 C CNN
	1    4750 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 2500 5300 2500
Connection ~ 5300 2500
Wire Wire Line
	4550 2200 4550 2500
Wire Wire Line
	4550 2500 4600 2500
Connection ~ 4550 2200
Wire Wire Line
	4550 2200 4700 2200
NoConn ~ 6100 1600
NoConn ~ 6100 1700
NoConn ~ 6100 1900
NoConn ~ 6100 2000
NoConn ~ 6100 2100
NoConn ~ 6100 2200
$Comp
L Device:R R3
U 1 1 5D7B640B
P 6200 1000
F 0 "R3" H 6270 1046 50  0000 L CNN
F 1 "10k" H 6270 955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6130 1000 50  0001 C CNN
F 3 "~" H 6200 1000 50  0001 C CNN
	1    6200 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5D7B6BAE
P 6500 1000
F 0 "R5" H 6570 1046 50  0000 L CNN
F 1 "10k" H 6570 955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6430 1000 50  0001 C CNN
F 3 "~" H 6500 1000 50  0001 C CNN
	1    6500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1150 6200 1400
Connection ~ 6200 1400
Wire Wire Line
	6200 1400 6650 1400
Wire Wire Line
	6500 1150 6500 1500
Connection ~ 6500 1500
Wire Wire Line
	6500 1500 6800 1500
$Comp
L power:+3.3V #PWR0118
U 1 1 5D7BCDC5
P 6350 750
F 0 "#PWR0118" H 6350 600 50  0001 C CNN
F 1 "+3.3V" H 6365 923 50  0000 C CNN
F 2 "" H 6350 750 50  0001 C CNN
F 3 "" H 6350 750 50  0001 C CNN
	1    6350 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 850  6200 750 
Wire Wire Line
	6200 750  6350 750 
Wire Wire Line
	6350 750  6500 750 
Wire Wire Line
	6500 750  6500 850 
Connection ~ 6350 750 
$Comp
L Device:C C4
U 1 1 5D7C397A
P 4900 900
F 0 "C4" V 4648 900 50  0000 C CNN
F 1 "100n" V 4739 900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4938 750 50  0001 C CNN
F 3 "~" H 4900 900 50  0001 C CNN
	1    4900 900 
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5D7C42B1
P 4450 900
F 0 "#PWR0119" H 4450 650 50  0001 C CNN
F 1 "GND" H 4455 727 50  0000 C CNN
F 2 "" H 4450 900 50  0001 C CNN
F 3 "" H 4450 900 50  0001 C CNN
	1    4450 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 900  5300 900 
Connection ~ 5300 900 
Wire Wire Line
	5300 900  5300 1100
Wire Wire Line
	4750 900  4450 900 
$Comp
L Device:C C2
U 1 1 5D7CB39C
P 3900 2150
F 0 "C2" H 4015 2196 50  0000 L CNN
F 1 "47pF" H 4015 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3938 2000 50  0001 C CNN
F 3 "~" H 3900 2150 50  0001 C CNN
	1    3900 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5D7CBEA8
P 3750 2400
F 0 "C1" H 3865 2446 50  0000 L CNN
F 1 "47pF" H 3865 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3788 2250 50  0001 C CNN
F 3 "~" H 3750 2400 50  0001 C CNN
	1    3750 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1450 4100 1450
Wire Wire Line
	3600 1650 3750 1650
Wire Wire Line
	3600 1750 3900 1750
Wire Wire Line
	3750 2250 3750 1650
Connection ~ 3750 1650
Wire Wire Line
	3750 1650 4050 1650
Wire Wire Line
	3900 2000 3900 1750
Connection ~ 3900 1750
Wire Wire Line
	3900 1750 4050 1750
$Comp
L power:GND #PWR0120
U 1 1 5D7E3D1F
P 3850 2750
F 0 "#PWR0120" H 3850 2500 50  0001 C CNN
F 1 "GND" H 3855 2577 50  0000 C CNN
F 2 "" H 3850 2750 50  0001 C CNN
F 3 "" H 3850 2750 50  0001 C CNN
	1    3850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2550 3750 2750
Wire Wire Line
	3750 2750 3850 2750
Wire Wire Line
	3900 2300 3900 2750
Wire Wire Line
	3900 2750 3850 2750
Connection ~ 3850 2750
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5D7EC30D
P 6550 2850
F 0 "J2" V 6704 2562 50  0000 R CNN
F 1 "Conn_01x04_Male" V 6613 2562 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6550 2850 50  0001 C CNN
F 3 "~" H 6550 2850 50  0001 C CNN
	1    6550 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 1950 6550 1950
Wire Wire Line
	6550 1950 6550 2650
Connection ~ 6650 1950
Wire Wire Line
	6650 2650 6650 2250
Wire Wire Line
	6650 2250 6950 2250
Wire Wire Line
	6950 2250 6950 1450
Connection ~ 6950 1450
Wire Wire Line
	6950 1450 7100 1450
Wire Wire Line
	6750 2650 6750 2600
Wire Wire Line
	6750 2600 7700 2600
Connection ~ 7700 2600
Wire Wire Line
	6450 2650 6450 2150
Wire Wire Line
	6450 2150 6800 2150
Connection ~ 6800 2150
Text Label 3750 1650 0    50   ~ 0
USB_D+
Text Label 3600 1750 0    50   ~ 0
USB_D-
Text Label 9800 1300 0    50   ~ 0
RX+
Text Label 9800 1600 0    50   ~ 0
RX-
Text Label 9800 1100 0    50   ~ 0
TX+
Text Label 8550 1200 0    50   ~ 0
TX-
$Comp
L Device:CP C6
U 1 1 5D799F49
P 8550 4100
F 0 "C6" H 8668 4146 50  0000 L CNN
F 1 "470uF" H 8668 4055 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 8588 3950 50  0001 C CNN
F 3 "~" H 8550 4100 50  0001 C CNN
	1    8550 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4550 8550 4550
Wire Wire Line
	8550 4550 8550 4250
Connection ~ 7000 4550
Wire Wire Line
	8300 3850 8550 3850
Wire Wire Line
	8550 3850 8550 3950
Connection ~ 8300 3850
$EndSCHEMATC