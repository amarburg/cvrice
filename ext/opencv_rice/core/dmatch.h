
#include <vector>

#include <opencv2/core.hpp>

#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>
#include <rice/Array.hpp>

#ifndef __OPENCV_RICE_DMATCH_H__
#define __OPENCV_RICE_DMATCH_H__

template<>
  inline
Rice::Object to_ruby< std::vector<cv::DMatch> >( std::vector<cv::DMatch> const &matches )
{
  Rice::Array out;
  for( std::vector<cv::DMatch>::const_iterator itr = matches.begin(); itr != matches.end(); itr++ )
  {
    out.push( to_ruby( *itr ) );
  }

  return out;
}


//template<>
//  inline
//Rice::Object to_ruby< std::vector<cv::DMatch> *>( std::vector<cv::DMatch> *matches )
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
