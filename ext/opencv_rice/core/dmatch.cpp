
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

int dmatch_queryIdx( const DMatch &dm ) { return dm.queryIdx; }
int dmatch_trainIdx( const DMatch &dm ) { return dm.trainIdx; }
int dmatch_imgIdx( const DMatch &dm ) { return dm.imgIdx; }
float dmatch_distance( const DMatch &dm ) { return dm.distance; }


void init_dmatch( Module &rb_mParent )
{

  define_class_under<DMatch>( rb_mParent, "DMatch" )
    .define_constructor( Constructor<cv::DMatch,int,int,float>() )
    .define_method( "queryIdx", &dmatch_queryIdx )
    .define_method( "trainIdx", &dmatch_trainIdx )
    .define_method( "distance", &dmatch_distance )
    .define_method( "imgIdx", &dmatch_imgIdx );

}
