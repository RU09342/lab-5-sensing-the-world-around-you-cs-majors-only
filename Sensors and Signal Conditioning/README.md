# Austin Huang, Matthew Rodriguez Sensors and Signal Conditioning

# ADC Implementation

The ADC value can be calculated by using the max value of the binary number that can be made with a specified amount of bits. The binary number must be proportionate 
to the voltage value within the voltage range. Thus, it can be set up as a proportion as a certain number in binary out of the specified voltage value out of the max
voltage value.

## Sensor and circuit elemtents

Photoresistor: Tested using voltage divider. The max voltage of the photoresistor needed to be kept below the 3.3V range. The correct resistor values were used to 
divide the voltage, so the output would stay below the range under any condition.

Photodiode: Photodiodes convert light(photons) into electrical current. Photodiodes can be used as sensors, since the amount of current emitted varies depending on 
how much light the photodiode receives. A circuit was built to test the photodiode and how it could be used to create a sensor for the lab.

Phototransistor: A light sensitive transistor can be used to create a sensor as well. Only the gate and drain were connected so that the transistor behaved as a diode. 

The 3 circuit elements (photoresistor, photodiode, and phototransistor) were tested to roughly estimate their minimum and maximum voltage outputs in a simple test 
circuit. The outputs of the circuit are checked so that they will not exceed a specified 3.3V, while their minimum values were also considered.

## Code

NOTE: This README is only a brief synopsis of the process used to collect and analyze data. Attached is a Word Document with additional details on the Sensors and 
Signal Conditioning of these circuit elements.
