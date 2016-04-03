#include <iostream>
#include <fstream>
#include "lib/w2b.h"
using namespace std;

#define BUFFERSIZE 1000000

int main(int argc, char* argv[]) {
  string buffone;
  short int bufftwo[BUFFERSIZE];
  int index = 0;
  ifstream ourFile;

  ourFile.open(argv[1]);

  while (getline(ourFile, buffone)) {
    if (index >= BUFFERSIZE) {
      break;
    }
    bufftwo[index] = stoi(buffone);
    index++;
  }

  writeBuffer(0, "out.wav", bufftwo, index + 1);

  return 0;
}
