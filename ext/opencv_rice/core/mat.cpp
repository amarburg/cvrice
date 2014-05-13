
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <iostream>
using std::endl;
using std::cout;

#include "mat_conversions.h"

// TODO:  These are madly non-type-safe.  
double mat_at_d( Mat const &m, int r, int c = 0) {
  switch(m.depth()) {
    case CV_8U:
      return 1.0 * m.at<unsigned char>(r,c);
    case CV_32F:
      return (double)m.at<float>(r,c);
    case CV_64F:
      return m.at<double>(r,c);
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_at_d" );
  }
}
float mat_at_f( Mat const &m, int r, int c = 0) {
  switch(m.depth()) {
    case CV_8U:
      return 1.0 * m.at<unsigned char>(r,c);
    case CV_32F:
      return m.at<float>(r,c);
    case CV_64F:
      return (float)m.at<double>(r,c);
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_at_f" );
  }
}

unsigned char mat_at_8u( Mat const &m, int r, int c = 0 ) {
  switch(m.depth()) {
    case CV_8U:
      return m.at<unsigned char>(r,c);
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_at_f" );
  }
}

void mat_set_d( Mat &m, int r, int c, double val ) {
  switch(m.depth()) {
    case CV_32F:
      m.at<float>(r,c) = val;
      break;
    case CV_64F:
      m.at<double>(r,c) = val;
      break;
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_set_d (%d)", m.depth() );
  }
}


int mat_get_rows( const Mat &m ) { return m.rows; }
int mat_get_cols( const Mat &m ) { return m.cols; }

void takes_a_mat( Mat mat ) { ; }
void takes_a_mat_ref( Mat const &mat ) { ; }

// A set of simply constructor functions 
Mat make_a_mat( Mat mat ) { return mat; }
Mat copy_constructor( Mat const &in ) { return Mat(in); }

void mat_svd( const Mat &m, Mat &w, Mat &u, Mat &vt, int flags = 0 )
{
  SVD::compute( m, w, u, vt, flags );
}

Mat mat_convert_to( const Mat &m, int rtype, double alpha, double beta )
{
  Mat out;
  m.convertTo( out, rtype, alpha, beta );
  return out;
}

Mat mat_merge( const Array mats )
{
  std::vector<Mat> matvec;
  for( Array::const_iterator itr = mats.begin(); itr != mats.end(); ++itr ) {
    matvec.push_back( from_ruby<Mat>(*itr) );
  }

  Mat out;
  cv::merge( matvec, out );
  return out;
}

Mat mat_transpose( const Mat &m ) { return m.t(); }

Mat mat_add_mat( const Mat &a, const Mat &b ) { return a+b; }
Mat mat_add_const( const Mat &a, const double b ) { return a+b; }
Mat mat_subtract_mat( const Mat &a, const Mat &b ) { return a-b; }
Mat mat_subtract_const( const Mat &a, const double b ) { return a-b; }
Mat mat_subtract_reverse_const( const Mat &a, const double b ) { return b-a; }
Mat mat_mult_mat( const Mat &a, const Mat &b ) { return a*b; }
Mat mat_mult_const( const Mat &a, const double b ) { return a*b; }

Mat mat_pinv( const Mat &m ) { return m.inv( DECOMP_SVD ); }
Mat mat_inv(  const Mat &m ) { return m.inv(); }
Size mat_size( const Mat &m ) { return m.size(); }

// TODO:  Done this way because Mat::eye returns a MatExpr ... can I integrate
// MatExpr into the library?
Mat mat_eye( int rows, int cols, int type )
{
  return Mat::eye( rows, cols, type ); 
}

Mat mat_zeros( int rows, int cols, int type )
{ 
  return Mat::zeros( rows, cols, type ); 
}

Object mat_to_a( Mat &m )
{
  Array arr;

  int num_rows = m.rows, num_cols = m.cols;

  switch(m.depth()) {
    case CV_32F:
      for( int r = 0; r < num_rows; ++r ) {
        Array row;
        float *flt = m.ptr<float>(r);
        for( int c = 0; c < num_cols; ++c ) {
          row.push( flt[c] );
        }
        arr.push( row );
      }
      break;
    case CV_64F:
      for( int r = 0; r < num_rows; ++r ) {
        Array row;
        double *dbl = m.ptr<double>(r);
        for( int c = 0; c < num_cols; ++c ) {
          row.push( dbl[c] );
        }
        arr.push( row );
      }
      break;
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_to_a" );
  }

  return arr;
}


