
#include <rice/Module.hpp>
using namespace Rice;

#include <opencv2/core.hpp>

#include "to_from_ruby.h"
#include "dmatch.h"

using namespace CVRice;

void init_mat( Module & );
void init_matx( Module & );
void init_vector( Module & );
void init_keypoint( Module & );
void init_point( Module & );
void init_size( Module & );

// TODO: Broken windows.  Fix up the namespacing
namespace CVRice {
  void init_draw( Module & );
  void init_scalar( Module & );
}

void init_core( Module &rb_mCVRice )
{
  init_mat( rb_mCVRice );
  init_matx( rb_mCVRice );
  init_point( rb_mCVRice );
  init_keypoint( rb_mCVRice );
  init_vector( rb_mCVRice );
  init_dmatch( rb_mCVRice );
  init_size( rb_mCVRice );
  init_draw( rb_mCVRice );
  init_scalar( rb_mCVRice );

  define_class_under<cv::String>( rb_mCVRice, "String" );
}



