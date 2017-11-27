#PCB Design - Austin Huang and Matthew Rodriguez

## PCB

The PCB designed contains the MSP430FR2311, two 8-pin headers, a bypass capacitor, a bulk capacitor, and a pull-up resistor.

This PCB is designed to be the breakout board for the MSP430. It has useful aspects that allow the MSP430 function from a second order 
design perspective. The bulk capacitor provides voltage to the MSP430 if there is a sudden drop in voltage to the system. The bypass filter
filters out AC noise. These design considerations will allow the MSP430 to perform better.

## Bill of Materials

|Component  | Name     	   	 |Value|
|-----------| ------------------ |-----|
|R1         | RES_0805 	   	 |100nF|
|U1         | MSP430FR2311IPW16R |10nF |
|C3         | CAP_0805	   	 |1nF  |
|J1         | 64456_8 	   	 |None |
|J2         | 64456_8 	   	 |None |
|C1         | CAP_0805 	   	 |47k  |
|C2         | CAP_0805           |None |

The components labeled in the bill of materials correspond to the schematic elements in schematic attached in the repository.

##DigiKey Link

http://www.digikey.com/short/q3rvz4

