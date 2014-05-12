
#include <iostream>
#include <vector>

#include <opencv2/core.hpp>

#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>
#include <rice/Array.hpp>

#ifndef __OPENCV_RICE_DMATCH_H__
#define __OPENCV_RICE_DMATCH_H__

namespace CVRice {
  typedef std::vector<cv::DMatch> DMatchVector;

  void init_dmatch( Rice::Module &rb_mParent );
};


template<>
inline
Rice::Object to_ruby< CVRice::DMatchVector >( CVRice::DMatchVector const &matches )
{
  std::cout << "In to_ruby" << std::endl;
  Rice::Array out;
  for( CVRice::DMatchVector::const_iterator itr = matches.begin(); itr != matches.end(); itr++ )
  {
    out.push( to_ruby( *itr ) );
  }

  return out;
}

template<>
inline
CVRice::DMatchVector from_ruby< CVRice::DMatchVector >( Rice::Object obj )
{
  std::cout << "In from_ruby" << std::endl;
  Rice::Array vec( obj );
  CVRice::DMatchVector out;
  for( Rice::Array::iterator itr = vec.begin(); itr != vec.end(); ++itr ) {
    out.push_back( from_ruby< cv::DMatch >( *itr ) );
  }

  return out;
}

// TODO.  This idiom again.  Leaking memory?
template<>
inline
CVRice::DMatchVector *from_ruby< CVRice::DMatchVector *>( Rice::Object obj )
{
  Rice::Array vec( obj );
  CVRice::DMatchVector *out = new CVRice::DMatchVector;
  for( Rice::Array::iterator itr = vec.begin(); itr != vec.end(); ++itr ) {
    out->push_back( from_ruby< cv::DMatch >( *itr ) );
  }

  return out;
}


//template<>
//  inline
//Rice::Object to_ruby< std::vector<cv::DMatch> *>( std::vector<cv::DMatch> const *matches )
//{
//  Rice::Array out;
//  for( std::vector<cv::DMatch>::const_iterator itr = matches->begin(); itr != matches->end(); itr++ )
//  {
//    out.push( to_ruby( *itr ) );
//  }
//
//  return out;
//}


#endif
