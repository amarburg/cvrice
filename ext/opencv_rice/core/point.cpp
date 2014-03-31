
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "core.h"

// Still haven't sussed how Rice handles accessors for class members
// So I'm writing manual accessors for now
int get_point2i_x( const Point2i &pt ) { return pt.x; };
int get_point2i_y( const Point2i &pt ) { return pt.y; };

float get_point2f_x( const Point2f &pt ) { return pt.x; };
float get_point2f_y( const Point2f &pt ) { return pt.y; };

double get_point2d_x( const Point2d &pt ) { return pt.x; };
double get_point2d_y( const Point2d &pt ) { return pt.y; };

void init_point( Module &rb_mCVRice ) {
  define_class_under<Point2f>( rb_mCVRice, "Point2f" )
    .define_constructor( Constructor<Point2f, float, float>(), (Arg("x") = 0., Arg("y") = 0.) )
    .define_method( "x", &get_point2f_x )
    .define_method( "y", &get_point2f_y );

  define_class_under<Point2d>( rb_mCVRice, "Point2d" )
    .define_constructor( Constructor<Point2d, double, double>(), (Arg("x") = 0., Arg("y") = 0. ) )
    .define_method( "x", &get_point2d_x )
    .define_method( "y", &get_point2d_y );

  define_class_under<Point2i>( rb_mCVRice, "Point2i" )
    .define_constructor( Constructor<Point2i, int, int>(), (Arg("x") = 0, Arg("y") = 0) )
    .define_method( "x", &get_point2i_x )
    .define_method( "y", &get_point2i_y );
}




