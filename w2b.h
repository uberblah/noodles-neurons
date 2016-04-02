
/* getBuffer is the meat and potato of this lib
 * OK ITS THE WHOLE LIB
 * WHY ARE YOU BEING SO SASSY
 *
 * Inputs:
 *  - offset (if you don't want to read the first byte) -- 0 starts at the beginning of the music
 *  - input_filename - char* array for the filename
 *  - buffer[] - the destination buffer (where you want the data to be read)
 *  - buffer_size - the size of that definition buffer
 *
 * Returns a 1 if you are at the end of the file, 0 otherwise
 */

int getBuffer(unsigned int offset, char* input_filename, short int buffer[], const int buffer_size);
