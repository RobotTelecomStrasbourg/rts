#!/usr/bin/python
# -*- coding: UTF-8 -*-

'''
@author: KILIAN HETT
'''

from __future__ import print_function

import numpy
from cv2 import *
import math
from PIL import Image
from PIL import ImageOps
import video


if __name__=="__main__":
	cam=video.create_capture(1);
	namedWindow("capture");
	rec=(100,100);
	while (True):
		ret, frame = cam.read();
		im=frame.copy();
		rim=flip(frame.copy(),1);
		rectangle(rim, (rim.shape[1]/2-rec[1]/2, rim.shape[0]/2-rec[0]/2), (rim.shape[1]/2+rec[1]/2, rim.shape[0]/2+rec[0]/2), (255,0,0),2);
		imshow("capture", rim);
		ch=0XFF&waitKey(5);
		if ch==27:
			break;
	rangeXmin=im.shape[0]/2-rec[0]/2;
	rangeXmax=im.shape[0]/2+rec[0]/2;
	rangeYmin=im.shape[1]/2-rec[1]/2;
	rangeYmax=im.shape[1]/2+rec[1]/2;
	cap=im[rangeXmin:rangeXmax, rangeYmin:rangeYmax];
	imwrite("pattern.jpg", cap);
