#!/usr/bin/python

import logging

# Get handles to the various logs
server_log          = logging.getLogger("pysnmp.server")
client_log          = logging.getLogger("pysnmp.client")
protocol_log        = logging.getLogger("pysnmp.protocol")
store_log           = logging.getLogger("pysnmp.store")

# Enable logging levels
server_log.setLevel(logging.DEBUG)
protocol_log.setLevel(logging.DEBUG)
client_log.setLevel(logging.DEBUG)
store_log.setLevel(logging.DEBUG)

# Initialize the logging
try:
  logging.basicConfig()
except Exception, e:
  print "Logging is not supported on this system"

from pymodbus.client.sync import ModbusTcpClient
import sys

client = ModbusTcpClient("10.10.10.1")
result = client.read_holding_registers(6, 1)
print(result.registers)
result2 = client.read_holding_registers(7, 1)
print(result2.registers)


from pymodbus import mei_message
rq = mei_message.ReadDeviceInformationRequest()
result3=client.execute(rq)
print(result3.information)


client.close()
