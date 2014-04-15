
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

template<> inline cv::_InputArray from_ruby<cv::_InputArray>( Rice::Object obj )
{ return mat_from_ruby( obj ); }
//template<> inline cv::_InputArray *from_ruby<cv::_InputArray *>( Rice::Object obj )
//{ return new cv::_InputArray(mat_from_ruby( obj )); }


//TODO.  Can this be templatized?
cv::Matx22d matx22d_from_ruby( Rice::Object obj );
template<> inline cv::Matx22d from_ruby< cv::Matx22d >( Rice::Object obj )
{ return matx22d_from_ruby( obj ); }

cv::Matx22f matx22f_from_ruby( Rice::Object obj );
template<> inline cv::Matx22f from_ruby< cv::Matx22f >( Rice::Object obj )
{ return matx22f_from_ruby( obj ); }

cv::Matx33d matx33d_from_ruby( Rice::Object obj );
template<> inline cv::Matx33d from_ruby< cv::Matx33d >( Rice::Object obj )
{ return matx33d_from_ruby( obj ); }

cv::Matx33f matx33f_from_ruby( Rice::Object obj );
template<> inline cv::Matx33f from_ruby< cv::Matx33f >( Rice::Object obj )
{ return matx33f_from_ruby( obj ); }



#endif
