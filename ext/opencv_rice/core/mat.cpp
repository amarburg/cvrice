


#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;


int get_mat_rows( const Mat &m ) { return m.rows; }
int get_mat_cols( const Mat &m ) { return m.cols; }

void init_mat( Module &rb_mCVRice )
{
  define_class_under< Mat >( rb_mCVRice, "Mat" )
    .define_constructor( Constructor<Mat>() )
    .define_method( "rows", &get_mat_rows )
    .define_method( "cols", &get_mat_cols );

  define_class_under< _InputArray >( rb_mCVRice, "InputArray" );
  define_implicit_cast<Mat, _InputArray>();

  define_class_under< cv::String >( rb_mCVRice, "String" );
}

