#!/usr/bin/python

from pycomm.ab_comm.slc import Driver as SlcDriver
from time import sleep
import logging
import sys

#logging.basicConfig(
#   level=logging.DEBUG
#)

c = SlcDriver()

def write_data(num, val):
  print "Write data: %d" % val
  c.write_tag('B1:%d' % num, val)

def read_tap(num):
  print c.read_tag('B1:%d' % num)[3]

val=int(sys.argv[1])

if c.open('10.10.10.1'):
  #write_data(1, val)
  #sleep(5)
  read_tap(1)

#c.close()
