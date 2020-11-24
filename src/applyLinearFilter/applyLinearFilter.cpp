// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
/*
 * Edge detection using the a convolutional filter with the Sobel operator.
 * Author for F21IRO @ Hamish MacKinnon, him2
 */

 #include <stdio.h>
 #include <yarp/os/Network.h>
 #include <yarp/os/BufferedPort.h>
 #include <yarp/sig/Image.h>
 #include <yarp/sig/Vector.h>
 #include <yarp/os/Time.h>
 #include <yarp/os/Property.h>
 #include <string>



 #include <yarp/cv/Cv.h>
 #include <opencv2/opencv.hpp>
// #include "imageFormatConverter.hpp"

    using namespace yarp::sig;
    using namespace yarp::os;

    // parameter for the Sobel filtering operation
    const auto ddepth = CV_16S;    // number of bits per pixel for colour depth

    int main(int argc, char *argv[])
    {


        // Network construction here allows for the use of ports
        Network yarp;

        BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
        BufferedPort<ImageOf<PixelMono> > outPort;

        imagePort.open("/imageProc/edgeDetection/in");  // give the port a name
        outPort.open("/imageProc/edgeDetection/out");
        
        while (1) { // repeat forever
            ImageOf<PixelRgb> *image = imagePort.read();  // read an image
            ImageOf<PixelMono> &outImage = outPort.prepare(); //get an output image

            if (image!=nullptr) { // check we actually got something

                // convert to OpenCV format
//                cv::Mat cvImage = coursework::toCvMat(*image);
                cv::Mat cvImage = yarp::cv::toCvMat(*image);

                // remove noise using a blur, then remove colour
                cv::Mat blurredImg;
                cv::GaussianBlur(cvImage, blurredImg, cv::Size(3, 3), 0, 0);

                cv::Mat grayscaleImg;
                cv::cvtColor(blurredImg, grayscaleImg, cv::COLOR_BGR2GRAY);

                // detect edges!
                cv::Mat x_derivatives, y_derivatives;
                cv::Sobel(grayscaleImg, x_derivatives, ddepth, 1, 0);
                cv::Sobel(grayscaleImg, y_derivatives, ddepth, 0, 1);

                // Approximate the true edges as a sum of x and y changes
                // Directions of derivatives don't matter, so remove the sign then combine.
                cv::Mat abs_x_derivatives, abs_y_derivatives;
                cv::convertScaleAbs(x_derivatives, abs_x_derivatives);
                cv::convertScaleAbs(y_derivatives, abs_y_derivatives);

                cv::Mat edges;
                const float dimension_weight = 0.5;
                cv::addWeighted(abs_x_derivatives, dimension_weight, abs_y_derivatives, dimension_weight, 0, edges);

                // return to yarp format
//                outImage = coursework::fromCvMat<PixelMono>(edges);
                outImage = yarp::cv::fromCvMat<PixelMono>(edges);
                outPort.write();
            }
       }
   return 0;
   }

