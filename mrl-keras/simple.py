#!/usr/bin/env python

from keras.models import Sequential
from keras.layers.core import Dense
from keras.layers.normalization import BatchNormalization
from keras.optimizers import SGD

import numpy as np
import soundfile as sf

import sys

chunk_size = 8
chunk_history = 128
synth_time = 30 #seconds

# usage string, for silly users and developers such as ourselves
usage = "./simple new <net-out>\n" +\
        "./simple train <net-file> <audio-file>\n" +\
        "./simple synth <net-file> <audio-in> <audio-out>\n" +\
        "./simple test <net-file> <audio-file> <audio-out>\n"

# check argument count
if len(sys.argv) < 3:
    print(usage)
    exit(0)

# get basic arguments
mode = sys.argv[1]
netfile = sys.argv[2]

# build the model
print("building model...")
model = Sequential()
model.add(Dense(chunk_size * chunk_history,\
        input_dim = chunk_size * chunk_history))
model.add(BatchNormalization())
model.add(Dense(chunk_size * chunk_history / 2))
model.add(Dense(chunk_size * chunk_history / 4))
model.add(Dense(chunk_size * chunk_history / 8))
model.add(Dense(chunk_size * chunk_history / 4))
model.add(Dense(chunk_size * chunk_history / 2, activation = "softmax"))
model.add(Dense(chunk_size))

# save the model if we're done
if mode == "new":
    print("saving model weights...")
    model.save_weights(netfile, overwrite = True)
    exit(0)

# are we prepared for this???
if len(sys.argv) < 4:
    print(usage)
    exit(0)

# compile the model for training and execution
print("compiling model...")
model.compile(SGD(), "mean_squared_error")

# load weights if available
print("loading weights...")
model.load_weights(sys.argv[2])
audiofile = sys.argv[3]

if mode == "train":
    print("loading audio input...")
    data, sample_rate = sf.read(audiofile)
    data = data[:,0]
    xbuf = []
    ybuf = []
    
    step = chunk_size
    print("preparing training dataset...")
    a = 0
    b = chunk_size * chunk_history
    c = b + chunk_size
    while a < (len(data) - (chunk_size * (chunk_history + 1))):
        xbuf.append(data[a : b])
        ybuf.append(data[b : c])
        a += step
        b += step
        c += step
    
    xbuf = np.array(xbuf)
    ybuf = np.array(ybuf)
        
    print("training model...")
    model.fit(np.array(xbuf), np.array(ybuf), nb_epoch = 1, batch_size = 32)
    
    print("saving model...")
    model.save_weights(netfile, overwrite = True)    
    
    exit(0)

if len(sys.argv) < 5:
    print(usage)
    exit(0)

outfile = sys.argv[4]

if mode == "synth":
    print("loading audio input...")
    data, sample_rate = sf.read(audiofile)
    data = data[:,0]
    sf.write("test.wav", data, sample_rate)
    
    outbuf = []        
    
    print("synthesizing audio...")
    inp = data[:chunk_size * chunk_history]
    for i in range(10000):
        outp = model.predict_on_batch(np.array([inp]))
        outp = outp[0][0]
        outbuf += list(outp)
        #inp = data[i * chunk_size :\
        #    (i * chunk_size) + (chunk_size * chunk_history)]
        for j in range(chunk_size * (chunk_history - 1)):
            inp[j] = inp[j + chunk_size]
        for j in range(chunk_size):
            inp[j + (chunk_size * (chunk_history - 1))] = outp[j]
    
    print("writing audio output...")
    sf.write(outfile, np.array(outbuf), sample_rate)

elif mode == "test":
    print("not yet implemented")
else:
    print("nah")
    exit(0xdeadbeef)
