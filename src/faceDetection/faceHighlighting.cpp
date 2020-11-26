/*
 * Face detection using a pretrained Haar Cascade.
 * The approach taken in this module is the same as the official OpenCV tutorial here:
 * https://docs.opencv.org/2.4/modules/contrib/doc/facerec/tutorial/facerec_video_recognition.html
 * Composed for F21IRO by @ Hamish MacKinnon, him2
 */

#include <memory>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "faceHighlighting.hpp"

using namespace cv;

namespace coursework {

    FaceBoxingResults recogniseAndBoxFaces(cv::CascadeClassifier* haar_cascade, const cv::Mat& inputImage) {
       // Clone the current frame:
       cv::Mat original = inputImage.clone();
       // Convert the current frame to grayscale:
       cv::Mat gray;
       cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
       // Find the faces in the frame:
       std::vector<cv::Rect_<int>> faces;
       haar_cascade->detectMultiScale(gray, faces);
       for(auto& face : faces) {
            // Draw a green rectangle around each detected face on the original colour image:
            cv::rectangle(original, face, CV_RGB(0, 255,0), 1);

        return FaceBoxingResults{original, faces};
    }

}

} // end namespace coursework
