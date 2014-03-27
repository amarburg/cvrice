#include <rice/Object.hpp>

#include <opencv2/core.hpp>

#ifndef __CVRICE_CVFFI_COMPAT_H__
#define __CVRICE_CVFFI_COMPAT_H__


cv::Mat cvmat_to_mat( Rice::Object obj );
Rice::Object mat_to_cvmat( cv::Mat &mat );


#endif
