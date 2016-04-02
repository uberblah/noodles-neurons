#include <floatfann.h>
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define SCALE_FACTOR 32767.0f
#define NUM_IN_OUT 512
#define NUM_LAYERS 3
#define MAX_ITERATIONS 50000
#define ERROR 0.001f
#define ACTIVATION FANN_GAUSSIAN
#define LEARNING_RATE 0.9f

int main(int argc, char* argv[]) {
    int flag;
    struct fann *nNetwork;
    char* loadFileName = NULL;
    char* saveFileName = NULL;
    char* inputFileName = NULL;
    char* outputFileName = NULL;
    char* trainFileName = NULL;
    //i -> input data
    //o -> output data
    //l -> load network
    //s -> save network
    //t -> train network
    bool iflag, oflag, lflag, sflag, tflag;

    srand(time(NULL));

    while((flag = getopt(argc,argv,"l:s:i:o:t:")) != -1) {
        switch(flag) {
	case 'l':
	    loadFileName = optarg;
	    lflag = true;
            break;
	case 'o':
	    outputFileName = optarg;
	    oflag = true;
	    break;
	case 's':
	    saveFileName = optarg;
	    sflag = true;
            break;
	case 'i':
	    inputFileName = optarg;
	    iflag = true;
            break;
	case 't':
	    trainFileName = optarg;
	    tflag = true;
	    break;
        }
    }

    if(lflag) {
        nNetwork = fann_create_from_file(loadFileName);
    }
    else {
        nNetwork = fann_create_standard(NUM_LAYERS, NUM_IN_OUT, NUM_IN_OUT, NUM_IN_OUT);
	fann_set_activation_function_hidden(nNetwork, ACTIVATION);
	fann_set_activation_function_output(nNetwork, ACTIVATION);
	fann_set_learning_rate(nNetwork, LEARNING_RATE);
    }

    if(tflag) {
	FILE* tfile = fopen(trainFileName, "r");
	fann_type* input = (fann_type*)malloc(sizeof(fann_type) * NUM_IN_OUT);
	fann_type* output = (fann_type*)malloc(sizeof(fann_type) * NUM_IN_OUT);

	int offset = rand() % NUM_IN_OUT;
	for(int i = 0; i < offset; i++)
	{
	    int x = 0;
	    fscanf(tfile, "%d\n", &x);
	}
	printf("\n");

	for(int i = 0; i < NUM_IN_OUT; i++)
	{
	    int x = 0;
	    while(x == 0)
	    {
		int s = fscanf(tfile, "%d\n", &x);
		if(s < 1)
		{
		    printf("not enough samples to train on\n");
		    exit(1);
		}
		input[i] = (float)x / SCALE_FACTOR;
	    }
	}
	for(int i = 0; i < NUM_IN_OUT; i++)
	{
	    int x = 0;
	    while(x == 0)
	    {
		int s = fscanf(tfile, "%d\n", &x);
		if(s < 1)
		{
		    printf("not enough samples to train on\n");
		    exit(1);
		}
		output[i] = (float)x / SCALE_FACTOR;
	    }
	}

	bool training = true;
	while(training)
	{
	    fann_train(nNetwork, input, output);
	    fann_type* swapper = input;
	    input = output;
	    output = swapper;
	    for(int i = 0; i < NUM_IN_OUT && training; i++)
	    {
		int x = 0;
		while(x == 0)
		{
		    int s = fscanf(tfile, "%d\n", &x);
		    if(s < 1)
		    {
			printf("training reached end of file\n");
			training = false;
			break;
		    }
		}
		output[i] = (float)x / SCALE_FACTOR;
	    }
	}

	free(input);
	free(output);

	fclose(tfile);

	printf("MSE: %f\n", fann_get_MSE(nNetwork));
	
        //fann_train_on_file(nNetwork, trainFileName, MAX_ITERATIONS, 50, ERROR);
    }

    if(sflag) {
        fann_save(nNetwork, saveFileName);
    }

    if(iflag) {
	FILE* infile = fopen(inputFileName, "r");
	fann_type* input = (fann_type*)malloc(sizeof(fann_type) * NUM_IN_OUT);
	for(int i = 0; i < NUM_IN_OUT; i++)
	{
	    int x = 0;
	    while(x == 0)
	    {
		int s = fscanf(infile, "%d\n", &x);
		if(s < 1)
		{
		    printf("not enough samples to run on\n");
		    exit(1);
		}
		input[i] = (float)x / SCALE_FACTOR;
	    }
	}
	fclose(infile);

	FILE* outfile = oflag ? fopen(outputFileName, "w") : stdout;
	for(int i = 0; i < 10000; i++)
	{
	    fann_type* output = fann_run(nNetwork, input);
	    for(int j = 0; j < NUM_IN_OUT; j++)
	    {
		fprintf(outfile, "%d\n", (int)(output[j] * SCALE_FACTOR));
		input[j] = output[j];
	    }
	}
	fclose(outfile);
	free(input);
    }

    fann_destroy(nNetwork);
return 0;
}
