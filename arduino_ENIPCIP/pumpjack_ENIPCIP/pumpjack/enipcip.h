/*
    enipcip.h - an Arduino library for a ENIP/CIP
    Copyright (C) 2019  Paul Rascagneres

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define EnipDebug

// For Arduino 0022
// #include "WProgram.h"
// For Arduino 1.0
#include "Arduino.h"

#include <SPI.h>
#include <Ethernet.h>

#ifndef EnipCIP_h
#define EnipCIP_h

#define EnipCIP_PORT 44818
#define x_Max 9
class EnipCIP
{
public:
  EnipCIP();
  int Run();  
  int sessionID;
  int valuesB[x_Max][x_Max];
  int valuesN[x_Max][x_Max];
  int Runs, Reads, Writes;
private: 
  uint8_t ByteArray[260];
};

#endif
