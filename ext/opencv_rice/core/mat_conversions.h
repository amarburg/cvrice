
#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>

#include <opencv2/core.hpp>

#include "mat_conversions.ipp"

#ifndef __OPENCV_RICE_MAT_CONVERSIONS_H__
#define __OPENCV_RICE_MAT_CONVERSIONS_H__


// Done this way so the template definition is fully accessible,
// without having the actual guts on display in the header.
cv::Mat mat_from_ruby( Rice::Object obj );

template<> inline cv::Mat from_ruby<cv::Mat>( Rice::Object obj )
{ return mat_from_ruby( obj ); }

template<> inline cv::_InputArray from_ruby<cv::_InputArray>( Rice::Object obj )
{ return mat_from_ruby( obj ); }

//TODO.  Can this be templatized?  Can you make a template of a template?
template<> inline cv::Matx22d from_ruby< cv::Matx22d >( Rice::Object obj )
{ return matx_from_ruby< cv::Matx22d >( obj ); }

template<> inline cv::Matx22f from_ruby< cv::Matx22f >( Rice::Object obj )
{ return matx_from_ruby< cv::Matx22f >( obj ); }

template<> inline cv::Matx33d from_ruby< cv::Matx33d >( Rice::Object obj )
{ return matx_from_ruby< cv::Matx33d >( obj ); }

template<> inline cv::Matx33f from_ruby< cv::Matx33f >( Rice::Object obj )
{ return matx_from_ruby< cv::Matx33f >( obj ); }


#endif
