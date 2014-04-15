
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <iostream>

#include "mat_conversions.h"

void takes_a_matx22d( Matx22d mat ) { ; }
void takes_a_matx22f( Matx22f mat ) { ; }
void takes_a_matx33d( Matx33d mat ) { ; }
void takes_a_matx33f( Matx33f mat ) { ; }

template <typename _Tp> _Tp matx_inv( const _Tp m ) { return m.inv(); }

// Borrow these functions
static Mat make_a_mat( Mat mat ) { return mat; }
Object mat_to_a( Mat &m );

//=========================================================


template <typename _Tp> void define_matx( Module &rb_mCVRice, const char *name )
{
  define_class_under< _Tp >( rb_mCVRice, name )
    .define_constructor( Constructor<_Tp>() )
    .define_method( "to_a", mat_to_a )
    .define_method( "to_mat", make_a_mat )
    .define_method( "inv", matx_inv< _Tp > )
    .define_method( "pinv", matx_inv< _Tp > )     // pseudo-inverse is inverse for square matrices
     .define_singleton_method( "from_ruby", &from_ruby<_Tp> );

  define_implicit_cast< _Tp, Mat>();
}

void init_matx( Module &rb_mCVRice )
{

  define_matx< Matx22d >( rb_mCVRice, "Matx22d");
  define_matx< Matx22f >( rb_mCVRice, "Matx22f");
  define_matx< Matx33d >( rb_mCVRice, "Matx33d");
  define_matx< Matx33f >( rb_mCVRice, "Matx33f");

  rb_mCVRice.define_module_function( "takes_a_matx22d", &takes_a_matx22d );
  rb_mCVRice.define_module_function( "takes_a_matx22f", &takes_a_matx22f );
  rb_mCVRice.define_module_function( "takes_a_matx33d", &takes_a_matx33d );
  rb_mCVRice.define_module_function( "takes_a_matx33f", &takes_a_matx33f );
}

