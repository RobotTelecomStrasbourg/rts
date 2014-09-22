#!/usr/bin/python
# -*- coding: UTF-8 -*-

from __future__ import print_function

import numpy
from cv2 import *
import math
from PIL import Image
from PIL import ImageOps
import video

def capture(cam):
	ret, frame = cam.read();
	vis = frame.copy();
	return vis;



if __name__=="__main__":
	him=imread("pattern.jpg");
	him=cvtColor(him, COLOR_RGB2GRAY);
	cam=video.create_capture(0);
	#namedWindow("patch");
	#imshow("patch",him);
	namedWindow("capture");
	threshold=0.98;
	#namedWindow("correlation");
	while (True):
		im=capture(cam);
		gray=cvtColor(im, COLOR_RGB2GRAY);
		xcorr_cv=matchTemplate(gray, him, TM_CCORR_NORMED);
		mi,ma,miLoc,maLoc=minMaxLoc(xcorr_cv);
		if (ma>threshold):
			f_x, f_y = maLoc;
			f_x=(gray.shape[1]/xcorr_cv.shape[1])*f_x + him.shape[1]/2;
			f_y=(gray.shape[0]/xcorr_cv.shape[0])*f_y + him.shape[0]/2;
			rectangle(im, (f_x-him.shape[1]/2, f_y-him.shape[0]/2), (f_x+him.shape[1]/2, f_y+him.shape[0]/2), (0,255,0), 2);
		else:
			pm=(im.shape[1]/2 - him.shape[1]/2, im.shape[0]/2 - him.shape[0]/2);
			pp=(im.shape[1]/2 + him.shape[1]/2, im.shape[0]/2 + him.shape[0]/2);
			rectangle(im, pm, pp, (0,0,255), 2);
		imshow("capture", im);
		#imshow("correlation", xcorr_cv);
		print ("max = {0}  :: maxLoc = {1}           \r".format(ma,maLoc), end='');
		ch = 0xFF & waitKey(5);
		if ch == 27:
			break;

