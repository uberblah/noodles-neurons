#include "fann.h"

#define LAYERSIZE 256

int main()
{
    const unsigned int num_layers = 3;
    const unsigned int num_input = LAYERSIZE;
    const unsigned int num_neurons_hidden = LAYERSIZE;
    const unsigned int num_output = LAYERSIZE;
    const float desired_error = (const float) 0.0005;
    const unsigned int max_epochs = 500000;
    const unsigned int epochs_between_reports = 100;

    struct fann *ann = fann_create_standard(num_layers, num_input,
					    num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, "sin.data", max_epochs,
		       epochs_between_reports, desired_error);

    fann_save(ann, "sin_float.net");

    fann_destroy(ann);

    return 0;
}

/*
     *

   * * *
 / |X|X|\
 | | | | |

 */
