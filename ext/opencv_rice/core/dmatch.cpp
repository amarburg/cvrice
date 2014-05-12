
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

#include "dmatch.h"

namespace CVRice {

  int dmatch_queryIdx( const DMatch &dm ) { return dm.queryIdx; }
  int dmatch_trainIdx( const DMatch &dm ) { return dm.trainIdx; }
  int dmatch_imgIdx( const DMatch &dm ) { return dm.imgIdx; }
  float dmatch_distance( const DMatch &dm ) { return dm.distance; }

  void takes_a_dmatch_vector_ref( const DMatchVector &vec ) { ; }
  void takes_a_dmatch_vector( const DMatchVector vec ) { ; }
  DMatchVector returns_a_dmatch_vector( void ) { return DMatchVector(); }

  void init_dmatch( Module &rb_mParent )
  {
    define_class_under<DMatch>( rb_mParent, "DMatch" )
      .define_constructor( Constructor<cv::DMatch,int,int,float>() )
      .define_method( "queryIdx", &dmatch_queryIdx )
      .define_method( "trainIdx", &dmatch_trainIdx )
      .define_method( "distance", &dmatch_distance )
      .define_method( "imgIdx", &dmatch_imgIdx );

    rb_mParent.define_module_function( "takes_a_dmatch_vector", &takes_a_dmatch_vector )
      .define_module_function( "takes_a_dmatch_vector_ref", &takes_a_dmatch_vector_ref )
      .define_module_function( "returns_a_dmatch_vector", &returns_a_dmatch_vector );
  }

}
