#!/usr/bin/python
from flask import Flask, request, render_template
from pymodbus.client.sync import ModbusTcpClient
from pymodbus import mei_message
import time

IP="10.10.10.1"

class MB():
  def __init__(self, ip, port=502):
    self.ip=ip
    self.port=port
    self.connect()
  def connect(self):
      self.client=ModbusTcpClient(self.ip, port=self.port,timeout=10)
  def read_reg(self):
    val=self.client.read_holding_registers(6, 2)
    return val.registers
  def write_reg(self, value):
    self.client.write_register(6, scada_value)
    return 0
  def deviceinfo(self):
    rq = mei_message.ReadDeviceInformationRequest()
    val=self.client.execute(rq)
    return(val.information)
  def close(self):
    self.client.close()


app = Flask(__name__)
modbus = MB(IP)
scada_value = modbus.read_reg()[0]

@app.route('/')
def index():
  m=MB(IP)
  val=m.deviceinfo()
  m.close()
  return render_template('scada.html',VendorName=val[0], ProductCode=val[1],  MajorMinorRevision=val[2])

@app.route('/highlight.pack.js')
def highlight_pack_js():
  return render_template('highlight.pack.js')

@app.route('/gauge.js')
def gauge_js():
  return render_template('gauge.js')

@app.route('/value')
def value():
  global scada_value
  val=modbus.read_reg()
  scada_value=val[0]
  print scada_value
  return str((val[1]*100)/180)

@app.route('/up')
def up():
  global scada_value
  scada_value=scada_value+1000
  modbus.write_reg(scada_value)
  return "OK"

@app.route('/down')
def down():
  global scada_value
  scada_value=scada_value-1000
  modbus.write_reg(scada_value)
  return "OK"

@app.route('/shutdown')
def shutdown():
  global scada_value
  scada_value=1
  modbus.write_reg(scada_value)
  return "OK"


if __name__ == '__main__':
  app.run(host='0.0.0.0', debug=True)
