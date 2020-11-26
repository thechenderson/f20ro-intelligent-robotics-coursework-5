#include <memory>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "faceHighlighting.hpp"

using namespace cv;

namespace coursework {

    std::vector<cv::Rect_<int>> recogniseAndBoxFaces(const std::shared_ptr<cv::CascadeClassifier>& haar_cascade, const cv::Mat& inputImage, cv::Mat& outputimage) {
        // Clone the current frame:
        cv::Mat original = inputImage.clone();
        // Convert the current frame to grayscale:
        cv::Mat gray;
        cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
        // Find the faces in the frame, initialised as an empty vector:
        std::vector<cv::Rect_<int>> faces = {};
        haar_cascade->detectMultiScale(gray, faces);
        for(auto& face : faces) {
           // Draw a green rectangle around each detected face on the original colour image:
           cv::rectangle(original, face, CV_RGB(0, 255,0), 1);
        }
        outputimage = original;
        return faces;

}

} // end namespace coursework
