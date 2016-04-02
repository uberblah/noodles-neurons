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
 *
 * code is heavily modified from this:
 * http://stackoverflow.com/questions/20028389/reading-audio-file-in-c
 * (the only thing kept was their header struct and reading method)
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define HEADER_SIZE 44

typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} header;

typedef struct header_file* header_p;

int getBuffer(unsigned int offset, char* input_filename,
              short int buffer[], const int buffer_size) {
  offset += HEADER_SIZE;
  FILE* input = fopen(input_filename, "rb");
  header_p meta = (header_p)malloc(sizeof(header));

  
  if (input) {
    fread(meta, 1, sizeof(header), input);
    short int secondary_buffer[meta->num_channels*buffer_size];
    fseek(input, offset, SEEK_SET);
    if (feof(input)) {
      return 1;
    }
    fread(secondary_buffer, 1, buffer_size, input);
    for (int i=0; i<buffer_size; i+=meta->num_channels) {
      //this strips out to 1 channel
      buffer[i] = secondary_buffer[i];
    }
  }
  return 0;
}
