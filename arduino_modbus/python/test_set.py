#!/usr/bin/python

import logging
import sys

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

client = ModbusTcpClient("10.10.10.1")
#result = client.read_holding_registers(6, 1)
result = client.write_register(6, int(sys.argv[1]))


client.close()
