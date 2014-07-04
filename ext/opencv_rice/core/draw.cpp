
#include <rice/Module.hpp>
#include <rice/Constructor.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
using namespace cv;

namespace CVRice {

  void cvrice_line( Mat &img, const Point pt1, const Point pt2, const Scalar &color,
      int thickness, int lineType, int shift )
  {
    line( img, pt1, pt2, color, thickness, lineType, shift );
  }

  void cvrice_puttext( Mat &img, const std::string &text, Point org, int fontFace, double fontScale, const Scalar &color, int thickness,
      int lineType, bool bottomLeftOrigin )
  {
    putText( img, text, org, fontFace, fontScale, color, thickness, lineType, bottomLeftOrigin );
  }

  void init_draw( Module &rb_mParent )
  {
    rb_mParent.define_module_function( "line", &cvrice_line,
        (Arg("img"), Arg("pt1"), Arg("pt2"), Arg("color"), Arg("thickness")=1,
         Arg("lineType")=(int)LINE_8, Arg("shift") = 0) )
      .define_module_function("put_text", &cvrice_puttext,
          (Arg("img"), Arg("text"), Arg("origin"), Arg("fontface"), Arg("fontscale"), 
           Arg("color"), Arg("thickness") = 1, Arg("lineType") = 8 , Arg("bottomLeftOrigin") = false ));
  }

}
