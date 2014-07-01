
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "core.h"
#include "matx.h"

Object vec3d_to_a( const Vec3d &vec )
{
  Array arr;
  arr.push( vec[0] );
  arr.push( vec[1] );
  arr.push( vec[2] );
  return arr;
}

template <typename _Vec>
Object vec_to_arr( const _Vec &vec )
{
  Array arr;
  for( int i = 0; i < _Vec::channels; ++i ) arr.push( vec[i] );
  return arr;
}


template <typename _Vec>
void define_vec2( Module &rb_mParent, const char *name  )
{
  typedef typename _Vec::value_type &(_Vec::*vec_accessor)( int i );
  define_class_under<_Vec>( rb_mParent, name )
    .define_constructor( Constructor<_Vec, typename _Vec::value_type, typename _Vec::value_type >(), 
        (Arg("a") = 0, Arg("b") = 0) ) 
    .define_method( "[]", vec_accessor(&_Vec::operator[]) )
    .define_method( "to_a", &vec_to_arr<_Vec>)
    .define_method( "to_mat", &matx_to_mat<_Vec> );
}

template <typename _Vec>
void define_vec3( Module &rb_mParent, const char *name  )
{
  typedef typename _Vec::value_type &(_Vec::*vec_accessor)( int i );
  define_class_under<_Vec>( rb_mParent, name )
    .define_constructor( Constructor<_Vec, typename _Vec::value_type, typename _Vec::value_type,
        typename _Vec::value_type>(),
        (Arg("a") = 0, Arg("b") = 0, Arg("c")=0) ) 
    .define_method( "[]", vec_accessor(&_Vec::operator[]) )
    .define_method( "to_a", &vec_to_arr<_Vec>)
    .define_method( "to_mat", &matx_to_mat<_Vec> );
}


template <typename _Vec>
void define_vec4( Module &rb_mParent, const char *name  )
{
  typedef typename _Vec::value_type &(_Vec::*vec_accessor)( int i );
  define_class_under<_Vec>( rb_mParent, name )
    .define_constructor( Constructor<_Vec, typename _Vec::value_type, typename _Vec::value_type,
        typename _Vec::value_type, typename _Vec::value_type>(), 
        (Arg("a") = 0, Arg("b") = 0, Arg("c")=0, Arg("d") = 0) ) 
    .define_method( "[]", vec_accessor(&_Vec::operator[]) )
    .define_method( "to_a", &vec_to_arr<_Vec>)
    .define_method( "to_mat", &matx_to_mat<_Vec> );
}

void init_vector( Module &parent ) {

  // How to expand this to variable lengths
  // (run into problems with default args)
  define_vec2<Vec2i>( parent, "Vec2i" );
  define_vec2<Vec2f>( parent, "Vec2f" );
  define_vec2<Vec2d>( parent, "Vec2d" );

  define_vec3<Vec3i>( parent, "Vec3i" );
  define_vec3<Vec3f>( parent, "Vec3f" );
  define_vec3<Vec3d>( parent, "Vec3d" );

  define_vec4<Vec4i>( parent, "Vec4i" );
  define_vec4<Vec4f>( parent, "Vec4f" );
  define_vec4<Vec4d>( parent, "Vec4d" );
}




