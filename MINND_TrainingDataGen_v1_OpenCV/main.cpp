/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on March 18, 2016, 9:37 AM
 */

#include <cstdlib>
#include "main.h"

#define MAX_DN 0xFF
#define DATASET_SZ 10000

using namespace std;
using namespace cv;

/*
 * 
 */
int main(int argc, char** argv) {

    int channels = CHANNELS;
    int x_dim = SPATIAL_DIM;
    int lambda_dim = SPECTRAL_DIM;
    int outboard_sz = x_dim + lambda_dim - 1;

    /* Create new random number generator */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> spatial_dist(0, SPATIAL_DIM - 1);
    std::uniform_int_distribution<int> spectral_dist(0, SPECTRAL_DIM - 1);
    std::uniform_int_distribution<int> intensity_dist(0, MAX_DN);


    /* Allocate memory */
    float truth_cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0}; // randomly generated truth in x - lambda space
    float plus[outboard_sz];
    float zero[x_dim]; // Results of MOSES forward model
    float minus[outboard_sz];
    float input_cube[CHANNELS][SPECTRAL_DIM][SPATIAL_DIM] = {0}; // Combination of results to feed into bottom of CNN

    char base_filename[] = "/minnd/images/";
    char train_truth_img_dir[] = "/minnd/images/train/truth/";
    char train_input_img_dir[] = "/minnd/images/train/input/";
    char test_truth_img_dir[] = "/minnd/images/test/truth/";
    char test_input_img_dir[] = "/minnd/images/test/input/";

    char train_truth_index[] = "/minnd/images/train/truth/index.txt";
    char train_input_index[] = "/minnd/images/train/input/index.txt";
    char test_truth_index[] = "/minnd/images/test/truth/index.txt";
    char test_input_index[] = "/minnd/images/test/input/index.txt";


    ofstream train_truth_fp;
    ofstream train_input_fp;
    ofstream test_truth_fp;
    ofstream test_input_fp;
    train_truth_fp.open(train_truth_index);
    train_input_fp.open(train_input_index);
    test_truth_fp.open(test_truth_index);
    test_input_fp.open(test_input_index);
//    myfile << "Writing this to a file.\n";
//    myfile.close();

    for (int testing = 0; testing < 2; testing++) {
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

            /* Display truth image for testing */
            cv::Mat truth_image = cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, truth_cube[0]);
            //            cv::namedWindow("Truth Image", WINDOW_FREERATIO); // Create a window for display.
            //            cv::imshow("Truth Image", truth_image);

            /* Display input image for testing */
            cv::Mat input_image_chan[3] = {cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, input_cube[0]), cv::Mat(4, 4, CV_32FC1, input_cube[1]), cv::Mat(4, 4, CV_32FC1, input_cube[2])};
            cv::Mat input_image;
            cv::merge(input_image_chan, 3, input_image); // Merge channels into one image
            //            cv::namedWindow("Input Image", WINDOW_FREERATIO); // Create a window for display.
            //            cv::imshow("Input Image", input_image);

            /* write images to disk */
            char filename[100];
            if (testing) {
                
                sprintf(filename, "%s%08d.bmp", test_input_img_dir, count);
                test_input_fp << filename << " 0 \n";
                imwrite(filename, input_image);
                
                sprintf(filename, "%s%08d.bmp", test_truth_img_dir, count);
                test_truth_fp << filename << " 0 \n";
                imwrite(filename, truth_image);
                
            } else {
                
                sprintf(filename, "%s%08d.bmp", train_input_img_dir, count);
                train_input_fp << filename << " 0 \n";
                imwrite(filename, input_image);
                
                sprintf(filename, "%s%08d.bmp", train_truth_img_dir, count);
                train_truth_fp << filename << " 0 \n";
                imwrite(filename, truth_image);
                
            }

            cv::waitKey(0);

        }
    }
    
    train_truth_fp.close();
    train_input_fp.close();
    test_truth_fp.close();
    test_input_fp.close();
    




    return 0;
}

