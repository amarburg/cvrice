
#include <rice/Module.hpp>
#include <rice/Enum.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
using namespace cv;

#include "calib3d.h"
#include "reproj.h"
#include "../core/core.h"


namespace CVRice {

  Pose::Pose( const Mat rvec, const Mat tvec )
    : _rvec(), _tvec() 
  {
    cv::Mat rin( rvec ), tin( tvec );

    if( (rin.cols * rin.rows) == 9 ) Rodrigues( rvec, rin );

    CV_Assert( (rin.cols == 1) && (rin.rows == 3));
    CV_Assert( (tin.cols == 1) && (tin.rows == 3)); 

    rin.convertTo( _rvec, CV_32F );
    tin.convertTo( _tvec, CV_32F );
  }

  Mat Pose::Pose::total( void ) {
    Mat rot = rotation_matrix();
    Mat total = Mat::eye(4,4, CV_32F );

    for( int r = 0; r < 3; ++r ) {
      for( int c = 0; c < 3; ++c )  {
        total.at<float>(r,c) = rot.at<float>(r,c);
        total.at<float>(3,c) = 0.0;
      }

      total.at<float>(r,3) = t().at<float>(r,0);
    }

    return total;
  }




  // TODO.  I dislike this indirection.  Figure out how to live with InputArray
  Mat calculateHomography( const Mat src, const Mat dst, Mat &mask, int method, double reprojThreshold )
  { 
    return cv::findHomography( src, dst, method, reprojThreshold, mask );
  }

  Pose calculatePnP( const Mat objpts, const Mat imgpts, const Mat cameramat, const Mat distcoeffs, int flags )
  {
    Mat rvec, tvec;

    bool result = solvePnP( objpts, imgpts, cameramat, distcoeffs, rvec, tvec, false, flags );

    return Pose( rvec, tvec );
  }


  Pose calculatePnPHint( const Mat objpts, const Mat imgpts, const Mat cameramat, const Mat distcoeffs, 
      const Mat rvec_hint, const Mat tvec_hint, int flags )
  {
    Mat rvec = rvec_hint, tvec = tvec_hint;

    bool result = solvePnP( objpts, imgpts, cameramat, distcoeffs, rvec, tvec, true, flags );

    return Pose( rvec, tvec );
  }

  Mat rodrigues( const Mat in )
  {
    Mat out;
    Rodrigues( in, out );
    return out;
  }

  void init_calib3d( Module &parent )
  {
    init_reproj( parent );

    define_enum<EstMethods>("EstimationMethods")
      .define_value("all_pts", ALL_POINTS )
      .define_value("lmeds", LMEDS )
      .define_value("ransac", RANSAC );

    //typedef Mat (*find_hom)(InputArray, InputArray, int, double, OutputArray ); 
    //parent.define_singleton_method( "findHomography", find_hom(&cv::findHomography),
    //    (Arg("src"), Arg("dst"), Arg("method") = 0, Arg("threshold") = 3, Arg("mask") = noArray() ) );

    define_class_under< Pose >( parent, "Pose" )
      .define_constructor( Constructor< Pose, const Mat, const Mat >() )
      .define_method( "rotation_matrix", &Pose::rotation_matrix )
      .define_method( "t", &Pose::t )
      .define_method( "tvec", &Pose::t )
      .define_method( "rvec", &Pose::rvec )
      .define_method( "total", &Pose::total )
      .define_method( "inv", &Pose::invert )
      .define_method( "invert", &Pose::invert );

    // Can't figure out how to handle OutputArrays .. as default arguments.  Handle it in Ruby for now
    parent.define_singleton_method( "calculateHomography", &CVRice::calculateHomography,
        (Arg("src"), Arg("dst"), Arg("mask"), Arg("method") = 0, Arg("threshold") = 3) )
      .define_singleton_method( "calculatePnP", &CVRice::calculatePnP,
          (Arg("objPts"), Arg("imgPts"), Arg("cameraMat"), Arg("distCoeffs"), Arg("flags") = (int)cv::ITERATIVE) )
      .define_singleton_method( "calculatePnPHint", &CVRice::calculatePnPHint,
          (Arg("objPts"), Arg("imgPts"), Arg("cameraMat"), Arg("distCoeffs"), 
           Arg("rvec_hint"), Arg("tvec_hint"), Arg("flags") = (int)cv::ITERATIVE) )
      .define_singleton_method( "rodrigues", &rodrigues );
  } 

}

