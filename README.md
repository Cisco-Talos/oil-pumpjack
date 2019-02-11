# Oil Pumpjack

This repository contains all the materials to create your own oil pumpjack. The purpose of this project is to provide a safe learning environment. The current version supports Modbus over TCP and EtherNet/IP protocol. For more details and to see how to build it, please refer to our [publication](https://blog.talosintelligence.com/2019/02/oil-pumpjack.html).

![Oil pumpjack](https://github.com/Cisco-Talos/oil-pumpjack/blob/master/Pictures/pump.gif)

## 3-D print models
The repository /stl contains the .stl objects. You can 3-D print these object to create the oil pumpjack

![3-D Model](https://github.com/Cisco-Talos/oil-pumpjack/blob/master/Pictures/image001.png)

* Object 1 is the pump.
* Object 2 is the motor, which activates the pump.
* Object 3 is where the three boards are located. It also contains the gauge that shows the speed level.

## Arduino Schematic

![Arduino Schematic](https://github.com/Cisco-Talos/oil-pumpjack/blob/master/Pictures/image002.jpg)

## Modbus over TCP Version

The Modbus over TCP version of the pumpjack is in the repository /arduino_modbus. Here is the subdirectories:

* /arduino_modbus/pumpjack_modbus contains the Arduino Uno source code
* /arduino_modbus/HMI contains the Human Machine Interface source code
* /arduino_modbus/python contains several python scripts to test the communication to the pump
* /arduino_modbus/plcscan contains the source code of a PLC scanner tool (the tool available [here](https://github.com/meeas/plcscan))

## EtherNet/IP Version

The EtherNet/IP version is in the directory /arduino_ENIPCIP. Here is the subdirectories:

* /arduino_ENIPCIP/pumpjack_ENIPCIP contains the Arduino Uno source code
* /arduino_ENIPCIP/python contains several python scripts to test the communication to the pump
* /arduino_ENIPCIP/pcap contains the pcap files used to create the protocol
