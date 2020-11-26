namespace coursework {
    std::vector<cv::Rect_<int>> recogniseAndBoxFaces(const std::shared_ptr<cv::CascadeClassifier>& haar_cascade, const cv::Mat& inputImage, cv::Mat& outputimage);
}
