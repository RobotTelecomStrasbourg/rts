#!/usr/bin/python
# -*- coding: UTF-8 -*-

from __future__ import print_function

import sys
sys.path.append("../../lib");

import time
import libservo
import libport
import numpy
from cv2 import *
import math
from PIL import Image
from PIL import ImageOps
import video


#try:
#	import RPi.GPIO as GPIO
#except RuntimeError:
#	print ("Erreur: RPi.GPIO n'est pas disponible");

def capture(cam):
	ret, frame = cam.read();
	vis = frame.copy();
	return vis;

if __name__=="__main__":
	## Initialisation du servomoteur
	pin=7;
	port=libport.Port(pin, libport.Port.OUT);
	svm=libservo.Servo(port);
	svm.bornes(-90,90);
	svm.start();
	#time.sleep(1);
	#timp = svm.rotate(-90);
	#time.sleep(1);
	#timp = svm.rotate(90);	
	#time.sleep(1);
	#svm.rotate(90);
	## Récupération du pattern	
	him=imread("pattern.jpg");
	him=cvtColor(him, COLOR_RGB2GRAY);
	#him=him[:,:,0];
	cam=video.create_capture(0);
	namedWindow("capture");
	## !!!!!! 
	## Si aucune detection baisser la valeur de threshold, si fausse detection augmenter valeur
	threshold=0.958;
	teta=0;
	## Controle du servo par vision 
	while (True):
		im=capture(cam);	
		im=im[(im.shape[0]/2)-50:(im.shape[0]/2)+50,:,:];
		#gray=im[(im.shape[0]/2)-50:(im.shape[0]/2)+50,:,0];
		gray=flip(cvtColor(im, COLOR_RGB2GRAY),1);
		#gray=gray[gray.shape[0]/3:(2*gray.shape[0])/3,:];
		#print (gray.shape);
		xcorr_cv=matchTemplate(gray, him, TM_CCORR_NORMED);
		mi,ma,miLoc,maLoc=minMaxLoc(xcorr_cv);
		if (ma>threshold):
			f_x,f_y=maLoc;
			f_x=im.shape[1] - ((gray.shape[1]/xcorr_cv.shape[1])*f_x + him.shape[1]/2);
			#f_x = (gray.shape[1]/xcorr_cv.shape[1])*f_x ;
			f_y=(gray.shape[0]/xcorr_cv.shape[0])*f_y + him.shape[0]/2;
			teta=((f_x*90)/gray.shape[1]);
			rectangle(im, (f_x-him.shape[1]/2, f_y-him.shape[0]/2), (f_x+him.shape[1]/2, f_y+him.shape[0]/2), (0,255,0), 2);
		else:
			teta=0;
			pm=(im.shape[1]/2 - him.shape[1]/2, im.shape[0]/2 - him.shape[0]/2);
			pp=(im.shape[1]/2 + him.shape[1]/2, im.shape[0]/2 + him.shape[0]/2);
			rectangle(im, pm, pp, (0,0,255), 2);
		imshow("capture", im);
		try:
			svm.rotate(teta);
		except Exception:
			s=0;
		print ("max = {0}  :: maxLoc = {1}    ::  teta = {2}       \r".format(ma,maLoc, teta), end='');
		ch = 0xFF & waitKey(5);
		if ch == 27:
			break;
	svm.stop();
	port.close();

