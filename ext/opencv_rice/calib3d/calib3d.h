
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
  //
  cv::Mat calculateHomography( const cv::Mat src, const cv::Mat dst, cv::Mat &mask, int method = ALL_POINTS, double reprojThreshold = 3 );


  class Pose {
    public:
      Pose( const Mat rvec, const Mat tvec )
        : _rvec( rvec ), _tvec( tvec ) {;}

      Mat t( void ) { return _tvec; }

      Mat rvec( void ) { return _rvec; }

      Mat rotation_matrix( void ) { 
        Mat rot;
        cv::Rodrigues( _rvec, rot );
        return rot;
      }

      Mat total( void ) {
        cv::Mat rot = rotation_matrix();
        cv::Mat total = cv::Mat::eye(4,4, CV_64F );

        for( int r = 0; r < 3; ++r ) {
          for( int c = 0; c < 3; ++c )  {
            total.at<double>(r,c) = rot.at<double>(r,c);
            total.at<double>(3,c) = 0.0;
          }

          total.at<double>(r,3) = t().at<double>(r,0);
        }

        return total;
      }

      Pose invert( void ) {
        // TODO.  Could be done without conversion to rotation matrix and
        // back again?
        Mat rinv;
        Rodrigues( rotation_matrix().inv(), rinv );
        return Pose( rinv, rotation_matrix() * _tvec * -1 );
      }

    protected:
      Mat _rvec, _tvec;
  };

  Pose calculatePnP( const cv::Mat objPts, const cv::Mat imgPts, const cv::Mat cameraMat, const cv::Mat distCoeff, int flags );
  Pose calculatePnPHint( const cv::Mat objPts, const cv::Mat imgPts, const cv::Mat cameraMat, const cv::Mat distCoeff,
      const cv::Mat rvec_hint, const cv::Mat tvec_hint, int flags );


  void init_calib3d( Rice::Module & );
}

#endif
