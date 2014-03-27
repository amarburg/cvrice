
#include <vector>
#include <rice/Object.hpp>
#include <rice/Array.hpp>
#include <opencv2/features2d.hpp>

#include <rice/to_from_ruby.hpp>

#ifndef __CVRICE_CORE_KEYPOINT_H__
#define __CVRICE_CORE_KEYPOINT_H__

typedef std::vector<cv::KeyPoint> KeyPointVector;

template<>
inline
std::vector<cv::KeyPoint> from_ruby< std::vector<cv::KeyPoint> >( Rice::Object o )
{
  Rice::Array arr( o );
  std::vector<cv::KeyPoint> vec;

  for( Rice::Array::iterator itr = arr.begin(); itr != arr.end(); ++itr ) {
    vec.push_back( from_ruby<cv::KeyPoint>( *itr ) );
  }
  return vec;
}

template<>
inline
Rice::Object to_ruby< std::vector<cv::KeyPoint> >( std::vector<cv::KeyPoint> const &vec )
{
  return Rice::Array(vec.begin(), vec.end());
}


#endif


