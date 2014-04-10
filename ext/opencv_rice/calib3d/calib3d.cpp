
#include <rice/Module.hpp>
#include <rice/Enum.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
using namespace cv;

#include "calib3d.h"
#include "reproj.h"
#include "../core/core.h"


namespace CVRice {

  //TODO.  I dislike this indirection.  Figure out how to live InputArray
  Mat findHomography( const Mat src, const Mat dst, 
      int method, double reprojThreshold )
  { return cv::findHomography( src, dst, method, reprojThreshold ); }

  void init_calib3d( Module &parent )
  {
    init_reproj( parent );

    define_enum<EstMethods>("EstimationMethods")
      .define_value("all_pts", ALL_POINTS )
      .define_value("lmeds", LMEDS )
      .define_value("ransac", RANSAC );

    //typedef Mat (*find_hom)(InputArray, InputArray, int, double, OutputArray ); 
    //parent.define_singleton_method( "findHomography", find_hom(&cv::findHomography),
    //    (Arg("src"), Arg("dst"), Arg("method") = 0, Arg("threshold") = 3 ) );

    parent.define_singleton_method( "findHomography", &CVRice::findHomography,
        (Arg("src"), Arg("dst"), Arg("method") = 0, Arg("threshold") = 3 ) );
  } 

}

