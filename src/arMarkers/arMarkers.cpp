// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
 
 #include <stdio.h>
 #include <yarp/os/Network.h>
 #include <yarp/os/BufferedPort.h>
 #include <yarp/sig/Image.h>
 #include <yarp/sig/Vector.h>
 #include <yarp/os/Time.h>
 #include <yarp/os/Property.h> 
 #include <string>
    
 #include <stdio.h>
 #include <yarp/os/Network.h>
 #include <yarp/os/BufferedPort.h>
 #include <yarp/sig/Image.h>
 #include <yarp/sig/Vector.h>
 #include <yarp/os/Time.h>
 #include <yarp/os/Property.h>
 #include <string>

 #include <opencv2/opencv.hpp>
 #include <opencv2/aruco.hpp>

#include "../applyLinearFilter/imageFormatConverter.hpp"



    using namespace yarp::sig;
    using namespace yarp::os;
    
    int main(int argc, char *argv[]) 
    {
        Network yarp;
    
        BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
        BufferedPort<ImageOf<PixelRgb> > outPort;

        imagePort.open("/imageProc/image/in");  // give the port a name
        outPort.open("/imageProc/image/out");
        
        //Create the dictionary of markers to compare against
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

        while (1) { // repeat forever
            ImageOf<PixelRgb> *image = imagePort.read();  // read an image
            ImageOf<PixelRgb> &outImage = outPort.prepare(); //get an output image

            if(image!=nullptr){

                //Convert yarp image to CV format
                cv::Mat cvImage = coursework::toCvMat(*image);

                //Code adapted from https://docs.opencv.org/master/d5/dae/tutorial_aruco_detection.html
                //Setup the marker detection function
                std::vector<int> markerIds;
                std::vector<std::vector<cv::Point2f>> markerCorners;

                cv::aruco::detectMarkers(cvImage, dictionary, markerCorners, markerIds);

               

                //Output the markers onto the image
                cv::Mat outputImage = cvImage.clone();
                cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);
                outImage = coursework::fromCvMat<PixelRgb>(outputImage);
                outPort.write();


            }
    
        }

   return 0;
}
   
