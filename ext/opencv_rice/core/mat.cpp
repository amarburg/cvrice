


#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <ffi_c/Pointer.h>

#include <iostream>


int get_mat_rows( const Mat &m ) { return m.rows; }
int get_mat_cols( const Mat &m ) { return m.cols; }


template<class T>
T *ptr_from_ffi_struct( Object obj )
{
  Object pointer( obj.call( rb_intern("pointer") ) );
  Pointer *ptr;
  Data_Get_Struct( pointer.value(), struct Pointer, ptr );
  return reinterpret_cast<T *>(ptr->memory.address);
}


Mat cvmat_to_mat( Object obj )
{
  if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
    return cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) );
  } else {
    rb_raise( rb_eTypeError, "Can't create a Mat from this type" );
  }

}

Object mat_to_cvmat( Mat &mat )
{
  CvMat cvmat = mat;

  VALUE ptr = rbffi_Pointer_NewInstance( cvCloneMat( &cvmat ) );
  VALUE args[] = {ptr};
  return rb_funcall2( rb_eval_string( "CVFFI::CvMat" ), rb_intern("new"), 1, args );
}

void takes_a_mat( Mat mat ) { ; }



void init_mat( Module &rb_mCVRice )
{
  Data_Type<Mat> rb_cMat = define_class_under< Mat >( rb_mCVRice, "Mat" )
    .define_constructor( Constructor<Mat>() )
    .define_method( "rows", &get_mat_rows )
    .define_method( "cols", &get_mat_cols );

  rb_mCVRice.define_module_function( "cvmat_to_mat", &cvmat_to_mat );
  rb_mCVRice.define_module_function( "mat_to_cvmat", &mat_to_cvmat );

  // Define a few stub functions to ensure all of the to_/from_ruby templates are generated...
  rb_mCVRice.define_module_function( "takes_a_mat", &takes_a_mat );

  define_class_under< _InputArray >( rb_mCVRice, "InputArray" );
  define_implicit_cast<Mat, _InputArray>();

  define_class_under< cv::String >( rb_mCVRice, "String" );
}

//template<>
//Mat from_ruby<Mat>( Object obj )
//{
//  if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
//    return cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) );
//  } else {
//    rb_raise( rb_eTypeError, "Can't create a Mat from this type" );
//  }
//
//}
//
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

