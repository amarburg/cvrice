#include "gtest/gtest.h"
#include "opencv2/core.hpp"
using namespace cv;

#include "opencv_rice/calib3d/reproj.h"
using namespace CVRice;

TEST( cvHMaxReprojError, TrivialDouble )
{
  const int rows = 10;
  Mat m1( rows, 2, CV_64F ), m2( rows, 2, CV_64F ), h = Mat::eye(3,3,CV_64F );

  for( int i = 0; i < rows; ++i ) {
    m1.at<double>(i,0) = i+4;
    m1.at<double>(i,1) = i;
    m2.at<double>(i,0) = i;
    m2.at<double>(i,1) = i+1;
  }

  Mat err = cvHMaxReprojError( m1, m2, h );

  ASSERT_EQ( rows, err.rows );
  ASSERT_EQ( 1, err.cols );
  ASSERT_EQ( CV_64F, err.type() );
  const double exp = 17.0;
  for( int j = 0; j < rows; ++j ) {
    ASSERT_DOUBLE_EQ( exp, err.at<double>(j,0) );
  }
}

TEST( cvHMaxReprojError, TrivialFloat )
{
  const int rows = 10;
  Mat m1( rows, 2, CV_32F ), m2( rows, 2, CV_32F ), h = Mat::eye(3,3,CV_32F );

  for( int i = 0; i < rows; ++i ) {
    m1.at<float>(i,0) = i-4;
    m1.at<float>(i,1) = i;
    m2.at<float>(i,0) = i;
    m2.at<float>(i,1) = i+1;
  }

  Mat err = cvHMaxReprojError( m1, m2, h );

  ASSERT_EQ( rows, err.rows );
  ASSERT_EQ( 1, err.cols );
  ASSERT_EQ( CV_64F, err.type() );
  const double exp = 17.0;
  for( int j = 0; j < rows; ++j ) {
    ASSERT_DOUBLE_EQ( exp, err.at<double>(j,0) );
  }
}
