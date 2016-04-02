#include <iostream>
#include "lib/w2b.h"
using namespace std;

int main() {
  //test
  short int buffer[256];
  int offset = 0;
  writeEmptyWav("test.wav", "out.wav");

  int ret = 5505;
  int count = 0;
  int retb = 0;

  while (ret >= 256*2) {
    ret = getBuffer(offset, "test.wav", buffer, 256);
    count += ret;
    if (ret == 256*2) {
      retb = writeBuffer(offset, "out.wav", buffer, ret);
    }
    offset += 256*2;
  }

  cout << "count: " << count << endl;
  cout << "count2: " << retb << endl;
  return 0;
}
