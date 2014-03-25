
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/nonfree.hpp>
using namespace cv;



void init_sift( Module &rb_mCVRice )
{
  typedef void (SIFT::*sift_detect)(InputArray, InputArray, std::vector<KeyPoint>& ) const;
  typedef void (SIFT::*sift_detect_describe)(InputArray, InputArray,
      std::vector<KeyPoint>& , OutputArray, bool ) const;

  define_class_under<SIFT>( rb_mCVRice, "SIFT" )
    .define_constructor( Constructor<SIFT, int, int, double, double, double>(), 
        (Arg("nfeatures") = 0, Arg("nOctaveLayers") = 3, Arg("contrastThreshold") = 0.04,
         Arg("edgeThreshold") = 10, Arg("sigma") = 1.6) )
    .define_method( "descriptor_size", &SIFT::descriptorSize )
    .define_method( "descriptor_type", &SIFT::descriptorType )
    .define_method( "default_norm", &SIFT::defaultNorm )
    .define_method( "detect", sift_detect(&SIFT::operator()) )
    .define_method( "detect_and_describe", sift_detect_describe(&SIFT::operator()) );
}
