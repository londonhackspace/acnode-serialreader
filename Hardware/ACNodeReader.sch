EESchema Schematic File Version 4
EELAYER 30 0
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
L power:+5V #PWR0101
U 1 1 5D3CD45D
P 3450 1850
F 0 "#PWR0101" H 3450 1700 50  0001 C CNN
F 1 "+5V" H 3465 2023 50  0000 C CNN
F 2 "" H 3450 1850 50  0001 C CNN
F 3 "" H 3450 1850 50  0001 C CNN
	1    3450 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D3CDAED
P 3450 5500
F 0 "#PWR0102" H 3450 5250 50  0001 C CNN
F 1 "GND" H 3455 5327 50  0000 C CNN
F 2 "" H 3450 5500 50  0001 C CNN
F 3 "" H 3450 5500 50  0001 C CNN
	1    3450 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2150 3550 1850
Wire Wire Line
	3550 1850 3450 1850
Wire Wire Line
	3450 5150 3450 5500
Wire Wire Line
	3450 1850 3450 2150
Connection ~ 3450 1850
Wire Wire Line
	3450 1850 2500 1850
Wire Wire Line
	2500 1850 2500 2450
Wire Wire Line
	2500 2450 2850 2450
$Comp
L Regulator_Linear:L78L05_SOT89 U1
U 1 1 5D3D7904
P 2050 1150
F 0 "U1" H 2050 1392 50  0000 C CNN
F 1 "L78L05_SOT89" H 2050 1301 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 2050 1350 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/15/55/e5/aa/23/5b/43/fd/CD00000446.pdf/files/CD00000446.pdf/jcr:content/translations/en.CD00000446.pdf" H 2050 1100 50  0001 C CNN
	1    2050 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5D3D8510
P 2050 1800
F 0 "#PWR0103" H 2050 1550 50  0001 C CNN
F 1 "GND" H 2055 1627 50  0000 C CNN
F 2 "" H 2050 1800 50  0001 C CNN
F 3 "" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0104
U 1 1 5D3D8CA0
P 1300 1050
F 0 "#PWR0104" H 1300 900 50  0001 C CNN
F 1 "+12V" H 1315 1223 50  0000 C CNN
F 2 "" H 1300 1050 50  0001 C CNN
F 3 "" H 1300 1050 50  0001 C CNN
	1    1300 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5D3D9614
P 2750 1050
F 0 "#PWR0105" H 2750 900 50  0001 C CNN
F 1 "+5V" H 2765 1223 50  0000 C CNN
F 2 "" H 2750 1050 50  0001 C CNN
F 3 "" H 2750 1050 50  0001 C CNN
	1    2750 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1050 1300 1150
Wire Wire Line
	2750 1150 2750 1050
Wire Wire Line
	2050 1800 2050 1500
Wire Wire Line
	2750 1200 2750 1150
Connection ~ 2750 1150
Wire Wire Line
	2750 1500 2050 1500
Connection ~ 2050 1500
Wire Wire Line
	2050 1500 2050 1450
Wire Wire Line
	1300 1200 1300 1150
Connection ~ 1300 1150
Wire Wire Line
	4050 4250 4600 4250
Text Label 4300 4150 0    50   ~ 0
uC_RX
Text Label 4300 4250 0    50   ~ 0
uC_TX
Text Label 4250 3850 0    50   ~ 0
i2c_SCL
$Comp
L Device:C C4
U 1 1 5D3E19F3
P 5250 2800
F 0 "C4" H 5365 2846 50  0000 L CNN
F 1 "22pF" H 5365 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5288 2650 50  0001 C CNN
F 3 "~" H 5250 2800 50  0001 C CNN
	1    5250 2800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D3E4493
P 5900 3900
F 0 "#PWR0106" H 5900 3650 50  0001 C CNN
F 1 "GND" H 5905 3727 50  0000 C CNN
F 2 "" H 5900 3900 50  0001 C CNN
F 3 "" H 5900 3900 50  0001 C CNN
	1    5900 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4150 6100 4200
Wire Wire Line
	4600 4700 4600 4250
