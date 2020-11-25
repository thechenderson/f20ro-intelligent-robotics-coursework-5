// Author @him2
namespace coursework {
    // Our compiler version doesn't support automatic structured bindings, so make a struct that we can bind to explicitly.
    struct FaceBoxingResults {
        cv::Mat imageWithBoxes;
        std::vector<cv::Rect_<int>> faceboxLocations;
    };
    FaceBoxingResults recogniseAndBoxFaces(const std::shared_ptr<cv::CascadeClassifier>& haar_cascade, const cv::Mat& inputImage);
}
