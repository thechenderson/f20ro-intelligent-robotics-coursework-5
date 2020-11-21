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

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <yarp/sig/Image.h>
#include <yarp/sig/ImageDraw.h>
#include <yarp/sig/ImageFile.h>

#include "imageFormatConverter.hpp"

namespace coursework {

::cv::Mat toCvMat(yarp::sig::ImageOf<yarp::sig::PixelRgb>& yarpImage)
{
    ::cv::Mat outMat (yarpImage.height(), yarpImage.width(), CV_8UC3,
                      yarpImage.getRawImage(), yarpImage.getRowSize()); // RVO
    ::cv::cvtColor(outMat, outMat, CV_BGR2RGB);

    return outMat;
}

// Reimplementing this with the mono colour type was more effort than installing
// the update with the proper template.
yarp::sig::ImageOf<yarp::sig::PixelRgb> fromCvMat(::cv::Mat& cvImage)
{
    constexpr size_t align_8_bytes = 8;
    constexpr size_t align_4_bytes = 4;

    yarp::sig::ImageOf<yarp::sig::PixelRgb> outImg;
    // Checking cv::Mat::type() compatibility with the T PixelType
    assert(CV_8UC3 == cvImage.type());
    ::cv::cvtColor(cvImage, cvImage, CV_BGR2RGB);

    // Check the cv::Mat alignment
    if (cvImage.step % align_8_bytes == 0) {
        outImg.setQuantum(align_8_bytes);
    }
    else if (cvImage.step % align_4_bytes == 0) {
        outImg.setQuantum(align_4_bytes);
    }
    outImg.setExternal(cvImage.data, cvImage.cols, cvImage.rows);
    return outImg;
}

}
