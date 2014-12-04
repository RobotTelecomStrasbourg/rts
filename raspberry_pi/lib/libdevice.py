#!/bin/python
# -*- coding: UTF-8 -*-

from libi2c import I2C
import time

class Arduino:
	LOCKED=0;
	UNLOCKED=1;
	TYPE_PUSH=11;
	TYPE_PULL=12;
	def __init__(self, addr):
		self.arduino=I2C(addr);
	def pushValue(self, reg, value, flag=LOCKED):
		if type(value) is not int:
			raise TypeError("The value must be an integer");
		if type(reg) is not int:
			raise TypeError("The register address must be an integer");
		datastream = [self.TYPE_PUSH, flag];
		for i in range(4):
			v = (value >> (i*8)) & 0xFF;
			datastream.append(v);
		self.arduino.writeBlockReg(reg, datastream);
		if (flag):
			return self.arduino.readU8();
		else:
			return 1;
	def pullValue(self, reg):
		if type(reg) is not int:
			raise TypeError("The register address must be an interger");
		self.arduino.writeU8Reg(reg, self.TYPE_PULL);
		value=0;
		for i in range(4):
			value=value|((self.arduino.readU8()<<(i*8)) & 0xFF);
		return value;



