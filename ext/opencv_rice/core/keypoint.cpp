
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "core.h"

// Still haven't sussed how Rice handles accessors for class members
// So I'm writing manual accessors for now
float get_keypoint_x( const KeyPoint &kp ) { return kp.pt.x; };
float get_keypoint_y( const KeyPoint &kp ) { return kp.pt.y; };
float get_keypoint_size( const KeyPoint &kp ) { return kp.size; };
float get_keypoint_angle( const KeyPoint &kp ) { return kp.angle; };
float get_keypoint_response( const KeyPoint &kp ) { return kp.response; };
int   get_keypoint_octave( const KeyPoint &kp ) { return kp.octave; };
int   get_keypoint_class_id( const KeyPoint &kp ) { return kp.class_id; };

void init_keypoint( Module &rb_mCVRice ) {

  define_class_under<KeyPoint>( rb_mCVRice, "Keypoint" )
    .define_constructor( Constructor<KeyPoint, float, float, float, float, float, int, int>(),
        ( Arg("x") = 0, Arg("y") = 0, Arg("size") = 0, Arg( "angle" ) = -1, Arg("response") = 0,
          Arg("octave") = 0, Arg("class_id") = -1 ) )
    .define_method( "x", &get_keypoint_x )
    .define_method( "y", &get_keypoint_y )
    .define_method( "size", &get_keypoint_size )
    .define_method( "angle", &get_keypoint_angle )
    .define_method( "response", &get_keypoint_response )
    .define_method( "octave", &get_keypoint_octave )
    .define_method( "class_id", &get_keypoint_class_id );

  //define_class_under<KeyPointVector>( rb_mCVRice, "KeypointArray" )
  //  .define_constructor( Constructor<KeypointArray>() );

}



