
#include <rice/Module.hpp>
#include <opencv2/core.hpp>


#ifndef __OPENCV_RICE_REPROJ_H__
#define __OPENCV_RICE_REPROJ_H__

namespace CVRice {
  using cv::Mat;

  Mat cvFMaxReprojError( const Mat _m1, const Mat _m2, const Mat model );
  Mat cvHMaxReprojError( const Mat _m1, const Mat _m2, const Mat model );

  void init_reproj( Rice::Module & );
};

#endif
