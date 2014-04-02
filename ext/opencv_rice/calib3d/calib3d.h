
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

#include <rice/Module.hpp>

#ifndef __OPENCV_RICE_CALIB3D_H__
#define __OPENCV_RICE_CALIB3D_H__

namespace CVRice {

  enum EstMethods { ALL_POINTS = 0,
                    LMEDS = cv::LMEDS,
                    RANSAC = cv::RANSAC };

  //TODO.  I dislike this indirection.  Figure out how to live with
  // InputArray
  cv::Mat findHomography( const cv::Mat src, const cv::Mat dst, 
      int method = ALL_POINTS, double reprojThreshold = 3 );

   void init_calib3d( Rice::Module & );
}

#endif