$Comp
L power:+5V #PWR0107
U 1 1 5D3EBD13
P 6500 3600
F 0 "#PWR0107" H 6500 3450 50  0001 C CNN
F 1 "+5V" H 6515 3773 50  0000 C CNN
F 2 "" H 6500 3600 50  0001 C CNN
F 3 "" H 6500 3600 50  0001 C CNN
	1    6500 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5D3EBF5A
P 6700 5400
F 0 "#PWR0108" H 6700 5150 50  0001 C CNN
F 1 "GND" H 6705 5227 50  0000 C CNN
F 2 "" H 6700 5400 50  0001 C CNN
F 3 "" H 6700 5400 50  0001 C CNN
	1    6700 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5200 6700 5300
Wire Wire Line
	6700 5300 6800 5300
Wire Wire Line
	6800 5300 6800 5200
Connection ~ 6700 5300
Wire Wire Line
	6700 5300 6700 5400
$Comp
L power:GND #PWR0109
U 1 1 5D3EE6D8
P 5900 4450
F 0 "#PWR0109" H 5900 4200 50  0001 C CNN
F 1 "GND" H 5905 4277 50  0000 C CNN
F 2 "" H 5900 4450 50  0001 C CNN
F 3 "" H 5900 4450 50  0001 C CNN
	1    5900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5D3EEC39
P 5950 4900
F 0 "#PWR0110" H 5950 4750 50  0001 C CNN
F 1 "+5V" H 5850 5000 50  0000 C CNN
F 2 "" H 5950 4900 50  0001 C CNN
F 3 "" H 5950 4900 50  0001 C CNN
	1    5950 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4400 5900 4400
Wire Wire Line
	5900 4400 5900 4450
Wire Wire Line
	6100 4900 5950 4900
$Comp
L Device:R R3
U 1 1 5D3F0A2D
P 7500 4200
F 0 "R3" H 7570 4246 50  0000 L CNN
F 1 "100R" H 7570 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 4200 50  0001 C CNN
F 3 "~" H 7500 4200 50  0001 C CNN
	1    7500 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4100 7350 4100
Wire Wire Line
	7350 4100 7350 4050
Wire Wire Line
	7350 4050 7500 4050
Wire Wire Line
	7500 4350 7350 4350
Wire Wire Line
	7350 4350 7350 4300
Wire Wire Line
	7350 4300 7100 4300
$Comp
L Device:C C3
U 1 1 5D3F39AC
P 3700 1850
F 0 "C3" V 3448 1850 50  0000 C CNN
F 1 "100n" V 3539 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3738 1700 50  0001 C CNN
F 3 "~" H 3700 1850 50  0001 C CNN
	1    3700 1850
	0    1    1    0   
$EndComp
Connection ~ 3550 1850
$Comp
L power:GND #PWR0111
U 1 1 5D3F6DA8
P 3950 1950
F 0 "#PWR0111" H 3950 1700 50  0001 C CNN
F 1 "GND" H 3955 1777 50  0000 C CNN
F 2 "" H 3950 1950 50  0001 C CNN
F 3 "" H 3950 1950 50  0001 C CNN
	1    3950 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1950 3950 1850
Wire Wire Line
	3950 1850 3850 1850
$Comp
L Device:R R1
U 1 1 5D3F838B
P 6750 2000
F 0 "R1" H 6820 2046 50  0000 L CNN
F 1 "10k" H 6820 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6680 2000 50  0001 C CNN
F 3 "~" H 6750 2000 50  0001 C CNN
	1    6750 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5D3F9053
P 6850 1750
F 0 "R2" H 6920 1796 50  0000 L CNN
F 1 "10k" H 6920 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6780 1750 50  0001 C CNN
F 3 "~" H 6850 1750 50  0001 C CNN
	1    6850 1750
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5D3FCC1C
P 5650 3850
F 0 "#PWR0112" H 5650 3700 50  0001 C CNN
F 1 "+5V" H 5750 3900 50  0000 C CNN
F 2 "" H 5650 3850 50  0001 C CNN
F 3 "" H 5650 3850 50  0001 C CNN
	1    5650 3850
	1    0    0    -1  
