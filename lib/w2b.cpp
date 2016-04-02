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
#include <fstream>
using namespace std;

#define HEADER_SIZE 44
#define NUM_CHANNELS 2

int getBuffer(unsigned int offset, char* input_filename,
              short int buffer[], const int buffer_size) {
  offset += HEADER_SIZE;
  FILE* input = fopen(input_filename, "rb");
  
  if (input) {
    short int secondary_buffer[NUM_CHANNELS*buffer_size];
    fseek(input, offset, SEEK_SET);
    if (feof(input)) return 0;
    int ret = fread(secondary_buffer, sizeof(short int), NUM_CHANNELS*buffer_size, input);
    ret = ret/2;

    for (int i=0; i<ret/NUM_CHANNELS; i++) {
      //this strips out to 1 channel
      buffer[i] = secondary_buffer[NUM_CHANNELS*i];
    }
    fclose(input);
    return ret;
  }
  else {
    return -1;
  }
}

int writeEmptyWav(char* input_filename, char* output_filename) {
  FILE* input = fopen(input_filename, "rb");
  FILE* output = fopen(output_filename, "wb");

  if ((!input) || (!output)) return 1;

  char buff[44];
  fread(buff, 1, 44, input);
  fwrite(buff, sizeof(char), sizeof(buff), output);
  fclose(input);
  fclose(output);

  return 0;
}

int writeBuffer(unsigned int offset, char* output_filename, short int buffer[], const int buffer_size) {
  offset += HEADER_SIZE;
  FILE* output = fopen(output_filename, "wb");

  if (!output || !buffer_size) return -1;

  short int secondary_buffer[NUM_CHANNELS*buffer_size];

  //duplicate the channels into the secondary buffer
  for (int i=0; i<buffer_size; i++) {
    for (int j=0; j<NUM_CHANNELS; j++) {
      secondary_buffer[i*NUM_CHANNELS + j] = buffer[i];
    }
  }

  fseek(output, offset, SEEK_SET);
  int ret = fwrite(secondary_buffer, sizeof(short int), NUM_CHANNELS*buffer_size, output);
  fclose(output);

  return ret;
}
