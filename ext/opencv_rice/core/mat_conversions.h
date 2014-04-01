
#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>

#include <opencv2/core.hpp>

#ifndef __OPENCV_RICE_MAT_CONVERSIONS_H__
#define __OPENCV_RICE_MAT_CONVERSIONS_H__


template<> cv::Mat from_ruby<cv::Mat>( Rice::Object obj );
template<> cv::InputArray from_ruby< cv::InputArray >(Rice::Object obj);
template<> cv::Matx33d from_ruby< cv::Matx33d >( Rice::Object obj );

#endif