$EndComp
$Comp
L ExtraParts:ISL8489EIBZ U3
U 1 1 5D3DCFE1
P 6600 4500
F 0 "U3" H 6600 5381 50  0000 C CNN
F 1 "ISL8489EIBZ" H 6750 5100 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6600 4500 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/0e27/0900766b80e27986.pdf" H 6600 4500 50  0001 C CNN
	1    6600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3600 6500 3800
Wire Wire Line
	7500 4050 7750 4050
Wire Wire Line
	7750 4050 7750 4100
Wire Wire Line
	7750 4100 8450 4100
Connection ~ 7500 4050
Wire Wire Line
	7500 4350 7800 4350
Wire Wire Line
	7800 4350 7800 4200
Wire Wire Line
	7800 4200 8450 4200
Connection ~ 7500 4350
Wire Wire Line
	7100 4600 7850 4600
Wire Wire Line
	7850 4600 7850 4300
Wire Wire Line
	7850 4300 8450 4300
Wire Wire Line
	7100 4800 7950 4800
Wire Wire Line
	7950 4800 7950 4600
Wire Wire Line
	7950 4600 8450 4600
$Comp
L power:GND #PWR0113
U 1 1 5D3ED1BC
P 8350 4900
F 0 "#PWR0113" H 8350 4650 50  0001 C CNN
F 1 "GND" H 8355 4727 50  0000 C CNN
F 2 "" H 8350 4900 50  0001 C CNN
F 3 "" H 8350 4900 50  0001 C CNN
	1    8350 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0114
U 1 1 5D3EDCDA
P 8350 4000
F 0 "#PWR0114" H 8350 3850 50  0001 C CNN
F 1 "+12V" H 8365 4173 50  0000 C CNN
F 2 "" H 8350 4000 50  0001 C CNN
F 3 "" H 8350 4000 50  0001 C CNN
	1    8350 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4000 8350 4400
Wire Wire Line
	8350 4500 8450 4500
Wire Wire Line
	8450 4400 8350 4400
Connection ~ 8350 4400
Wire Wire Line
	8350 4400 8350 4500
Wire Wire Line
	8450 4700 8350 4700
Wire Wire Line
	8350 4700 8350 4800
Wire Wire Line
	8450 4800 8350 4800
Connection ~ 8350 4800
Wire Wire Line
	8350 4800 8350 4900
Text Label 7750 4100 0    50   ~ 0
RX+
Text Label 7800 4200 0    50   ~ 0
RX-
Text Label 7100 4600 0    50   ~ 0
TX+
Text Label 7100 4800 0    50   ~ 0
TX-
$Comp
L Device:C C6
U 1 1 5D457A84
P 6300 3800
F 0 "C6" V 6048 3800 50  0000 C CNN
F 1 "100n" V 6139 3800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6338 3650 50  0001 C CNN
F 3 "~" H 6300 3800 50  0001 C CNN
	1    6300 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 3800 6100 3800
$Comp
L Device:C C5
U 1 1 5D3E2FBD
P 5600 3150
F 0 "C5" H 5715 3196 50  0000 L CNN
F 1 "22pF" H 5715 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5638 3000 50  0001 C CNN
F 3 "~" H 5600 3150 50  0001 C CNN
	1    5600 3150
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5D47849B
P 5500 3950
F 0 "R4" H 5570 3996 50  0000 L CNN
F 1 "10k" H 5570 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5430 3950 50  0001 C CNN
F 3 "~" H 5500 3950 50  0001 C CNN
	1    5500 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 3000 5100 2800
Wire Wire Line
	5450 3200 5450 3150
Wire Wire Line
	6450 3800 6500 3800
Connection ~ 6500 3800
Wire Wire Line
	5900 3900 5900 3800
Wire Wire Line
	5400 2800 5750 2800
Wire Wire Line
	5750 2800 5750 2950
Wire Wire Line
	6100 2950 6100 3800
Connection ~ 5750 2950
Wire Wire Line
	5750 2950 5750 3150
