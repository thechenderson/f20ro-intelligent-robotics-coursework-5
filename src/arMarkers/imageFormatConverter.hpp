/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

/*
 * Adapted for F21IRO Coursework by Hamish MacKinnon, him2
 */

// Forward declare so we don't include the entirity of OpenCV
namespace cv {
    class Mat;
}

namespace coursework {


::cv::Mat toCvMat(yarp::sig::ImageOf<yarp::sig::PixelRgb>& yarpImage);
yarp::sig::ImageOf<yarp::sig::PixelRgb> fromCvMat(::cv::Mat& cvImage);
yarp::sig::ImageOf<yarp::sig::PixelMono> monoFromCvMat(::cv::Mat& cvImage);


} // namespace coursework
