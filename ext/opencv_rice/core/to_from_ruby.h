
#include <opencv2/core.hpp>
#include <rice/to_from_ruby.hpp>
#include <rice/Object.hpp>
#include <rice/String.hpp>

#include <memory>
using std::auto_ptr;

#ifndef __CORE_TO_FROM_RUBY_H__
#define __CORE_TO_FROM_RUBY_H__

template<> 
  inline
cv::String from_ruby<cv::String>( Rice::Object x ) 
{ 
  return cv::String( Rice::String(x).str() );
}

// TODO:  Generating these temporary objects must 
// cause a memory leak, no?
template<> 
  inline
cv::String *from_ruby<cv::String *>( Rice::Object x ) 
{ 
  return new cv::String( Rice::String(x).str() );
}


#endif
