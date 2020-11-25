/*
 * Face detection using a pretrained Haar Cascade.
 * The approach taken in this module is the same as the official OpenCV tutorial here:
 * https://docs.opencv.org/2.4/modules/contrib/doc/facerec/tutorial/facerec_video_recognition.html
 * Composed for F21IRO by @ Hamish MacKinnon, him2
 */

 #include <stdio.h>
 #include <yarp/os/Network.h>
 #include <yarp/os/BufferedPort.h>
 #include <yarp/sig/Image.h>
 #include <yarp/sig/Vector.h>
 #include <yarp/os/Time.h>
 #include <yarp/os/Property.h>
 #include <yarp/os/BinPortable.h>
 #include <string>
 #include <memory>
 #include <exception>

#include <opencv2/opencv.hpp>

 #include "imageFormatConverter.hpp"
 #include "faceHighlighting.hpp"

    using namespace yarp::sig;
    using namespace yarp::os;

    // Data for initialising the face boxing algorithm
    const std::string haar_cascade_data_filename = "/home/user/software/git/opencv/data/haarcascades/haarcascade_frontalface_default.xml"; //"haarcascade_frontalface_default.xml";  //"/home/user/software/git/opencv/data/haarcascades/haarcascade_frontalface_default.xml";


    int main(int argc, char *argv[])
    {


        // Network construction here allows for the use of ports
        Network yarp;

        // initialise the face boxing algorithm
        const std::shared_ptr<cv::CascadeClassifier> haarCascade = std::make_shared<cv::CascadeClassifier>();
        haarCascade->load(haar_cascade_data_filename);
        if(haarCascade-> empty()) {
            throw std::runtime_error("haarCascade loading failed.");
        }

        BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
        BufferedPort<ImageOf<PixelRgb> > outPort;
        BufferedPort<BinPortable<std::vector<cv::Rect_<int>>>> facePort;  // is a face port a mouth? Either way this is where we spit out the face squares.

        imagePort.open("/faceDetection/in");  // give the port a name
        outPort.open("/faceDetection/out");

        facePort.open("/faceDetection/faceVector/out");
        
        while (1) { // repeat forever
            ImageOf<PixelRgb> *image = imagePort.read();  // read an image
            ImageOf<PixelRgb> &outImage = outPort.prepare(); //get an output image
            std::vector<cv::Rect_<int>>& outVector = facePort.prepare().content(); // get an output vector of rectangles

            if (image!=nullptr) { // check we actually got something

                // convert to OpenCV format
                cv::Mat cvImage = coursework::toCvMat(*image);

                // actual work
                auto faceBoxes= coursework::recogniseAndBoxFaces(haarCascade, cvImage);

                // return to yarp format
                outImage = coursework::fromCvMat(faceBoxes.imageWithBoxes);
                outVector = faceBoxes.faceboxLocations;
                outPort.write();
                facePort.write();
            }
       }
   return 0;
   }



