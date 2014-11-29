#!/usr/bin/python
# -*- coding: UTF-8 -*-

import smbus

class I2C:
	def __init__(self, addr):
		self._addr=addr;
		self._bus=smbus.SMBus(1);
	def writeU8(self, v):
		try:
			self._bus.write_byte(self._addr, v);
		except IOError, err:
			print "Error : write data";

	def readU8(self):
		try:
			return self._bus.read_byte(self._addr);
		except IOError, err:
			print "Error : read data";
			return 0x0;

	def writeU8Reg(self, reg, v):
		try:
			self._bus.write_byte_data(self._addr, reg, v);
		except IOError, err:
			print "Error : write data";

	def readU8Reg(self, reg):
		try:
			return self._bus.read_byte_data(self._addr, reg);
		except IOError, err:
			print "Error : read data";
			print err;
			print IOError;
			return 0x0;

	def writeU16Reg(self, reg, v):
		try:
			self._bus.write_word_data(self._addr, reg, v);
		except IOError, err:
			print "Error : write data";

	def readU16Reg(self, reg):
		try:
			return self._bus.read_word_data(self._addr, reg);
		except IOError, err:
			print "Error : read data";
			return 0x0;

	def writeBlockReg(self, reg, b):
		try:
			self._bus.write_block_data(self._addr, reg, b);
		except IOError, err:
			print "Error : write block";

	def readBlockReg(self, reg, length):
		try:
			return self._bus.read_block_data(self._addr, reg, length);
		except IOError, err:
			print "Error : read data";
			return 0x0;
		
		



















