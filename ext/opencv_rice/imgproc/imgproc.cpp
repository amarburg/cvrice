
#include <iostream>
#include <vector>
using std::vector;

#include <rice/Module.hpp>
using namespace Rice;

#include <opencv2/imgproc.hpp>
using namespace cv;

#include "core/to_from_ruby.h"
#include "core/vector.h"


Mat cvrice_cvtcolor( const Mat &src, int code )
{
Mat out;
cv::cvtColor( src, out, code );
return out;
}

// TODO.  Here's the inability to handle InputArray cropping up again.  Must fix this...

//  Also, skipped the borderType argument for now..
void cvrice_sobel( const Mat &src, Mat &dst, int ddepth, int dx, int dy, int ksize, double scale, double delta )
{
  Sobel( src, dst, ddepth, dx, dy, ksize, scale, delta );
}

//void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false )
Mat cvrice_canny( const Mat &src, double threshold1, double threshold2, int apertureSize, bool L2gradient )
{
  Mat out( src.size(), src.type() );
  Canny( src, out, threshold1, threshold2, apertureSize, L2gradient );
  return out;
}

//C++: void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0 )
vector<Vec2f> cvrice_houghlines( const Mat &src, double rho, double theta, int threshold, double srn, double stn )
{
  vector<Vec2f> lines;
  HoughLines( src, lines, rho, theta, threshold, srn, srn );
  return lines;
}

vector<Vec4i> cvrice_houghlines_p( const Mat &src, double rho, double theta, int threshold, double minLineLength, double maxLineGap )
{
  vector<Vec4i> lines;
  HoughLinesP( src, lines, rho, theta, threshold, minLineLength, maxLineGap );
  return lines;
}

template <typename _Vec>
Mat cvrice_undistort( const Mat &in, const Mat camera, const _Vec distCoeffs )
{
  Mat out;
  cv::undistort( in, out, camera, distCoeffs );
  return out;
}

Mat cvrice_warp_perspective( const Mat in, const Mat m, const Size dsize, int flags, int borderMode, const Scalar borderValue )
{
  Mat out( dsize, in.type() );
  warpPerspective( in, out, m, dsize, flags, borderMode, borderValue );
  return out;
}

Mat cvrice_threshold( const Mat &in, double thresh, double maxval, int type )
{
  Mat out;
  threshold( in, out, thresh, maxval, type );
  return out;
}

template <typename _Vec>
Mat cvrice_undistort_newcam( const Mat &in, const Mat camera, const _Vec distCoeffs, const Mat &newCamera )
{
  Mat out;
  cv::undistort( in, out, camera, distCoeffs, newCamera );
  return out;
}


void init_imgproc( Module &rb_mCVRice )
{

  rb_mCVRice.define_module_function( "sobel", &cvrice_sobel, (Arg("src"), Arg("dst"), Arg("ddepth"),
        Arg("dx"), Arg("dy"), Arg("ksize")=3, Arg("scale")=1.0, Arg("delta") =0 ) )
    .define_module_function("canny", &cvrice_canny, 
        (Arg("input"), Arg("threshold1"), Arg("threshold2"), Arg("apertureSize") = 3, Arg("L2gradient") = false ))
    .define_module_function("houghlines", &cvrice_houghlines,
        (Arg("input"), Arg("rho"), Arg("theta"), Arg("threshold"), Arg("srn") = 0, Arg("stn")=0))
    .define_module_function("houghlines_p", &cvrice_houghlines_p,
        (Arg("input"), Arg("rho"), Arg("theta"), Arg("threshold"), Arg("minLineLength") = 0, Arg("maxLineGap") = 0))
    .define_module_function("threshold", &cvrice_threshold )
    .define_module_function("cvtcolor", &cvrice_cvtcolor )
    .define_module_function("undistort4d", &cvrice_undistort<Vec4d> )
    .define_module_function("undistort4d_newcam", &cvrice_undistort_newcam<Vec4d> )
    .define_module_function("warp_perspective", &cvrice_warp_perspective,
        (Arg("input"), Arg("m"), Arg("dsize"), Arg("flags") = (int)INTER_LINEAR, 
         Arg("borderMode") = (int)BORDER_CONSTANT, Arg("borderValue") = Scalar()));
}

