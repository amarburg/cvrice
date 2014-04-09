
#include <iostream>
#include <vector>
using std::vector;

#include <rice/Module.hpp>
using namespace Rice;

#include <opencv2/imgproc.hpp>
using namespace cv;

#include "core/to_from_ruby.h"


// TODO.  Here's the inability to handle InputArray cropping up again.  Must fix this...
//  Also, skipped the borderType argument for now..
void cvrice_sobel( const Mat &src, Mat &dst, int ddepth, int dx, int dy, int ksize, double scale, double delta )
{
  Sobel( src, dst, ddepth, dx, dy, ksize, scale, delta );
}

void init_imgproc( Module &rb_mCVRice )
{

  rb_mCVRice.define_module_function( "sobel", &cvrice_sobel, (Arg("src"), Arg("dst"), Arg("ddepth"),
        Arg("dx"), Arg("dy"), Arg("ksize")=3, Arg("scale")=1.0, Arg("delta") =0 ) );
}

