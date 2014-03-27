
#include <iostream>
#include <vector>
using std::vector;

#include <rice/Module.hpp>
using namespace Rice;

#include <opencv2/highgui.hpp>
using namespace cv;

#include "core/to_from_ruby.h"



//// de-obfuscation wrapper that makes the filename args non-reference
//
//Mat imread_cppstring( const std::string &fname, int flags = -1 )
//{ return cv::imread( fname, flags ); }
//
// Strip off the params vector for now
// const vector<int>& params=vector<int>() )
bool imwrite_noparams( const cv::String &fname, InputArray img )
{ return cv::imwrite( fname, img ); }


void bar_test( const std::string &str )
{
  std::cout << str << std::endl;
}

void foo_test( const cv::String &str )
{
  std::cout << str << std::endl;
}

void baz_test( const Rice::String str )
{
  std::cout << str << std::endl;
}

void init_highgui( Module &rb_mCVRice )
{
  rb_mCVRice.define_module_function( "load_image", &imread, (Arg("filename"), Arg("flags") = 1 ) );
  rb_mCVRice.define_module_function( "save_image", &imwrite_noparams, (Arg("filename"), Arg("img")) );

  rb_mCVRice.define_method( "bar", &bar_test );
  rb_mCVRice.define_method( "foo", &foo_test );
  rb_mCVRice.define_method( "baz", &baz_test );
}