$Comp
L ACNodeReader-rescue:AVR-ISP-6-Connector J2
U 1 1 5D4A869B
P 5300 2100
F 0 "J2" V 4975 2150 50  0000 C CNN
F 1 "AVR-ISP-6" V 4884 2150 50  0000 C CNN
F 2 "Tag-Connect:TC2030-MCP-NL" V 5050 2150 50  0001 C CNN
F 3 " ~" H 4025 1550 50  0001 C CNN
	1    5300 2100
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0115
U 1 1 5D4ABCDC
P 5300 2600
F 0 "#PWR0115" H 5300 2450 50  0001 C CNN
F 1 "+5V" H 5315 2773 50  0000 C CNN
F 2 "" H 5300 2600 50  0001 C CNN
F 3 "" H 5300 2600 50  0001 C CNN
	1    5300 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5D4AC69A
P 5550 1700
F 0 "#PWR0116" H 5550 1450 50  0001 C CNN
F 1 "GND" H 5555 1527 50  0000 C CNN
F 2 "" H 5550 1700 50  0001 C CNN
F 3 "" H 5550 1700 50  0001 C CNN
	1    5550 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 1700 5400 1700
Wire Wire Line
	5400 2600 5300 2600
Wire Wire Line
	4050 2850 4850 2850
Wire Wire Line
	4850 2850 4850 2300
Wire Wire Line
	4850 2300 4900 2300
Wire Wire Line
	4300 2200 4300 2750
Wire Wire Line
	4300 2750 4050 2750
$Comp
L Connector:Conn_01x04_Female J3
U 1 1 5D4D0511
P 5000 5250
F 0 "J3" V 4846 5398 50  0000 L CNN
F 1 "Conn_01x04_Female" V 4937 5398 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5000 5250 50  0001 C CNN
F 3 "~" H 5000 5250 50  0001 C CNN
	1    5000 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 3850 5100 5050
Wire Wire Line
	5000 5050 5000 3750
$Comp
L power:GND #PWR0117
U 1 1 5D4DA5A4
P 4500 5100
F 0 "#PWR0117" H 4500 4850 50  0001 C CNN
F 1 "GND" H 4505 4927 50  0000 C CNN
F 2 "" H 4500 5100 50  0001 C CNN
F 3 "" H 4500 5100 50  0001 C CNN
	1    4500 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 5D4DAEFE
P 4900 4900
F 0 "#PWR0118" H 4900 4750 50  0001 C CNN
F 1 "+5V" H 4915 5073 50  0000 C CNN
F 2 "" H 4900 4900 50  0001 C CNN
F 3 "" H 4900 4900 50  0001 C CNN
	1    4900 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4800 4900 4900
Wire Wire Line
	4800 5050 4800 4950
Wire Wire Line
	4800 4950 4500 4950
Wire Wire Line
	4500 4950 4500 5100
$Comp
L Device:C C8
U 1 1 5D4E713D
P 2500 2700
F 0 "C8" H 2615 2746 50  0000 L CNN
F 1 "100nF" H 2615 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2538 2550 50  0001 C CNN
F 3 "~" H 2500 2700 50  0001 C CNN
	1    2500 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5D4E7F9F
P 2500 3050
F 0 "#PWR0119" H 2500 2800 50  0001 C CNN
F 1 "GND" H 2505 2877 50  0000 C CNN
F 2 "" H 2500 3050 50  0001 C CNN
F 3 "" H 2500 3050 50  0001 C CNN
	1    2500 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2550 2500 2450
Connection ~ 2500 2450
Wire Wire Line
	2500 2850 2500 3050
Text Label 4250 3750 0    50   ~ 0
i2c_SDA
Wire Wire Line
	4250 2950 4050 2950
Wire Wire Line
	4250 2100 4250 2950
Wire Wire Line
	4050 3850 5100 3850
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 5D569267
P 2150 2650
F 0 "J5" H 2150 2500 50  0000 L CNN
F 1 "Conn_01x04_Female" H 1850 2400 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 2150 2650 50  0001 C CNN
F 3 "~" H 2150 2650 50  0001 C CNN
	1    2150 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1850 7100 1850
Wire Wire Line
	7100 1850 7100 2000
Wire Wire Line
	7150 1750 7000 1750
$Comp
L power:GND #PWR0123
U 1 1 5D4B559B
P 7550 2650
F 0 "#PWR0123" H 7550 2400 50  0001 C CNN
F 1 "GND" H 7555 2477 50  0000 C CNN
F 2 "" H 7550 2650 50  0001 C CNN
F 3 "" H 7550 2650 50  0001 C CNN
	1    7550 2650
	1    0    0    -1  
