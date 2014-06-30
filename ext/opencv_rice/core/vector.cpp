
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

void init_vector( Module &parent ) {

  typedef double &(Vec2d::*vec2d_accessor)( int i );
  define_class_under<Vec2d>( parent, "Vec2d" )
    .define_constructor( Constructor<Vec2d, double, double>(), (Arg("a") = 0, Arg("b") = 0) )
    .define_method( "[]", vec2d_accessor(&Vec2d::operator[]) );

  typedef double &(Vec3d::*vec3d_accessor)( int i );
  define_class_under<Vec3d>( parent, "Vec3d" )
    .define_constructor( Constructor<Vec3d, double, double, double>(), (Arg("a") = 0, Arg("b") = 0, Arg("c") = 0) )
    .define_method( "[]", vec3d_accessor(&Vec3d::operator[]) )
    .define_method( "to_a", &vec3d_to_a )
    .define_method( "to_mat", &matx_to_mat<Vec3d> );

  typedef double &(Vec4d::*vec4d_accessor)( int i );
  define_class_under<Vec4d>( parent, "Vec4d" )
    .define_constructor( Constructor<Vec4d, double, double, double, double>(),
        (Arg("a") = 0, Arg("b") = 0, Arg("c") = 0, Arg("d") = 0) )
    .define_method( "[]", vec4d_accessor(&Vec4d::operator[]) );
}




