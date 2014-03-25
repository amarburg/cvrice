
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
using namespace Rice;



/* The magic entry point function for the shared library. */
extern "C"
void Init_libopencv_rice_c( void ) {

  Module rb_MCVRice = define_module( "CVRice" );
}
