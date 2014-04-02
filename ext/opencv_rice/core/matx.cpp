
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <iostream>

#include "mat_conversions.h"

void takes_a_matx33d( Matx33d mat ) { ; }


//=========================================================

void init_matx( Module &rb_mCVRice )
{
  define_class_under< Matx33d >( rb_mCVRice, "Matx33d" )
    .define_constructor( Constructor<Matx33d>() )
     .define_singleton_method( "from_ruby", &from_ruby<cv::Matx33d> );

  define_implicit_cast<Matx33d, Mat>();

  rb_mCVRice.define_module_function( "takes_a_matx33d", &takes_a_matx33d );
}

