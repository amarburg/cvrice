
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
      Pose( const cv::Mat rvec, const cv::Mat tvec );

      cv::Mat t( void ) { return _tvec; }

      cv::Mat rvec( void ) { return _rvec; }

      cv::Mat rotation_matrix( void ) { 
        cv::Mat rot;
        cv::Rodrigues( _rvec, rot );
        return rot;
      }

      template <typename _Tp>
        cv::Mat total( void ) {
          cv::Mat rot = rotation_matrix();
          cv::Matx< _Tp, 4, 4 > total( rot.at< float >(0,0), rot.at<float>(0,1), rot.at<float>(0,2), _tvec.at<float>(0,0),
               rot.at< float >(1,0), rot.at<float>(1,1), rot.at<float>(1,2), _tvec.at<float>(1,0),
               rot.at< float >(2,0), rot.at<float>(2,1), rot.at<float>(2,2), _tvec.at<float>(2,0),
               0.0, 0.0, 0.0, 1.0 );

          return cv::Mat(total);
        }

      cv::Mat total_d( void ) { return total<double>(); }


      Pose invert( void ) {
        // TODO.  Could be done without conversion to rotation matrix and back again?
        cv::Mat rinv;
        cv::Rodrigues( rotation_matrix().inv(), rinv );
        return Pose( rinv, rotation_matrix() * _tvec * -1 );
      }

    protected:
      cv::Mat _rvec, _tvec;
  };

  Pose calculatePnP( const cv::Mat objPts, const cv::Mat imgPts, const cv::Mat cameraMat, const cv::Mat distCoeff, int flags );
  Pose calculatePnPHint( const cv::Mat objPts, const cv::Mat imgPts, const cv::Mat cameraMat, const cv::Mat distCoeff,
      const cv::Mat rvec_hint, const cv::Mat tvec_hint, int flags );


  void init_calib3d( Rice::Module & );
}

#endif
