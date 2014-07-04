
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "vector.h"

namespace CVRice {

  double scalar_element( const Scalar s, int i )
  {
    if( (i<0) || (i>3) )
      rb_raise( rb_eArgError, "Trying to access out of bounds in Scalar" );

    return s[i];
  }

  void init_scalar( Module &rb_mParent )
  {
    define_class_under< Scalar >( rb_mParent, "Scalar" )
      .define_constructor( Constructor< Scalar,double,double,double,double >(),
          (Arg("v0")=0.0, Arg("v1")=0.0, Arg("v2")=0.0, Arg("v3")=0.0))
      .define_method( "[]", &scalar_element )
      .define_method( "to_a", &vec_to_arr< Vec<double,4> >)
      .define_singleton_method( "all", &Scalar::all );

    define_implicit_cast<Scalar,Vec4d>();
  }

}
