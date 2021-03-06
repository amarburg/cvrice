#include <vector>
#include <rice/Object.hpp>
#include <rice/Array.hpp>

#include <rice/to_from_ruby.hpp>

#ifndef __VECTOR_H__
#define __VECTOR_H__

template<> inline
Rice::Object to_ruby< std::vector<cv::Vec4i> >( std::vector<cv::Vec4i> const &vec )
{
  return Rice::Array(vec.begin(), vec.end());
}

template<> inline
Rice::Object to_ruby< std::vector<cv::Vec2f> >( std::vector<cv::Vec2f> const &vec )
{
  return Rice::Array(vec.begin(), vec.end());
}

template <typename _Vec> inline
Object vec_to_arr( const _Vec &vec )
{
  Array arr;
  for( int i = 0; i < _Vec::channels; ++i ) arr.push( vec[i] );
  return arr;
}


#endif
