#include <iostream>
#include "lib/w2b.h"
using namespace std;

int main() {
  //test
  short int buffer[256];
  cout << getBuffer(0, "test.wav", buffer, 256) << endl;

  for (int i=0; i<256; i++) cout << buffer[i] << endl;

  return 0;
}
