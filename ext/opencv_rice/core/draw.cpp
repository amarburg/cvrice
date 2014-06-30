
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

  void init_draw( Module &rb_mParent )
  {
    rb_mParent.define_module_function( "line", &cvrice_line,
        (Arg("img"), Arg("pt1"), Arg("pt2"), Arg("color"), Arg("thickness")=1,
         Arg("lineType")=(int)LINE_8, Arg("shift") = 0) );
  }

}
