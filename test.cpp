#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <fstream>
#include "w2b.h"
using namespace std;

int main() {
  //test
  short int buffer[256];

  getBuffer(0, "test.wav", buffer, 256);

  for (int i=0; i<256; i++) {
    cout << buffer[i] << endl;
  }

  return 0;
}
