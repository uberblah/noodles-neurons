
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

/* writeEmptyWav copies headers from an input file to an output file.
 * Needed for a valid .wav file.
 *
 * Inputs:
 *  - input_filename: the input file
 *  - output_filename: the output file
 *
 * Returns a 1 if there is an error in the file reads/writes
 */
int writeEmptyWav(char* input_filename, char* output_filename);

/* writeBuffer, getBuffer's dumb friend.
 * JK writeBuffer, we still love you.
 *
 * It writes a buffer to a file in .wav format, so use it on a file
 * that you've already used writeEmptyWav on.
 *
 * Inputs:
 *  - offset: where to start writing
 *  - output_filename: the filename of the output file
 *  - buffer[]: the buffer to write out
 *  - buffer_size: the length of the buffer
 *
 * It will return the amount written, or -1 for errors
 */
int writeBuffer(unsigned int offset, char* output_filename, short int buffer[], const int buffer_size);
