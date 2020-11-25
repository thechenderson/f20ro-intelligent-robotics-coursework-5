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
 #include <memory>

#include <opencv2/opencv.hpp>

 #include "imageFormatConverter.hpp"
 #include "faceHighlighting.hpp"

    using namespace yarp::sig;
    using namespace yarp::os;

    // Data for initialising the face boxing algorithm
    const std::string haar_cascade_data_filename = "haarcascade_frontalface_default.xml";  //"/home/user/software/git/opencv/data/haarcascades/haarcascade_frontalface_default.xml";


    int main(int argc, char *argv[])
    {


        // Network construction here allows for the use of ports
        Network yarp;

        // initialise the face boxing algorithm
        const std::shared_ptr<cv::CascadeClassifier> haarCascade;
        haarCascade->load(haar_cascade_data_filename);

        BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
        BufferedPort<ImageOf<PixelRgb> > outPort;

        imagePort.open("/faceDetection/in");  // give the port a name
        outPort.open("/faceDetection/out");
        
        while (1) { // repeat forever
            ImageOf<PixelRgb> *image = imagePort.read();  // read an image
            ImageOf<PixelRgb> &outImage = outPort.prepare(); //get an output image

            if (image!=nullptr) { // check we actually got something

                // convert to OpenCV format
                cv::Mat cvImage = coursework::toCvMat(*image);

                // actual work
                auto faced_image = coursework::recogniseAndBoxFaces(haarCascade, cvImage);

                // return to yarp format
                outImage = coursework::fromCvMat(faced_image);
                outPort.write();
            }
       }
   return 0;
   }



