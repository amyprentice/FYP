'''
FYP - Amy feat. Abuzar
'''
import matplotlib.pyplot as plt
import numpy
import serial
import scipy
from python_speech_features import mfcc
import librosa
from time import time
from scipy.signal import butter, lfilter, freqz
import pandas as pd
import warnings


warnings.simplefilter(action='ignore', category=FutureWarning)
serial_data = serial.Serial('COM3', 9600)

mfcc_coeff1 = []
mfcc_coeff2 = []
coeff1 = [0]*13
coeff2 = [0]*13
signal1 = []
signal2 = []
signal3 = []
signal4 = []
test = []
sampling_frequency = 8000
order = 6
cut_off = 4000
num_mfcc = 0

serial_data.flushInput()

run = True
initialise = True
flag = False


# def butter_lowpass(co, fs, order=5):
#     nyq = 0.5 * fs
#     normal_cutoff = co / nyq
#     b, a = butter(order, normal_cutoff, btype='low', analog=False)
#     return b, a
#
#
# def butter_lowpass_filter(data, co, fs, order=5):
#     b, a = butter_lowpass(co, fs, order=order)
#     y = lfilter(b, a, data)
#     return y


while run:
    while '' in signal1:
        signal1.remove('')
    while '' in signal2:
        signal2.remove('')
    if (len(signal1) and len(signal2)) > 300:
        # signal1 = butter_lowpass_filter(signal1, cut_off, sampling_frequency, order)
        # print("abuzar the true nigga")
        signal1 = numpy.array(signal1,numpy.float)
        signal2 = numpy.array(signal2,numpy.float)
        signal3 = numpy.array(signal3, numpy.float)
        signal4 = numpy.array(signal4, numpy.float)
        piezo_mean = numpy.mean([signal3, signal4], axis=0)
        signal4_mean = numpy.mean(signal4)
        # print(signal4_mean)
        mfcc_coeff1 = librosa.feature.mfcc(signal1, sampling_frequency, None, 13, 2)
        mfcc_coeff2 = librosa.feature.mfcc(signal2, sampling_frequency, None, 13, 2)
        mfcc_coeff1 = [val1 for sublist1 in mfcc_coeff1 for val1 in sublist1]
        mfcc_coeff2 = [val2 for sublist2 in mfcc_coeff2 for val2 in sublist2]

        if initialise:
            df1a = pd.DataFrame({'MFCC': coeff1})
            df2a = pd.DataFrame({'MFCC': coeff2})
            initialise = False
        else:
            df1b = pd.DataFrame.from_records({'Coeff': mfcc_coeff1})
            df1a = pd.concat([df1a, df1b], axis = 1, sort = True)
            df2b = pd.DataFrame.from_records({'Coeff': mfcc_coeff2})
            df2a = pd.concat([df2a, df2b], axis = 1, sort = True)

        if num_mfcc == 1:

            df1a.to_csv('MFCC1_Idle.txt', sep='\t')
            df2a.to_csv('MFCC2_Idle.txt', sep='\t')
            avg_val1 = (df1a.loc[0, 'Coeff'] + df2a.loc[0, 'Coeff'])/2
            # print(piezo_mean)
            max_val1 = sum(i > 26 for i in piezo_mean)
            max_val2 = sum(i > signal4_mean + 2 for i in signal4)
            print(max_val2)
            # print(max_val1)
            if avg_val1 < 500:
                print("Nothing")
            elif max_val2 < 15:
                print("Cracker")
            else:
                print("Water")

            num_mfcc = 100
            signal1 = []
            signal2 = []
        else:
            num_mfcc = num_mfcc + 1


    else:
        # serial_data.reset_input_buffer()
        output = serial_data.readline().strip()
        output = output.decode('utf-8')
        try:
            mic1, mic2, piezo1, piezo2 = output.split(',')
        except:
            print("Data Collection Failed")
            pass
        try:
            print("Data Collection Begun")
            signal1.append(mic1[:])
            signal2.append(mic2[:])
            signal3.append(piezo1[:])
            signal4.append(piezo2[:])

        except:
            pass
