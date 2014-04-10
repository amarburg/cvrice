
#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>

#include <opencv2/core.hpp>

#ifndef __OPENCV_RICE_MAT_CONVERSIONS_H__
#define __OPENCV_RICE_MAT_CONVERSIONS_H__


// Done this way so the template definition is fully accessible,
// without having the actual guts on display in the header.
cv::Mat mat_from_ruby( Rice::Object obj );
template<> inline cv::Mat from_ruby<cv::Mat>( Rice::Object obj )
{ return mat_from_ruby( obj ); }

//TODO.  Can this be templatized?
cv::Matx33d matx33d_from_ruby( Rice::Object obj );
template<> inline cv::Matx33d from_ruby< cv::Matx33d >( Rice::Object obj )
{ return matx33d_from_ruby( obj ); }

cv::Matx33f matx33f_from_ruby( Rice::Object obj );
template<> inline cv::Matx33f from_ruby< cv::Matx33f >( Rice::Object obj )
{ return matx33f_from_ruby( obj ); }

#endif
