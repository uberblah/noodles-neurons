#include <fann.h>
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUM_IN_OUT 256
#define MAX_ITERATIONS 50000
#define ERROR 0.001

int main(int argc, char* argv[]) {
    bool iflag, oflag, tflag, nflag, gflag;
    int flag;
    struct fann *nNetwork;
    char* inputFileName;
    char* dataFileName;
    char* outputFileName;

    srand(time(NULL));

    while((flag = getopt(argc,argv,"i:o:t:")) != -1) {
        switch(flag) {
            case 'i':
                inputFileName = optarg;
                iflag = true;
            break;
            case 'o':
                outputFileName = optarg;
                oflag = true;
            break;
            case 't':
                dataFileName = optarg;
                tflag = true;
            break;
        }
    }

    if(iflag) {
        nNetwork = fann_create_from_file(inputFileName);
    }
    else {
        nNetwork = fann_create_standard(3,NUM_IN_OUT,NUM_IN_OUT,NUM_IN_OUT);
    }

    fann_set_activation_function_hidden(nNetwork, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(nNetwork, FANN_SIGMOID_SYMMETRIC);

    if(tflag) {
        fann_train_on_file(nNetwork,dataFileName,MAX_ITERATIONS,50,ERROR);
    }

    if(oflag) {
        fann_save(nNetwork,outputFileName);
    }

    fann_destroy(nNetwork);
return 0;
}
