#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
sys.path.append("../lib");
from libi2c import I2C

import smbus
import time


def main(addr, value):
	arduino = I2C(addr);
	arduino.writeU8(value);
	print " -- Envoie de la valeur ", value;
	time.sleep(1);
	receive = arduino.readU8();
	print " -- Reponse de l'arduino ", receive;

if __name__=="__main__":
	addr = 0x12;
	main(addr, 6);

