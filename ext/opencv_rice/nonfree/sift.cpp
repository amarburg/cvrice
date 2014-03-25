
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/nonfree.hpp>
using namespace cv;


// Define  slightly a more functional forms
Array sift_detect( SIFT &sift, InputArray img )   //, InputArray mask  )
{
  std::vector<KeyPoint> kps;
  Mat mask;
  sift( img, mask, kps );
  return Array(kps.begin(), kps.end());
}

Array sift_detect_describe( SIFT &sift, InputArray img, InputArray mask, Mat &descriptors, bool use_provided = false )
{
  std::vector<KeyPoint> kps;
  sift( img, mask, kps, descriptors, use_provided );
  return Array(kps.begin(), kps.end());
}


void init_sift( Module &rb_mCVRice )
{
  //typedef void (SIFT::*sift_detect)(InputArray, InputArray, std::vector<KeyPoint>& ) const;
  //typedef void (SIFT::*sift_detect_describe)(InputArray, InputArray,
  //    std::vector<KeyPoint>& , OutputArray, bool ) const;

  define_class_under<SIFT>( rb_mCVRice, "SIFT" )
    .define_constructor( Constructor<SIFT, int, int, double, double, double>(), 
        (Arg("nfeatures") = 0, Arg("nOctaveLayers") = 3, Arg("contrastThreshold") = 0.04,
         Arg("edgeThreshold") = 10, Arg("sigma") = 1.6) )
    .define_method( "descriptor_size", &SIFT::descriptorSize )
    .define_method( "descriptor_type", &SIFT::descriptorType )
    .define_method( "default_norm", &SIFT::defaultNorm )
    .define_method( "detect", &sift_detect )
    .define_method( "describe", &sift_detect_describe, (Arg("image"), Arg("mask"), Arg("descriptors"), Arg("use_provided") = false) );

    //.define_method( "detect", sift_detect(&SIFT::operator()) )
}
