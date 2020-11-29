# create_training_data.py

import numpy as np
from grabscreen import grab_screen
import cv2
import time
from getkeys import key_check
import os
import serial
arduinoSerial = serial.Serial('com4',9600)
time.sleep(1)
t_time = 0.100

def keys_to_output(keys):
    '''
    Convert keys to a ...multi-hot... array

    [A,W,D] boolean values.
    '''
    output = [0,0,0]
    
    if 'A' in keys:
        output[0] = 1
        arduinoSerial.write(b'4') #LEFT
        time.sleep(t_time)
    elif 'D' in keys:
        output[2] = 1
        arduinoSerial.write(b'6') #RIGHT
        time.sleep(t_time)
    elif 'W' in keys:
        output[1] = 1
        arduinoSerial.write(b'8') #Straight
        time.sleep(t_time)
    return output


file_name = 'training_data_actual_28_.npy'

if os.path.isfile(file_name):
    print('File exists, loading previous data!')
    training_data = list(np.load(file_name))
else:
    print('File does not exist, starting fresh!')
    training_data = []


def main():

    for i in list(range(4))[::-1]:
        print(i+1)
        time.sleep(1)


    paused = False
    while(True):

        if not paused:
            # 800x600 windowed mode
            screen = grab_screen(region=(0,60,800,640))
            last_time = time.time()
            screen = cv2.cvtColor(screen, cv2.COLOR_BGR2GRAY)
            screen = cv2.resize(screen, (160,120))
            # resize to something a bit more acceptable for a CNN
            keys = key_check()
            output = keys_to_output(keys)
            training_data.append([screen,output])
            
            if 'R' in keys:
                print(len(training_data))
                np.save(file_name,training_data)

        keys = key_check()
        if 'T' in keys:
            if paused:
                paused = False
                print('unpaused!')
                time.sleep(1)
            else:
                print('Pausing!')
                paused = True
                time.sleep(1)


main()
