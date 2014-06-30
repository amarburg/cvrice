
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include <string>
#include <vector>
using std::vector;

#include "core.h"

// Still haven't sussed how Rice handles accessors for class members
// So I'm writing manual accessors for now
template <typename _Tp>
_Tp get_size_width( const Size_<_Tp> &sz ) 
{ return sz.width; }

template <typename _Tp>
_Tp get_size_height( const Size_<_Tp> &sz ) 
{ return sz.height; }

template <typename _Tp>
void takes_a_size( const Size_<_Tp> &sz ) 
{;}

template <typename _Tp>
bool size_equality( const Size_<_Tp> a, const Size_<_Tp> b ) 
{ return (a.height == b.height) && (a.width == b.width); }



template <typename _Tp>
void define_size( Module &rb_mParent, const char *name )
{
  define_class_under< Size_<_Tp> >( rb_mParent, name )
    .define_constructor( Constructor<Size_<_Tp>, int, int>(), (Arg("x")=0, Arg("y")=0) )
    .define_method( "width", &get_size_width<_Tp> )
    .define_method( "height", &get_size_height<_Tp> )
    .define_method( "==", &size_equality<_Tp> );

}


void init_size( Module &rb_mCVRice ) {

  define_size<int>( rb_mCVRice, "Size2i" );
  define_size<float>( rb_mCVRice, "Size2f" );

   rb_mCVRice.define_module_function( "takes_a_size2i", &takes_a_size<int> )
     .define_module_function( "takes_a_size2f", &takes_a_size<float> );

  define_implicit_cast<Size2i,Size2f>();
  define_implicit_cast<Size2f,Size2i>();
}




