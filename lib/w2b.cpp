/*
 *            ____  _     
 *  __      _|___ \| |__  
 *  \ \ /\ / / __) | '_ \
 *   \ V  V / / __/| |_) |
 *    \_/\_/ |_____|_.__/ 
 *
 *   .wav to buffer tool
 *
 * It converts wavs to buffers.
 * Beerware licensed I guess
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include  <sndfile.h>
#include <fstream>
using namespace std;

#define HEADER_SIZE 44
#define NUM_CHANNELS 2

int getBuffer(unsigned int offset, char* input_filename,
              short int buffer[], const int buffer_size) {

  struct SF_INFO* info = new SF_INFO;
  info->format = 0;
  SNDFILE* input = sf_open(input_filename, SFM_READ, info);

  if (!input) return -1;

  sf_seek(input, offset, SEEK_SET);

  short int secondary_buffer[info->channels*buffer_size];


  int ret = sf_readf_short(input, secondary_buffer, buffer_size);

  for (int i=0; i<buffer_size; i++) {
    buffer[i] = secondary_buffer[info->channels*i];
  }

  sf_close(input);

  delete(info);

  return ret;
}

int writeBuffer(unsigned int offset, char* output_filename, short int buffer[], const int buffer_size) {
  struct SF_INFO* info = new SF_INFO;
  info->format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  info->channels = 1;
  info->samplerate = 8000;

  SNDFILE* output = sf_open(output_filename, SFM_WRITE, info);
  if (!output) return -1;

  sf_seek(output, offset, SEEK_SET);

  int ret = sf_write_short(output, buffer, buffer_size);
  sf_write_sync(output);

  sf_close(output);
  delete(info);
  return ret;
}
