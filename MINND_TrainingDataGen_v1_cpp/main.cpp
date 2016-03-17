/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "main.h"

#define MAX_DN 0xFF
#define DATASET_SZ 100000


using namespace std;

int main(int argc, char** argv) {

    /* Test function to generate single image */
    single_image_gen();
    
//    dataset_gen();



}

void dataset_gen() {
    int channels = CHANNELS;
    int x_dim = SPATIAL_DIM;
    int lambda_dim = SPECTRAL_DIM;
    int outboard_sz = x_dim + lambda_dim - 1;

    /* Create new random number generator */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> spatial_dist(0, SPATIAL_DIM - 1);
    std::uniform_int_distribution<int> spectral_dist(0, SPECTRAL_DIM - 1);
    std::uniform_int_distribution<int> intensity_dist(50, MAX_DN);


    /* Allocate memory */
    float truth_cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0}; // randomly generated truth in x - lambda space
    float plus[outboard_sz];
    float zero[x_dim]; // Results of MOSES forward model
    float minus[outboard_sz];
    float input_cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0}; // Combination of results to feed into bottom of CNN

    /* Open database for storing input and truth data sets */
    char db_input_path[] = "training_data/minnd_input_LMBD";
    char db_truth_path[] = "training_data/minnd_truth_LMBD";
    open_input_db(db_input_path);
    open_truth_db(db_truth_path);


    for (int count = 0; count < DATASET_SZ; count++) {

        memset(truth_cube, 0, channels * x_dim * lambda_dim * sizeof (int));

        /* Draw new X, Y and intensity values */
        int x = spatial_dist(generator); // generates number in the range 0 ... MAX_DN
        int y = spectral_dist(generator);
        float I = intensity_dist(generator);

        /* Activate randomized pixel */
        truth_cube[PLUS][y][x] = I;
        truth_cube[ZERO][y][x] = I;
        truth_cube[MINUS][y][x] = I;

        /* Execute MOSES forward model */
        fomod(plus, zero, minus, truth_cube);

        /* Execute reverse forward model to put in format for Neural Network */
        reverse_fomod(plus, zero, minus, input_cube);

        add_to_input_db(count, input_cube);
        add_to_truth_db(count, truth_cube);

    }

    close_input_db();
    close_truth_db();
}

void single_image_gen() {
    int channels = CHANNELS;
    int x_dim = SPATIAL_DIM;
    int lambda_dim = SPECTRAL_DIM;
    int total_pix = SPATIAL_DIM * SPECTRAL_DIM;

    /* Create new random number generator */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> spatial_dist(0, SPATIAL_DIM - 1);
    std::uniform_int_distribution<int> spectral_dist(0, SPECTRAL_DIM - 1);
    std::uniform_int_distribution<int> intensity_dist(50, MAX_DN);

    /* Draw new X, Y and intensity values */
    int x = spatial_dist(generator); // generates number in the range 0 ... MAX_DN
    int y = spectral_dist(generator);
    float I = intensity_dist(generator);

    std::cout << " " << x << " " << y << " " << I << "\n";


    /* Allocate memory for the input cube */
    float cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0};

    /* Activate randomized pixel */
    cube[PLUS][y][x] = I;
    cube[ZERO][y][x] = I;
    cube[MINUS][y][x] = I;

    /* Save cube to disk */
    char cube_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/cube.bin";
    FILE * fp = fopen(cube_path, "wb");
    fwrite(cube, sizeof (float), total_pix*channels, fp);
    fclose(fp);

    /* Plot input cube for testing */
    Gnuplot g0;
    char cmd_str[200];
    sprintf(cmd_str, "plot '%s' binary array=(%d,%d) ", cube_path, x_dim, lambda_dim);
    strcat(cmd_str, " rotation=-90d format='%int%int%int' with rgbimage");
    //    printf(cmd_str);
    g0.cmd(cmd_str);

    /* Allocate space for results of MOSES forward model */
    int outboard_sz = x_dim + lambda_dim - 1;
    float plus[outboard_sz];
    float zero[x_dim];
    float minus[outboard_sz];

    /* Execute MOSES forward model */
    fomod(plus, zero, minus, cube);

    /* Save results of forward model to disk */
    /* Zero order */
    char zero_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/zero.bin";
    fp = fopen(zero_path, "wb");
    fwrite(zero, sizeof (int), x_dim, fp);
    fclose(fp);
    /* Positive Order*/
    char plus_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/plus.bin";
    fp = fopen(plus_path, "wb");
    fwrite(plus, sizeof (int), outboard_sz, fp);
    fclose(fp);
    /* Positive Order*/
    char minus_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/minus.bin";
    fp = fopen(minus_path, "wb");
    fwrite(minus, sizeof (int), outboard_sz, fp);
    fclose(fp);

    Gnuplot g1("lines"), g2("lines"), g3("lines");

    /* Plot the result on each of the three detectors */
    sprintf(cmd_str, "plot '%s' binary array=(%d) format='%%int' with lines", zero_path, x_dim);
    g1.set_title("m = 0 Image");
    g1.cmd(cmd_str);
    sprintf(cmd_str, "plot '%s' binary array=(%d) format='%%int' with lines", plus_path, outboard_sz);
    g2.set_title("m = 1 Image");
    g2.cmd(cmd_str);
    sprintf(cmd_str, "plot '%s' binary array=(%d) format='%%int' with lines", minus_path, outboard_sz);
    g3.set_title("m = -1 Image");
    g3.cmd(cmd_str);


    /* Execute reverse forward model to put in format for Neural Network */
    float cnn_cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0};
    memset(cnn_cube, 0, channels * x_dim * lambda_dim * sizeof (float));
    reverse_fomod(plus, zero, minus, cnn_cube);

    /* Save CNN input cube to disk */
    char cnn_cube_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/cnn_cube.bin";
    fp = fopen(cnn_cube_path, "wb");
    fwrite(cnn_cube, sizeof (float), total_pix*channels, fp);
    fclose(fp);

    /* Plot input cube for testing */
    sprintf(cmd_str, "plot '%s' binary array=(%d,%d) ", cnn_cube_path, x_dim, lambda_dim);
    strcat(cmd_str, " rotation=-90d format='%int%int%int' with rgbimage");
    //    printf(cmd_str);
    Gnuplot g4;
    g4.cmd(cmd_str);

    /* Stop program until we're finished looking at the results */
    pause();
}