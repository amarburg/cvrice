
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
using namespace Rice;

#include "core/core.h"
#include "highgui/highgui.h"
#include "calib3d/calib3d.h"
#include "nonfree/nonfree.h"

/* The magic entry point function for the shared library. */
extern "C"
void Init_libopencv_rice( void ) {

  Module rb_mCVRice = define_module( "CVRice" );

  init_core( rb_mCVRice );
  init_highgui( rb_mCVRice );
  init_nonfree( rb_mCVRice );
  CVRice::init_calib3d( rb_mCVRice );
}
