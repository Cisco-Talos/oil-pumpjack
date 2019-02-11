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

#include "enipcip.h"

// For Arduino 0022
// Server EnipServer(EnipCIP_PORT);
// For Arduino 1.0
EthernetServer EnipServer(EnipCIP_PORT);

EnipCIP::EnipCIP()
{
}

int EnipCIP::Run()
{  
  Runs = 1 + Runs * (Runs < 999);

  //****************** Read from socket ****************
  // For Arduino 0022
  // Client client = EnipServer.available();
  // For Arduino 1.0
  EthernetClient client = EnipServer.available();
  int MessageLength;

  if(client.available())
  {
    Reads = 1 + Reads * (Reads < 999);
    int i = 0;
    while(client.available())
    {
      ByteArray[i] = client.read();
      i++;
    }
    if (ByteArray[0] == 0x65 && ByteArray[1] == 0x00)
    {
      sessionID=random(0x00,0xFF);
      #ifdef EnipDebug
        Serial.println("Registration");
        Serial.print("Session ID: 0x0b0224");
        Serial.println(sessionID,HEX);
      #endif
      MessageLength = 28;
      // Session 0x0b0224XX
      ByteArray[4]=sessionID;
      ByteArray[5]=0x24;
      ByteArray[6]=0x02;
      ByteArray[7]=0x0b;
      client.write(ByteArray, MessageLength);
    }
    if (ByteArray[40] == 0x4e)
    {
      #ifdef EnipDebug
        Serial.println("Forward close");
      #endif
      if(ByteArray[4] != sessionID)
        return(0);
      MessageLength = 64;
      ByteArray[40]=0xce;
      ByteArray[41]=0x00;
      ByteArray[42]=0x00;
      ByteArray[43]=0x00;
      client.write(ByteArray, MessageLength);
    }
    if (ByteArray[40] == 0x54)
    {
      #ifdef EnipDebug
        Serial.println("Forward Open");
      #endif
      if(ByteArray[4] != sessionID)
        return(0);
      MessageLength = 88;
      ByteArray[40]=0xd4;
      ByteArray[41]=0x00;
      ByteArray[42]=0x00;
      ByteArray[43]=0x00;
      client.write(ByteArray, MessageLength);
    }
    if (ByteArray[46] == 0x4b)
    {
      if(ByteArray[4] != sessionID)
        return(0);
      int letter=ByteArray[66];
      int first_num=ByteArray[65];
      int second_num=ByteArray[67];

      #ifdef EnipDebug
        Serial.println("Class / Service");
        Serial.print("Letter: 0x");
        Serial.println(letter, HEX);

        Serial.print("1st Number: ");
        Serial.println(first_num);

        Serial.print("2nd Number: 0x");
        Serial.println(second_num, HEX);
      #endif
      
      if (ByteArray[63] == 0xab)
      {
        int value=(ByteArray[72]<<8)+ByteArray[71];
        #ifdef EnipDebug
          Serial.println("Write Mode");
          Serial.print("Value: ");
          Serial.println(value, HEX);
        #endif
        if (first_num < x_Max && second_num < x_Max)
        {
          #ifdef EnipDebug
            Serial.println("Correct Index");
          #endif
          if (letter == 0x85)
          {
            #ifdef EnipDebug
              Serial.println("B case");
            #endif
            valuesB[first_num][second_num]=value;
          }
          else if (letter == 0x89)
          {
            #ifdef EnipDebug
              Serial.println("N case");
            #endif
            valuesN[first_num][second_num]=value;
          } else {
            #ifdef EnipDebug
              Serial.println("Unknown case");
            #endif
          }
        } else {
          #ifdef EnipDebug
            Serial.println("Incorrect Index");
          #endif 
        }
        MessageLength = 73;
        ByteArray[46]=0xcb;
        ByteArray[47]=0x00;
        ByteArray[48]=0x00;
        ByteArray[49]=0x00;
        ByteArray[58]=0x00;
        client.write(ByteArray, MessageLength);
      }
      else if (ByteArray[63] == 0xa2)
      {
         #ifdef EnipDebug
           Serial.println("Read Mode");
         #endif
         if (first_num < x_Max && second_num < x_Max)
         {
          MessageLength = 75;
          ByteArray[46]=0xcb;
          ByteArray[47]=0x00;
          ByteArray[48]=0x00;
          ByteArray[49]=0x00;
          ByteArray[58]=0x00;
            
           if (letter == 0x85){
            #ifdef EnipDebug
              Serial.print("Return B");
              Serial.print(first_num);
              Serial.print(":");
              Serial.print(second_num);
              Serial.print(" : ");
              Serial.println(valuesB[first_num][second_num]);
            #endif
            //Value      
            ByteArray[67]=valuesB[first_num][second_num] & 0xFF;
            ByteArray[68]=valuesB[first_num][second_num] >> 8;
               
            client.write(ByteArray, MessageLength);
          
           }
           else if (letter == 0x89){
             #ifdef EnipDebug
              Serial.print("Return N");
              Serial.print(first_num);
              Serial.print(":");
              Serial.print(second_num);
              Serial.print(" : ");
              Serial.println(valuesN[first_num][second_num]);
            #endif
            //Value      
            ByteArray[67]=valuesN[first_num][second_num] & 0xFF;
            ByteArray[68]=valuesN[first_num][second_num] >> 8;
               
            client.write(ByteArray, MessageLength);
           }
           else {
            #ifdef EnipDebug
              Serial.println("Unknown letter");
            #endif
           }
         } else {
          #ifdef EnipDebug
            Serial.println("Incorrect Index");
          #endif 
        }
      }
      else
      {
         #ifdef EnipDebug
           Serial.println("Unknown Mode");
         #endif        
      }
    }
  }
}
