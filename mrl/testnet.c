#include <stdio.h>
#include <math.h>
#include "floatfann.h"

#define POSTMUL 32767

int main()
{
    fann_type *calc_out;
    fann_type input[128];

    struct fann *ann = fann_create_from_file("sin_float.net");

    calc_out = fann_run(ann, input);

    printf("xor test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);

    fann_destroy(ann);
    return 0;
}