$EndComp
NoConn ~ 7150 1650
$Comp
L Device:C C9
U 1 1 5D4CF21B
P 8500 1850
F 0 "C9" H 8615 1896 50  0000 L CNN
F 1 "100nF" H 8615 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8538 1700 50  0001 C CNN
F 3 "~" H 8500 1850 50  0001 C CNN
	1    8500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2000 7100 2000
Wire Wire Line
	4050 3750 5000 3750
$Comp
L power:+5V #PWR0124
U 1 1 5D660D0B
P 6400 1600
F 0 "#PWR0124" H 6400 1450 50  0001 C CNN
F 1 "+5V" H 6415 1773 50  0000 C CNN
F 2 "" H 6400 1600 50  0001 C CNN
F 3 "" H 6400 1600 50  0001 C CNN
	1    6400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1750 6400 1750
Wire Wire Line
	6400 1750 6400 1600
Wire Wire Line
	6600 2000 6400 2000
Wire Wire Line
	6400 2000 6400 1750
Connection ~ 6400 1750
$Comp
L Device:R R5
U 1 1 5D6CB022
P 1650 2550
F 0 "R5" V 1700 2700 50  0000 C CNN
F 1 "1K" V 1650 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1580 2550 50  0001 C CNN
F 3 "~" H 1650 2550 50  0001 C CNN
	1    1650 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5D6CBBDE
P 1650 2700
F 0 "R6" V 1700 2850 50  0000 C CNN
F 1 "1K" V 1650 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1580 2700 50  0001 C CNN
F 3 "~" H 1650 2700 50  0001 C CNN
	1    1650 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5D6CD1FE
P 1650 2800
F 0 "R7" V 1700 2950 50  0000 C CNN
F 1 "1K" V 1650 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1580 2800 50  0001 C CNN
F 3 "~" H 1650 2800 50  0001 C CNN
	1    1650 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 2700 1950 2750
Wire Wire Line
	1950 2800 1950 2850
Wire Wire Line
	4050 4850 4200 4850
$Comp
L power:+5V #PWR0125
U 1 1 5D7BB6A8
P 3150 5900
F 0 "#PWR0125" H 3150 5750 50  0001 C CNN
F 1 "+5V" H 3165 6073 50  0000 C CNN
F 2 "" H 3150 5900 50  0001 C CNN
F 3 "" H 3150 5900 50  0001 C CNN
	1    3150 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5D7C5FBC
P 4000 6000
F 0 "C10" V 3748 6000 50  0000 C CNN
F 1 "100n" V 3839 6000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 5850 50  0001 C CNN
F 3 "~" H 4000 6000 50  0001 C CNN
	1    4000 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 6000 4150 6000
$Comp
L Device:R R11
U 1 1 5D7F0032
P 3650 6000
F 0 "R11" V 3443 6000 50  0000 C CNN
F 1 "10K" V 3534 6000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3580 6000 50  0001 C CNN
F 3 "~" H 3650 6000 50  0001 C CNN
	1    3650 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 5600 3800 6000
Wire Wire Line
	3850 6000 3800 6000
Connection ~ 3800 6000
Wire Wire Line
	3500 6000 3150 6000
Wire Wire Line
	3150 6000 3150 5900
Wire Wire Line
	4300 2200 4900 2200
Wire Wire Line
	4250 2100 4900 2100
Wire Wire Line
	4200 2000 4900 2000
Text GLabel 6950 2500 0    50   Input ~ 0
i2c_SCL
Text GLabel 6950 2350 0    50   Input ~ 0
i2c_SDA
Wire Wire Line
	1300 1150 1750 1150
Wire Wire Line
	1300 1500 2050 1500
Wire Wire Line
	2350 1150 2750 1150
$Comp
L ACNodeReader-rescue:ATmega88PB-AU-MCU_Microchip_ATmega U2
U 1 1 5D98CB6F
P 3450 3650
F 0 "U2" H 3450 2061 50  0000 C CNN
F 1 "ATmega88PB-AU" H 3450 1970 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 3450 3650 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001909A.pdf" H 3450 3650 50  0001 C CNN
	1    3450 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_GND24 Y1
