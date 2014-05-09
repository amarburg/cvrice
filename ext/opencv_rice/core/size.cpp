
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include <vector>
using std::vector;

#include "core.h"

// Still haven't sussed how Rice handles accessors for class members
// So I'm writing manual accessors for now
int get_size2i_width( const Size2i &sz ) { return sz.width; }
int get_size2i_height( const Size2i &sz ) { return sz.height; }
float get_size2f_width( const Size2f &sz ) { return sz.width; }
float get_size2f_height( const Size2f &sz ) { return sz.height; }

void takes_a_size2f( const Size2f &sz ) {;}
void takes_a_size2i( const Size2i &sz ) {;}

void init_size( Module &rb_mCVRice ) {

  define_class_under<Size2i>( rb_mCVRice, "Size2i" )
    .define_constructor( Constructor<Size2i, int, int>(), (Arg("x")=0, Arg("y")=0) )
    .define_method( "width", &get_size2i_width )
    .define_method( "height", &get_size2i_height );

  define_class_under<Size2f>( rb_mCVRice, "Size2f" )
    .define_constructor( Constructor<Size2f, float, float>(), (Arg("x")=0., Arg("y")=0.) )
    .define_method( "width", &get_size2f_width )
    .define_method( "height", &get_size2f_height );

  rb_mCVRice.define_module_function("takes_a_size2f", &takes_a_size2f )
    .define_module_function( "takes_a_size2i", &takes_a_size2i );

  define_implicit_cast<Size2i,Size2f>();
  define_implicit_cast<Size2f,Size2i>();
}




