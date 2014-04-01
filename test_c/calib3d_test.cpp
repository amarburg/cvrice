#include "gtest/gtest.h"
#include "opencv2/core.hpp"
using namespace cv;

#include "opencv_rice/calib3d/calib3d.h"
using namespace CVRice;

TEST( findHomography, AllPoints )
{
  const int rows = 10;
  Mat m1( rows, 2, CV_64F ), m2( rows, 2, CV_64F );

  for( int i = 0; i < rows; ++i ) {
    m1.at<double>(i,0) = sin(i);
    m1.at<double>(i,1) = cos(i);
    m2.at<double>(i,0) = sin(i);
    m2.at<double>(i,1) = cos(i)+1;
  }

  Mat h = CVRice::findHomography( m1, m2, ALL_POINTS );
  ASSERT_EQ( 3, h.rows );
  ASSERT_EQ( 3, h.rows );

  Mat h_ransac = CVRice::findHomography( m1, m2, CVRice::RANSAC );
  ASSERT_EQ( 3, h_ransac.rows );
  ASSERT_EQ( 3, h_ransac.rows );

  Mat h_lmeds = CVRice::findHomography( m1, m2, CVRice::LMEDS );
  ASSERT_EQ( 3, h_lmeds.rows );
  ASSERT_EQ( 3, h_lmeds.rows );


//  ASSERT_EQ( CV_64F, err.type() );
//  const double exp = 17.0;
//  for( int j = 0; j < rows; ++j ) {
//    ASSERT_DOUBLE_EQ( exp, err.at<double>(j,0) );
//  }
}