U 1 1 5E07B328
P 4550 3100
F 0 "Y1" V 4504 3344 50  0000 L CNN
F 1 "Crystal_GND24" V 4595 3344 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_7050-4Pin_7.0x5.0mm" H 4550 3100 50  0001 C CNN
F 3 "~" H 4550 3100 50  0001 C CNN
	1    4550 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 3050 4300 3050
Wire Wire Line
	4300 3050 4300 2950
Wire Wire Line
	4300 2950 4550 2950
Wire Wire Line
	4550 3250 4050 3250
Wire Wire Line
	4050 3250 4050 3150
Wire Wire Line
	5100 3000 4800 3000
Wire Wire Line
	4800 3000 4800 2950
Wire Wire Line
	4800 2950 4550 2950
Connection ~ 4550 2950
Wire Wire Line
	5450 3200 4700 3200
Wire Wire Line
	4700 3200 4700 3250
Wire Wire Line
	4700 3250 4550 3250
Connection ~ 4550 3250
$Comp
L power:GND #PWR0120
U 1 1 5E0B71A5
P 4300 3100
F 0 "#PWR0120" H 4300 2850 50  0001 C CNN
F 1 "GND" H 4305 2927 50  0000 C CNN
F 2 "" H 4300 3100 50  0001 C CNN
F 3 "" H 4300 3100 50  0001 C CNN
	1    4300 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3100 4350 3100
Connection ~ 4350 3100
Wire Wire Line
	4350 3100 4750 3100
Wire Wire Line
	5650 3950 5650 3850
$Comp
L Device:R R9
U 1 1 5EE364C3
P 900 2850
F 0 "R9" H 830 2804 50  0000 R CNN
F 1 "0R" H 830 2895 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 830 2850 50  0001 C CNN
F 3 "~" H 900 2850 50  0001 C CNN
	1    900  2850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 5EE3ACF5
P 800 2850
F 0 "R8" H 650 2900 50  0000 L CNN
F 1 "DNF" H 600 2800 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 730 2850 50  0001 C CNN
F 3 "~" H 800 2850 50  0001 C CNN
	1    800  2850
	1    0    0    -1  
$EndComp
Connection ~ 6100 3800
Wire Wire Line
	5900 3800 6100 3800
Wire Wire Line
	5750 2950 6100 2950
$Comp
L Device:C C1
U 1 1 5EE74DE3
P 1300 1350
F 0 "C1" H 1415 1396 50  0000 L CNN
F 1 "10u" H 1415 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1338 1200 50  0001 C CNN
F 3 "~" H 1300 1350 50  0001 C CNN
	1    1300 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5EE7545C
P 2750 1350
F 0 "C2" H 2865 1396 50  0000 L CNN
F 1 "10u" H 2865 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2788 1200 50  0001 C CNN
F 3 "~" H 2750 1350 50  0001 C CNN
	1    2750 1350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:LM75C U4
U 1 1 5F47B6BF
P 7550 1850
F 0 "U4" H 7550 2531 50  0000 C CNN
F 1 "LM75C" H 7550 2440 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 7550 1850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm75b.pdf" H 7550 1850 50  0001 C CNN
	1    7550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2350 7000 2350
Wire Wire Line
	7000 2350 7000 1750
Connection ~ 7000 1750
Wire Wire Line
	6950 2500 7100 2500
Wire Wire Line
	7100 2500 7100 2000
Connection ~ 7100 2000
Wire Wire Line
	7550 2650 7550 2450
$Comp
L power:+5V #PWR0122
U 1 1 5D4B4AEA
P 7550 1150
F 0 "#PWR0122" H 7550 1000 50  0001 C CNN
F 1 "+5V" H 7565 1323 50  0000 C CNN
F 2 "" H 7550 1150 50  0001 C CNN
F 3 "" H 7550 1150 50  0001 C CNN
	1    7550 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1350 7550 1250
Wire Wire Line
	7550 1250 8500 1250
Wire Wire Line
	8500 1250 8500 1700
Connection ~ 7550 1250
Wire Wire Line
	7550 1250 7550 1150
Wire Wire Line
	7550 2450 8050 2450
Wire Wire Line
	8500 2450 8500 2000
