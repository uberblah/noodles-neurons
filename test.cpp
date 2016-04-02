#include <iostream>
#include "lib/w2b.h"
using namespace std;

int main() {
  //test
  short int buffer[256];
  int ret = 256;
  int offset = 0;
  int reta = 0;

  while (ret >= 256) {
    ret = getBuffer(offset, "test.wav", buffer, 256);
    for (int i=0; i<ret; i++) cout << buffer[i] << endl;
    reta = writeBuffer(offset, "out.wav", buffer, ret);
    offset += ret;
  }

  return 0;
}
