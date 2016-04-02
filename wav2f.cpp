#include <iostream>
#include "lib/w2b.h"
using namespace std;

int main(int argc, char* argv[]) {
  //test
  short int buffer[256];
  int ret = 256;
  int offset = 0;

  while (ret >= 256) {
    ret = getBuffer(offset, argv[1], buffer, 256);
    for (int i=0; i<ret; i++) cout << buffer[i] << endl;
    offset += ret;
  }


  return 0;
}
