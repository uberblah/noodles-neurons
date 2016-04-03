# noodles-neurons - JUNK
This directory contains all of the code, tools, and other good stuff, that we created before landing at our final version. It also includes an early version of our neural network, which was contained in a c++ implementation. It will produce the kinds of files that you hear in ../output\_songs/out\*.wav, and we were able to get a faint beat out of it, but nothing resembling a melody. We abandoned this because we believed a recurrent network is what we needed to get music. All we found about RNNs and FANN was contained in a project that seems like it never got ground [here](https://sourceforge.net/p/fann/discussion/323465/thread/fd022697/).

## wav tools
### install
First, install libsndfile:

http://www.mega-nerd.com/libsndfile/

Then copy either `Makefile_Linux` or `Makefile_Mac` to just `Makefile`

Then run "make"

Then run `wav2f ../wavs/test.wav > test.txt` and then `f2wav test.txt`

You should get `out.wav` which should **SOUND** the same as `test.wav`, which is a simple sine wave. If you run diff on it it will not BE the same, because wav2f strips the audio to 1 channel.

There you have it. Have fun.

### wav tool usage
`wav2f <in_file> > <out_file>`
 * wav2f takes in a file as an argument and outputs each sample on a new line to stdout.

`f2wav <in_file>`
 * f2wav takes in a .txt in the wav2f format and outputs a resulting .wav file to out.wav. It will overwrite out.wav

## nn
