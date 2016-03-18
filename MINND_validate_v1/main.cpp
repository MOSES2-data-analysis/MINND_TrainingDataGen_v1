
/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on March 15, 2016, 6:41 PM
 */

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "caffe/caffe.hpp"

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "params.h"
using std::string;
using namespace caffe;

void rot90(cv::Mat &matImage, int rotflag){
  //1=CW, 2=CCW, 3=180
  if (rotflag == 1){
    transpose(matImage, matImage);  
    flip(matImage, matImage,1); //transpose+flip(1)=CW
  } else if (rotflag == 2) {
    transpose(matImage, matImage);  
    flip(matImage, matImage,0); //transpose+flip(0)=CCW     
  } else if (rotflag ==3){
    flip(matImage, matImage,-1);    //flip(-1)=180          
  } else if (rotflag != 0){ //if not 0,1,2,3:
    std::cout  << "Unknown rotation flag(" << rotflag << ")" << std::endl;
  }
}

/*
 * 
 */
int main(int argc, char** argv) {

    /* input and output cubes */
    float input_cube[CHANNELS][SPATIAL_DIM][SPECTRAL_DIM] = {0};
    float scaled_input_cube[CHANNELS][SPATIAL_DIM][SPECTRAL_DIM];
    float output_cube[CHANNELS][SPATIAL_DIM][SPECTRAL_DIM];

    /* Set up directories */
    string model_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/minnd_deploy.prototxt";
    string trained_file = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_v1/MINND_v1_iter_100000.caffemodel";
    char input_path[] = "/home/byrdie/NetBeansProjects/MINND_TrainingDataGen_v1/MINND_TrainingDataGen_v1_cpp/training_data/cnn_cube.bin";

    /* Variable declaration */
    shared_ptr<Net<float> > net_; // Neural Network model
    int num_channels_;

    /* Enable GPU mode */
    Caffe::set_mode(Caffe::GPU);

    /* Load the network. */
    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);
    CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
    CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";

    /* Select the input layer from the network */
    Blob<float>* input_layer = net_->input_blobs()[0];
    num_channels_ = input_layer->channels();
    CHECK(num_channels_ == 3 || num_channels_ == 1) << "Input layer should have 1 or 3 channels.";

    
    /* Select the output layer from the network */
    Blob<float>* output_layer = net_->output_blobs()[0];
    std::cout << output_layer->shape(0) << " " << output_layer->shape(1) << " " << output_layer->shape(2) << std::endl;
    std::cout << output_layer->channels() << " " << output_layer->width() << " " << output_layer->height() << std::endl;
    /* Load validation image */
    FILE * fp = fopen(input_path, "rb");
    fread(input_cube, sizeof (float), CHANNELS * SPATIAL_DIM * SPECTRAL_DIM, fp);
    fclose(fp);

    /* Rescale validation image to range 0 - 1 */
    for (int i = 0; i < CHANNELS; i++) {
        for (int j = 0; j < SPECTRAL_DIM; j++) {
            for (int k = 0; k < SPATIAL_DIM; k++) {

                input_cube[i][j][k] /= MAX_DN;
                std::cout << input_cube[i][j][k] << "   ";
            }
            std::cout << std::endl;

        }

        std::cout << std::endl;
        std::cout << std::endl;

    }


    /* Display validation image for testing */
    cv::Mat image_chan[3] = {cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, input_cube[0]), cv::Mat(4, 4, CV_32FC1, input_cube[1]), cv::Mat(4, 4, CV_32FC1, input_cube[2])};

    /* Merge channels */
    cv::Mat image;
    cv::merge(image_chan, 3, image);

    /* Display input image */
    cv::namedWindow("Display window", cv::WINDOW_FREERATIO); // Create a window for display.
    cv::imshow("Display window", image);

    /* Wrap input layer to insert into network */
    std::vector<cv::Mat> input_channels;
    int width = input_layer->width();
    int height = input_layer->height();
    float* input_data = input_layer->mutable_cpu_data();
    for (int i = 0; i < input_layer->channels(); ++i) {

        cv::Mat channel(height, width, CV_32FC1, input_data);
        input_channels.push_back(channel);
        input_data += width * height;

    }

    
    /* This operation will write the separate BGR planes directly to the
     * input layer of the network because it is wrapped by the cv::Mat
     * objects in input_channels. */
    cv::split(image, input_channels);
    CHECK(reinterpret_cast<float*> (input_channels.at(0).data)
            == net_->input_blobs()[0]->cpu_data())
            << "Input channels are not wrapping the input layer of the network.";


    /* Check the input layer */
    for (int i = 0; i < SPATIAL_DIM; i++) {
        for (int j = 0; j < SPECTRAL_DIM; j++) {

            //            std::cout << input_layer->data_at(1, 1, i, j) << " ";
            std::cout << *(input_layer->cpu_data() + (i * SPATIAL_DIM) + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    /* Check ouput before to make sure forward pass actually does something */
    //    for (int i = 0; i < CHANNELS * SPATIAL_DIM * SPECTRAL_DIM; i++) {
    //        std::cout << *(output_layer->cpu_data() + i) * 255.0 << std::endl;
    //    }

    /* Run a forward pass of the Neural Network */
    net_->ForwardPrefilled();



    //    sleep(3);

    /* Copy the output layer to a std::vector */
    //    Blob<float>* output_layer = net_->output_blobs()[0];
    const float* begin = output_layer->cpu_data();
    const float* end = begin + output_layer->channels();
    const std::vector<float> output = std::vector<float>(begin, end);

    float output_row[CHANNELS * SPATIAL_DIM * SPECTRAL_DIM];

    for (int i = 0; i < CHANNELS * SPATIAL_DIM * SPECTRAL_DIM; i++) {


        output_row[i] = *(output_layer->cpu_data() + i) * 10.0;
        std::cout << output_row[i] << "   ";

    }
    std::cout << std::endl;
    std::cout << std::endl;


    //    for (int i = 0; i < CHANNELS; ++i) {
    for (int j = 0; j < SPECTRAL_DIM; ++j) {
        for (int k = 0; k < SPATIAL_DIM; ++k) {
            output_cube[0][j][k] = output_row[j + SPECTRAL_DIM * k];
            //                std::cout << output_cube[k][j][i] << "   ";
        }
    }
    //    }
    for (int j = 0; j < SPECTRAL_DIM; ++j) {
        for (int k = 0; k < SPATIAL_DIM; ++k) {
            output_cube[1][j][k] = output_row[j + SPECTRAL_DIM * k];
            //                std::cout << output_cube[k][j][i] << "   ";
        }
    }
    for (int j = 0; j < SPECTRAL_DIM; ++j) {
        for (int k = 0; k < SPATIAL_DIM; ++k) {
            output_cube[2][j][k] = output_row[j + SPECTRAL_DIM * k];
            //                std::cout << output_cube[k][j][i] << "   ";
        }
    }

    cv::Mat out_chan[CHANNELS] = {cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, output_cube[0]), cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, output_cube[1]), cv::Mat(SPATIAL_DIM, SPECTRAL_DIM, CV_32FC1, output_cube[2])};
    cv::Mat out_image;
    cv::merge(out_chan, 3, out_image);
//    rot90(out_image,2);
    cv::flip(out_image, out_image, 1);
    
    /* Display input image */
//    cv::namedWindow("Output window", cv::WINDOW_FREERATIO); // Create a window for display.
//    cv::namedWindow("Output window 1", cv::WINDOW_FREERATIO); // Create a window for display.
//    cv::namedWindow("Output window 2", cv::WINDOW_FREERATIO); // Create a window for display.
    cv::namedWindow("Output window 3", cv::WINDOW_FREERATIO); // Create a window for display.


//    cv::imshow("Output window", out_chan[0]);
//    cv::imshow("Output window 1", out_chan[1]);
//    cv::imshow("Output window 2", out_chan[2]);
    cv::imshow("Output window 3", out_image);



    cv::waitKey(0);

    return 0;
}

