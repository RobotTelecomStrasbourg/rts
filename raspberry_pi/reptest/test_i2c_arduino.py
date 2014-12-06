#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
sys.path.append("../lib");
#from libdevice import Arduino
import libdevice

import time


def main(addr, value):
	arduino=libdevice.Arduino(addr);
	arduino.pushValue(1,1000);	

	v = arduino.pullValue(0);
	print v;


'''	arduino = I2C(addr);
	arduino.writeU8(value);
	print " -- Envoie de la valeur ", value;
	time.sleep(1);
	receive = arduino.readU8();
	print " -- Reponse de l'arduino ", receive;
'''


if __name__=="__main__":
	addr = 0x10;
	main(addr, 6);

