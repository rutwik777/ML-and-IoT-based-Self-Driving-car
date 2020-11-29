# test_model.py

import numpy as np
from grabscreen import grab_screen
import cv2
import time
from alexnet import alexnet
from getkeys import key_check
import serial
arduinoSerial = serial.Serial('com4',9600)
time.sleep(1)

import random

WIDTH = 160
HEIGHT = 120
LR = 1e-3
EPOCHS = 20
MODEL_NAME = 'self-driving-car-fast-final-{}-{}-{}-epochs-930-data.model'.format(LR, 'alexnetv2',EPOCHS)

t_time = 0.09

def straight():
    print ('Straight')
    arduinoSerial.write(b'8') #Straight

def left():
    print ('Left')
    arduinoSerial.write(b'4') #LEFT
    time.sleep(t_time)
##    ReleaseKey(A)

def right():
    print ('Right')
    arduinoSerial.write(b'6') #RIGHT
    time.sleep(t_time)
#    ReleaseKey(D)
    
model = alexnet(WIDTH, HEIGHT, LR)
model.load(MODEL_NAME)

def main():
    last_time = time.time()
    for i in list(range(4))[::-1]:
        print(i+1)
        time.sleep(1)

    paused = False
    while(True):
        
        if not paused:
            # 800x600 windowed mode
            #screen =  np.array(ImageGrab.grab(bbox=(0,40,800,640)))
            screen = grab_screen(region=(0,40,800,640))
            print('loop took {} seconds'.format(time.time()-last_time))
            last_time = time.time()
            screen = cv2.cvtColor(screen, cv2.COLOR_BGR2GRAY)
            screen = cv2.resize(screen, (160,120))

            prediction = model.predict([screen.reshape(160,120,1)])[0]
            moves = list(np.around(prediction))
            print(moves, prediction)


            if moves == [0,1,0] :
                straight()
            elif moves == [1,0,0]: 
                left()
            elif moves == [0,0,1]:
                right()
            else:
                straight()

        keys = key_check()

        # p pauses game and can get annoying.
        if 'T' in keys:
            if paused:
                paused = False
                time.sleep(1)
            else:
                paused = True
                time.sleep(1)

main()       
