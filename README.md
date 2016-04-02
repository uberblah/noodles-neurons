# noodles-neurons

## wav tools instructions
First, install libsndfile:

http://www.mega-nerd.com/libsndfile/

Then, edit "Makefile" to point to where your libsndfile lives (instead of /usr/local lib after -I and -L)

Then run "make"

Then run `wav2f wavs/prologue_8k.wav > test.txt` and then `f2wav test.txt`

You should get `out.wav` which should **SOUND** the same as `prologue_8k.wav`. If you run diff on it it will not BE the same, because wav2f strips the audio to 1 channel.

There you have it. Have fun.
