
#include <rice/Module.hpp>
using namespace Rice;

#include <opencv2/core.hpp>

#include "to_from_ruby.h"

void init_mat( Module & );
void init_keypoint( Module & );
void init_dmatch( Module & );

void init_core( Module &rb_mCVRice )
{
  init_mat( rb_mCVRice );
  init_keypoint( rb_mCVRice );
  init_dmatch( rb_mCVRice );

  define_class_under<cv::String>( rb_mCVRice, "String" );
}