Connection ~ 7550 2450
Wire Wire Line
	7550 2450 7550 2350
Wire Wire Line
	7950 1950 8050 1950
Wire Wire Line
	8050 1950 8050 2450
Connection ~ 8050 2450
Wire Wire Line
	8050 2450 8100 2450
Wire Wire Line
	7950 1850 8100 1850
Wire Wire Line
	8100 1850 8100 2450
Connection ~ 8100 2450
Wire Wire Line
	8100 2450 8150 2450
Wire Wire Line
	7950 1750 8150 1750
Wire Wire Line
	8150 1750 8150 2450
Connection ~ 8150 2450
Wire Wire Line
	8150 2450 8500 2450
Text Notes 6350 850  0    50   ~ 0
May be TMP1075, PCT2075 or any other LM75-compatible IC
$Comp
L Mechanical:MountingHole H1
U 1 1 5F5380E2
P 1150 3500
F 0 "H1" H 1250 3546 50  0000 L CNN
F 1 "MountingHole" H 1250 3455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965" H 1150 3500 50  0001 C CNN
F 3 "~" H 1150 3500 50  0001 C CNN
	1    1150 3500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F539C7A
P 1150 3850
F 0 "H2" H 1250 3896 50  0000 L CNN
F 1 "MountingHole" H 1250 3805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965" H 1150 3850 50  0001 C CNN
F 3 "~" H 1150 3850 50  0001 C CNN
	1    1150 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 5F54FB89
P 8650 4500
F 0 "J1" H 8622 4382 50  0000 R CNN
F 1 "Conn_01x08_Male" H 8622 4473 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Horizontal" H 8650 4500 50  0001 C CNN
F 3 "~" H 8650 4500 50  0001 C CNN
	1    8650 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 3950 5350 3950
Wire Wire Line
	4050 3950 4200 3950
Connection ~ 4200 3950
Wire Wire Line
	4200 2000 4200 3950
Wire Wire Line
	4900 5050 4900 4900
Connection ~ 4900 4900
Wire Wire Line
	1800 2550 1950 2550
Wire Wire Line
	1800 2700 1950 2700
Wire Wire Line
	1950 2800 1800 2800
Wire Wire Line
	1500 2550 1300 2550
Text Label 1300 2550 0    50   ~ 0
LED1
Text Label 1300 2700 0    50   ~ 0
LED2
Text Label 1300 2800 0    50   ~ 0
LED3
Wire Wire Line
	1300 2700 1500 2700
Wire Wire Line
	1500 2800 1300 2800
Wire Wire Line
	800  2650 800  2700
Wire Wire Line
	800  2650 900  2650
Wire Wire Line
	900  2700 900  2650
Connection ~ 900  2650
Wire Wire Line
	900  2650 1950 2650
$Comp
L power:GND #PWR0121
U 1 1 5F638B74
P 800 3200
F 0 "#PWR0121" H 800 2950 50  0001 C CNN
F 1 "GND" H 805 3027 50  0000 C CNN
F 2 "" H 800 3200 50  0001 C CNN
F 3 "" H 800 3200 50  0001 C CNN
	1    800  3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 5F639369
P 1200 3050
F 0 "#PWR0126" H 1200 2900 50  0001 C CNN
F 1 "+5V" H 1215 3223 50  0000 C CNN
F 2 "" H 1200 3050 50  0001 C CNN
F 3 "" H 1200 3050 50  0001 C CNN
	1    1200 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  3000 800  3200
Wire Wire Line
	900  3000 900  3150
Wire Wire Line
	900  3150 1200 3150
Wire Wire Line
	1200 3150 1200 3050
Text Label 4300 4650 0    50   ~ 0
LED1
Text Label 4300 4750 0    50   ~ 0
LED2
Text Label 4450 2550 0    50   ~ 0
LED3
Wire Wire Line
	4050 2550 4450 2550
Wire Wire Line
	4050 4650 4300 4650
Wire Wire Line
	4050 4750 4300 4750
Wire Wire Line
	4200 4850 4200 5600
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5F66A142
P 4050 5400
F 0 "J4" V 4112 5444 50  0000 L CNN
F 1 "Conn_01x02_Male" V 4203 5444 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 4050 5400 50  0001 C CNN
F 3 "~" H 4050 5400 50  0001 C CNN
	1    4050 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 5600 3950 5600
