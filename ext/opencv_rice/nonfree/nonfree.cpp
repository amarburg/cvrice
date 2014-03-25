
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/nonfree.hpp>
using namespace cv;

#include "nonfree.h"

void init_nonfree( Module &rb_mCVRice )
{
  init_sift( rb_mCVRice );
}
