
/* getBuffer is the meat and potato of this lib. It reads a .wav file and
 * outputs the samples to a given buffer. Pretty simple.
 *
 * Inputs:
 *  - offset (if you don't want to read the first byte) -- 0 starts at the beginning of the music
 *  - input_filename - char* array for the filename
 *  - buffer[] - the destination buffer (where you want the data to be read)
 *  - buffer_size - the size of that definition buffer
 *
 * returns the amount read if successful, -1 if something went wrong,
 * and 0 if you are at the end of the file
 */

int getBuffer(unsigned int offset, char* input_filename, short int buffer[], const int buffer_size);
