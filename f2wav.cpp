#include <iostream>
#include "lib/w2b.h"
using namespace std;

//#define BUFFERSIZE 10000000
#define BUFFERSIZE 1000000

int main(int argc, char* argv[]) {
  for (int i=1; i<argc; i++) {
    FILE* filp = fopen(argv[i], "rb" );
    if (!filp) {return 1;}

    char* buffer = new char[BUFFERSIZE];
    int read = fread(buffer, sizeof(char), BUFFERSIZE, filp);
    fclose(filp);

    cout << read << endl;
    short buffer_edited[read/2];
    int count = 0;
    char arr[6] = {0,0,0,0,0,0};
    int arrcount = 0;

    for (int j=0; j<read; j++) {
      if (buffer[j] == '\n') {
        std::string str(arr);
        buffer_edited[count] = stoi(str);
        //cout << "str: " << str << " | num: " << buffer_edited[count] << endl;
        //buffer_edited[count] = dec_converter(arr);
        count++;
        for (int k=0; k<6; k++) arr[k] = 0;
        arrcount = 0;
      }
      else {
        arr[arrcount] = buffer[j];
        arrcount++;
      }
    }

    //for (int j=0; j<count; j++) cout << buffer_edited[j] << endl;

   writeBuffer(0, "out.wav", buffer_edited, count);
  }

  return 0;
}
