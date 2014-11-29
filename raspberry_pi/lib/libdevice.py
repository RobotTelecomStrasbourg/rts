#!/bin/python
# -*- coding: UTF-8 -*-

from libi2c import I2C
import time

class Arduino:
	LOCKED=0;
	UNLOCKED=1;
	TYPE_PUSH=11;
	TYPE_PULL=12;
	def __init__(self, addr, flag=LOCKED):
		self.arduino=I2C(addr);
		self.flag=flag;
	def pushValue(self, reg, value):
		if type(value) is not int:
			raise TypeError("The value must be an integer");
		if type(reg) is not int:
			raise TypeError("The register address must be an integer");
		self.arduino.writeU8(self.TYPE_PUSH);
		#self.arduino.writeU8(flag);
		#self.arduino.writeU8(reg);
		#for i in range(4):
		#	self.arduino.writeU8((value>>(i*8)) & 0xF);
		#if (flag):
		#	return self.arduino.readU8();
		#else:
		#	return 1;
	def pullValue(self, reg):
		if type(reg) is not int:
			raise TypeError("The register address must be an interger");
		self.arduino.writeU8(TYPE_PULL);
		self.arduino.writeU8(reg);
		value=0;
		for i in range(4):
			value=value|(self.arduino.readU8()<<(i*8));
		return value;



