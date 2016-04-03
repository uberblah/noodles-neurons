# noodles & neurons
![noodles](http://i.imgur.com/lM2IvHZ.jpg)

## What
This is noodles & neurons, a "music generator" based off of a neural network. It trains a neural network off of .wav files and then uses a .wav file to attempt to generate more music. It does generate music, but the music is not in some's tastes. All I can say is that my noodles & neurons outputs aren't going on my ipod anytime soon.

The 2 versions of noodles & neurons were built in C++ (first) and python (2nd). Our C++ library ran into limitations in that we could not build an RNN, which we believed would help us get a more accurate result. It works, but produces fairly simple tones.

## Why
We wanted to learn about neural networks, and audio, while difficult to get right, is easy to deal with in a simple input & output sense. We take in samples and output samples, producing a real, listenable result. The only way we completely fail is by generating 0's. All in all, it was a good learning experience, but we hit our fair share of roadblocks along the way.

## Challenges
Neural networks are hard. I'm just gonna say it. The people who do what we are doing and do it well have PHDs and years of experience. We had a Wikipedia and Youtube based knowledge and 36 hours. What we got sure passes as audio, and was music to our ears. With enough tweaking and training, we might be able to get something listenable out of our bot.

The biggest problem we ran into was our depth of knowledge. To create a sound is one thing, but to create a beat is a much more difficult thing. We simply don't have the resources and knowledge required in order to make the right adjustments to our NN to get a better result.

On top of this, because of our computing power, we were limited to looking at a small amount of samples (256) at a time. If we were able to look at more samples, it's likely we would get a better result.

#RUN!
## get ready to run
```bash
sudo pip install keras pydot soundfile Cython
sudo apt-get install hdf5-dev # or similar if you're not using Ubuntu
sudo pip install h5py
cd webapp
npm install
cd ..
./learning.py new out.net
```

## run!
You can run simple.py as well, but it's, uh, simpler. You can also output to not /dev/null, but there's a lot of output.
```bash
./learning.py train out.net wavs/glass.wav > /dev/null
./learning.py synth out.net wavs/glass.wav out.wav
```

## webapp!
The webapp trains the neural network on the uploaded wav and returns the result. We didn't have time to make it perfect, so it just spins while the network is training and synthesizing at the moment.

```bash
# train once
./learning.py train out.net wavs/glass.wav
node webapp/app.js
```

Then navigate to `localhost:3031`

