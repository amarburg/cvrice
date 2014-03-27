#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <ffi_c/Pointer.h>

#include <iostream>


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


