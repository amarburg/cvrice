
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "core.h"

template <typename _T>
float set_point_x( _T &pt, const typename _T::value_type v ) { return (pt.x=v); };

template <typename _T>
float set_point_y( _T &pt, const typename _T::value_type v ) { return (pt.y=v); };

template <typename _T>
typename _T::value_type get_point_x( const _T &pt ) { return pt.x; };

template <typename _T>
typename _T::value_type get_point_y( const _T &pt ) { return pt.y; };

template <typename _T>
_T subtract( _T a, _T b) { return a-b; };

template <typename _T>
double square_distance_to( _T &a, const _T &b) { return ((a.x - b.x)*(a.x - b.x)) + ((a.y-b.y)*(a.y-b.y)); }

template <typename _T>
double distance_to( _T &a, const _T &b) { return sqrt( square_distance_to<_T>(a,b) ); }

void init_point( Module &rb_mCVRice ) {
  define_class_under<Point2f>( rb_mCVRice, "Point2f" )
    .define_constructor( Constructor<Point2f, float, float>(), (Arg("x") = 0., Arg("y") = 0.) )
    .define_method( "x", &get_point_x<Point2f> )
    .define_method( "y", &get_point_y<Point2f> )
    .define_method( "x=", &set_point_x<Point2f> )
    .define_method( "y=", &set_point_y<Point2f> )
    .define_method( '-', &subtract<Point2f>)
    .define_method( "distance_to", &distance_to<Point2d> )
    .define_method( "square_distance_to", &square_distance_to<Point2d> )
    .define_method( "sqr_distance_to", &square_distance_to<Point2d> );

  define_class_under<Point2d>( rb_mCVRice, "Point2d" )
    .define_constructor( Constructor<Point2d, double, double>(), (Arg("x") = 0., Arg("y") = 0. ) )
    .define_method( "x", &get_point_x<Point2d> )
    .define_method( "y", &get_point_y<Point2d> )
    .define_method( "x=", &set_point_x<Point2d> )
    .define_method( "y=", &set_point_y<Point2d> )
    .define_method( '-', &subtract<Point2d> )
    .define_method( "dot", &Point2d::dot )
    .define_method( "distance_to", &distance_to<Point2d> )
    .define_method( "square_distance_to", &square_distance_to<Point2d> )
    .define_method( "sqr_distance_to", &square_distance_to<Point2d> );

  define_class_under<Point2i>( rb_mCVRice, "Point2i" )
    .define_constructor( Constructor<Point2i, int, int>(), (Arg("x") = 0, Arg("y") = 0) )
    .define_method( "x", &get_point_x<Point2i> )
    .define_method( "y", &get_point_y<Point2i> );

  define_implicit_cast<Point2f,Point2d>();
  define_implicit_cast<Point2f,Point2i>();

  define_implicit_cast<Point2d,Point2f>();
  define_implicit_cast<Point2d,Point2i>();

  define_implicit_cast<Point2d,Point2i>();
  define_implicit_cast<Point2f,Point2i>();
}