Wire Wire Line
	4050 5600 4200 5600
Connection ~ 4200 5600
Wire Wire Line
	4200 5600 4200 6000
NoConn ~ 7150 1950
NoConn ~ 2850 4150
NoConn ~ 2850 4250
NoConn ~ 2850 4350
NoConn ~ 2850 4450
NoConn ~ 4050 4550
NoConn ~ 4050 4450
NoConn ~ 4050 4350
NoConn ~ 4050 3650
NoConn ~ 4050 3550
NoConn ~ 4050 3450
NoConn ~ 4050 3350
$Comp
L Device:D_Zener D1
U 1 1 5F745A0A
P 850 1300
F 0 "D1" V 804 1380 50  0000 L CNN
F 1 "D_Zener" V 895 1380 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323F" H 850 1300 50  0001 C CNN
F 3 "~" H 850 1300 50  0001 C CNN
	1    850  1300
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 1150 850  1150
Wire Wire Line
	1300 1500 850  1500
Wire Wire Line
	850  1500 850  1450
Connection ~ 1300 1500
Wire Wire Line
	4600 4700 6100 4700
Wire Wire Line
	4050 4150 6100 4150
$Comp
L Connector:Conn_01x04_Male J6
U 1 1 5F7829D5
P 5900 5750
F 0 "J6" H 5872 5724 50  0000 R CNN
F 1 "Conn_01x04_Male" H 5872 5633 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 5900 5750 50  0001 C CNN
F 3 "~" H 5900 5750 50  0001 C CNN
	1    5900 5750
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 5F7B58B0
P 5500 6100
F 0 "#PWR0127" H 5500 5850 50  0001 C CNN
F 1 "GND" H 5505 5927 50  0000 C CNN
F 2 "" H 5500 6100 50  0001 C CNN
F 3 "" H 5500 6100 50  0001 C CNN
	1    5500 6100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0128
U 1 1 5F7B8129
P 5150 5750
F 0 "#PWR0128" H 5150 5600 50  0001 C CNN
F 1 "+5V" H 5165 5923 50  0000 C CNN
F 2 "" H 5150 5750 50  0001 C CNN
F 3 "" H 5150 5750 50  0001 C CNN
	1    5150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 5750 5150 5850
Wire Wire Line
	5150 5850 5700 5850
Wire Wire Line
	5700 5950 5500 5950
Wire Wire Line
	5500 5950 5500 6100
Text Label 5400 5650 0    50   ~ 0
uC_TX
Text Label 5400 5750 0    50   ~ 0
uC_RX
Wire Wire Line
	5700 5750 5400 5750
Wire Wire Line
	5700 5650 5400 5650
$Comp
L Connector:Conn_01x04_Male J7
U 1 1 5F7F44B4
P 9150 3200
F 0 "J7" H 9258 3481 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9258 3390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9150 3200 50  0001 C CNN
F 3 "~" H 9150 3200 50  0001 C CNN
	1    9150 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0129
U 1 1 5F80C1CE
P 10000 2950
F 0 "#PWR0129" H 10000 2800 50  0001 C CNN
F 1 "+5V" H 10015 3123 50  0000 C CNN
F 2 "" H 10000 2950 50  0001 C CNN
F 3 "" H 10000 2950 50  0001 C CNN
	1    10000 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 5F80DCB4
P 9950 3400
F 0 "#PWR0130" H 9950 3150 50  0001 C CNN
F 1 "GND" H 9955 3227 50  0000 C CNN
F 2 "" H 9950 3400 50  0001 C CNN
F 3 "" H 9950 3400 50  0001 C CNN
	1    9950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 3100 10000 3100
Wire Wire Line
	10000 3100 10000 2950
Wire Wire Line
	9950 3200 9950 3400
Text Label 9550 3300 0    50   ~ 0
i2c_SCL
Text Label 9550 3400 0    50   ~ 0
i2c_SDA
Wire Wire Line
	9350 3300 9550 3300
Wire Wire Line
	9350 3400 9550 3400
Wire Wire Line
	9350 3200 9950 3200
$EndSCHEMATC
