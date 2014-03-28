
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <iostream>

#include "cvffi_compat.h"


// Ensure the matrix packages is loaded and get the ID of the
//  Matrix class
static VALUE rb_cMatrix = Qnil;
static VALUE matrix_load(  void )
{
  rb_require( "matrix" );
  return rb_const_get( rb_cObject, rb_intern("Matrix"));
}

// TODO.  Do this better.
  template<>
Mat from_ruby<Mat>( Object obj )
{
  //  //if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
  //  //  return cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) );
  //  //} else
  //

  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type<Mat>::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    //std::cout << "Convert from Matrix" << std::endl;
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );
    //std::cout << "Convert from Array of size " << a.size() << std::endl;

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    int num_rows = a.size(), num_cols = Array(a[0]).size();
    Mat m( num_rows, num_cols, CV_64F );

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );
      for( int c = 0; c < num_cols; ++c ) {
        m.at<double>(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += '(';
  s+= (int)obj.rb_type();
  s+= ')';
  s += " to Mat";
  rb_raise( rb_eTypeError, "%s", s.c_str() );


}


// TODO:  These are madly non-type-safe.  
double mat_at_d( Mat const &m, int r, int c ) {
  switch(m.depth()) {
    case CV_32F:
      return (double)m.at<float>(r,c);
    case CV_64F:
      return m.at<double>(r,c);
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_at_d" );
  }
}
float mat_at_f( Mat const &m, int r, int c ) {
  switch(m.depth()) {
    case CV_32F:
      return m.at<float>(r,c);
    case CV_64F:
      return (float)m.at<double>(r,c);
    default:
      rb_raise( rb_eTypeError, "Haven't handled this case in mat_at_f" );
  }
}

int mat_get_rows( const Mat &m ) { return m.rows; }
int mat_get_cols( const Mat &m ) { return m.cols; }

void takes_a_mat( Mat mat ) { ; }
void takes_a_mat_ref( Mat const &mat ) { ; }

// A set of simply constructor functions 
Mat make_a_mat( Mat mat ) { return mat; }

Mat copy_constructor( Mat const &in ) { return Mat(in); }


void init_mat( Module &rb_mCVRice )
{
  Data_Type<Mat> rb_cMat = define_class_under< Mat >( rb_mCVRice, "Mat" )
    .define_constructor( Constructor<Mat>())
    .define_method( "rows", &mat_get_rows )
    .define_method( "cols", &mat_get_cols )
    .define_method( "at_d", &mat_at_d )
    .define_method( "at_f", &mat_at_f )
    .define_singleton_method( "copy_constructor", &copy_constructor );

  rb_mCVRice.define_module_function( "cvmat_to_mat", &cvmat_to_mat );
  rb_mCVRice.define_module_function( "mat_to_cvmat", &mat_to_cvmat );

  // Define a few stub functions to ensure all of the to_/from_ruby 
  // templates are generated...
  // Still hurts my head figuring out why this is necessary..
  rb_mCVRice.define_module_function( "takes_a_mat", &takes_a_mat );
  rb_mCVRice.define_module_function( "takes_a_mat_ref", &takes_a_mat_ref );
  rb_mCVRice.define_module_function( "make_a_mat", &make_a_mat );
  rb_mCVRice.define_module_function( "from_ruby", &from_ruby<cv::Mat> );

  define_class_under< _InputArray >( rb_mCVRice, "InputArray" );
  define_implicit_cast<Mat, _InputArray>();

  define_class_under< cv::String >( rb_mCVRice, "String" );
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

