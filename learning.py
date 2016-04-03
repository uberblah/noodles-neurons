#!/usr/bin/env python

from keras.utils.visualize_util import plot
from keras.models import Sequential, Graph
from keras.layers.core import Dense
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers.convolutional import Convolution1D
from keras.layers.normalization import BatchNormalization
from keras.optimizers import SGD, RMSprop
import keras.objectives as KObjs

import numpy as np
import soundfile

import random as rnd
import math
import sys
import os

# a place to save the network diagram
model_image = "network.png"
sample_size = 256
synth_time = 30 #seconds

# usage string, for silly users and developers such as ourselves
usage = "./learning.py new <net-out>\n" +\
        "./learning.py train <net-file> <audio-file>\n" +\
        "./learning.py synth <net-file> <audio-in> <audio-out>\n" +\
        "./learning.py test <net-file> <audio-file> <audio-out>\n"

# check argument count
if len(sys.argv) < 3:
    print(usage)
    exit(0)

# get basic arguments
mode = sys.argv[1]
netfile = sys.argv[2]

# create the model and fill it in if necessary
print("building model...")
#model = Sequential()
#model.add(Dense(sample_size, activation = "sigmoid", input_dim = sample_size))
#model.add(Dense(sample_size, activation = "sigmoid"))
model = Graph()
model.add_input("audio", input_shape = (sample_size,))
model.add_input("memo", input_shape = (sample_size,))
model.add_node(Dense(sample_size, activation = "sigmoid"),\
                input = "audio", name = "audiolayer")
memolayer = Dense(sample_size, activation = "sigmoid", init = "glorot_normal")
model.add_node(memolayer, inputs = ["memo", "audio"], name = "memolayer")
model.add_node(Dense(sample_size, activation = "sigmoid"),\
                input = "audiolayer", name = "mergelayer")
model.add_node(BatchNormalization(), input = "memolayer", name = "normlayer")
model.add_output("memo-out", input = "normlayer", merge_mode = "sum")
model.add_output("output", input = "mergelayer", merge_mode = "sum")

# make a diagram of the network, save it in a file
if model_image != None:
    print("exporting model diagram...")
    plot(model, to_file=model_image)

# save the model if we're done
if mode == "new":
    print("saving model weights...")
    model.save_weights(netfile, overwrite = True)
    exit(0)

# are we prepared for this???
if len(sys.argv) < 4:
    print(usage)
    exit(0)

# prepare the model for learning
print("compiling model...")
#rms = SGD()
rms = RMSprop()
#model.compile(optimizer=rms, loss="mean_squared_error")
KObjs.allzero = lambda x,y: KObjs.mean_squared_error(x, y)\
                            * rnd.choice([-0.01, 0.01])
#model.compile(optimizer=rms, loss={"output": "mean_squared_error"})
model.compile(optimizer = rms,\
    loss = {"output": "mean_squared_error", "memo-out": "mean_squared_error"})

# load weights if available
print("loading weights...")
model.load_weights(sys.argv[2])
audiofile = sys.argv[3]

if mode == "train":
    print("loading audio input...")
    data, sample_rate = soundfile.read(audiofile)
    data = data[:,0] # extract the 0th channel
    
    print("preparing training dataset (please wait for train)...")
    xbuf = []
    ybuf = []
    for i in range(0, len(data) - (3 * sample_size), sample_size):
        xbuf.append(data[i : i + sample_size])
        ybuf.append(data[i + sample_size : i + (2 * sample_size)])    
    
    X = np.array(xbuf)
    y = np.array(ybuf)
    M = np.zeros((sample_size,))
    Mc = np.copy(M)
    
    print("training neural network (mind the gap)...")
    for i in range(math.floor(len(X))):
        #print(X[i].shape)
        #print(np.array(M).shape)
        #print(y[i].shape)
        lss = model.fit({"audio": np.array([X[i]]),\
                         "memo": np.array([M]),\
                         "memo-out": np.array([Mc]),\
                         "output": np.array([y[i]])})
        if i % 500:
            print("loss rate: " + str(lss))
        M = model.predict_on_batch({"audio": np.array([X[i]]),\
                                    "memo": np.array([M])})["memo-out"][0]
        #M = memolayer()
        print(M)
    #model.fit({"audio": X, "memo": X, "output": y}, batch_size = 1, nb_epoch = 1)
    
    print("saving weights...")
    model.save_weights(netfile, overwrite = True)
    
    exit(0)

if len(sys.argv) < 5:
    print(usage)
    exit(0)

outfile = sys.argv[4]

if mode == "synth":
    print("loading input file...")
    data, sample_rate = soundfile.read(audiofile)
    data = data[:,0]
    inp = data[:sample_size]
    outbuf = []
    
    M = np.zeros((sample_size,))    
    
    print("synthesizing sounds...")
    for i in range(10000):
        outp = model.predict_on_batch({"audio": np.array([inp]),\
                                        "memo": np.array([M])})
        outbuf += list(outp["output"][0])
        #print(outp[0][0])
        inp = outp["output"][0]
        #M = memolayer.get_output(train = False).eval()
        M = outp["memo-out"][0]
        #M = memolayer()
        #print(M)
        
    print("writing output file...")
    soundfile.write(outfile, outbuf, sample_rate)
    
elif mode == "test":
    print("not yet implemented")
else:
    print("no mode given")
    exit(0xdeadbeef)

# soundfile.write('new_file.ogg', data, samplerate)