//=========================================================

void init_mat( Module &rb_mCVRice )
{

  Data_Type<Mat> rb_cMat = define_class_under< Mat >( rb_mCVRice, "Mat" )
    .define_constructor( Constructor<Mat,int,int,int>(), (Arg("rows")=0, Arg("cols") = 0, Arg("type") = CV_64F) )
    .define_method( "rows", &mat_get_rows )
    .define_method( "cols", &mat_get_cols )
    .define_method( "type", &Mat::type )
    .define_method( "depth", &Mat::depth )
    .define_method( "channels", &Mat::channels )
    .define_method( "at_d", &mat_at_d, (Arg("r"), Arg("c") = 0) )
    .define_method( "at_f", &mat_at_f, (Arg("r"), Arg("c") = 0) )
    .define_method( "at_8u", &mat_at_8u, (Arg("r"), Arg("c") = 0) )
    .define_method( "set_d", &mat_set_d )
    .define_method( "convert_to", &mat_convert_to, (Arg("type"), Arg("alpha") = 1.0, Arg("beta") = 0.0))
    .define_method( "to_a", &mat_to_a )
    .define_method( "svd", &mat_svd, 
        (Arg("w"), Arg("u"), Arg("vt"), Arg("flags") = 0 ) )
    .define_method( "inv", &mat_inv )
    .define_method( "pinv", &mat_pinv )
    .define_method( "add_mat", &mat_add_mat )
    .define_method( "add_const", &mat_add_const )
    .define_method( "subtract_mat", &mat_subtract_mat )
    .define_method( "subtract_const", &mat_subtract_const )
    .define_method( "subtract_reverse_const", &mat_subtract_reverse_const )
    .define_method( "mult_mat", &mat_mult_mat )
    .define_method( "mult_const", &mat_mult_const )
    .define_method( "transpose", &mat_transpose )
    .define_method( "size", &mat_size )
    .define_singleton_method( "copy_constructor", &copy_constructor )
    .define_singleton_method( "eye", &mat_eye, (Arg("rows"), Arg("cols"), Arg("type") = CV_64F) )
    .define_singleton_method( "zeros", &mat_zeros, (Arg("rows"), Arg("cols"), Arg("type") = CV_64F) )
    .define_singleton_method( "from_ruby", &from_ruby<cv::Mat> )
    .define_singleton_method( "merge", &mat_merge );

//  rb_mCVRice.define_module_function( "cvmat_to_mat", &cvmat_to_mat );
//  rb_mCVRice.define_module_function( "mat_to_cvmat", &mat_to_cvmat );

  // Define a few stub functions to ensure all of the to_/from_ruby 
  // templates are generated...
  // Still hurts my head figuring out why this is necessary..
  rb_mCVRice.define_module_function( "takes_a_mat", &takes_a_mat );
  rb_mCVRice.define_module_function( "takes_a_mat_ref", &takes_a_mat_ref );
  rb_mCVRice.define_module_function( "make_a_mat", &make_a_mat );

  define_class_under< _InputArray >( rb_mCVRice, "InputArray" );
  define_implicit_cast<Mat, _InputArray>();
}

//template<>
//Mat *from_ruby<Mat *>( Object obj )
//{
//  if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
//    return new Mat(cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) ));
//  } else {
//    rb_raise( rb_eTypeError, "Can't create a Mat  from this type" );
//  }
//
//}

//  template<>
//_InputArray from_ruby<_InputArray>( Object obj )
//{
//  if( obj.is_instance_of( rb_const_get( rb_cObject, rb_intern("CVFFI::CvMat") ) ) ) {
//    return cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) );
//  } else {
//    rb_raise( rb_eTypeError, "Can't create a _InputArray from this type" );
//  }
//
//}
//
//  template<>
//_InputArray *from_ruby<_InputArray *>( Object obj )
//{
//  //if( obj.is_instance_of( rb_const_get( rb_cObject, rb_intern("CVFFI::CvMat") ) ) ) {
//  if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
//    return new _InputArray(cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) ));
//  } else {
//    rb_raise( rb_eTypeError, "Can't create a _InputArray from this type" );
//  }
//
//}

