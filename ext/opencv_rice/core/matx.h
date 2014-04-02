
#include <opencv2/core.hpp>


#ifndef __OPENCV_RICE_MATX_H__
#define __OPENCV_RICE_MATX_H__


template <typename _T> inline cv::Mat matx_to_mat( const _T &m ) { return cv::Mat(m); }


#endif
