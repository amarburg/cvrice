
#include <opencv2/core/core.hpp>
#include <opencv2/core/core_c.h>
using namespace cv;

#include <rice/Module.hpp>
using namespace Rice;

#include <stdio.h>

namespace CVRice {

  // n.b. I've changed the API.  It now assumes _m1 is an  N x 2 1-channel matrix, 
  // not a N x 1 2-channel matrix.  As such, count = _m1->rows, 
  // not _m1->rows * _m1->cols as before
  //
  // _m1 and _m2 must be the .x and .y values in normalized homogeneous points (x,y,1)
  //
  Mat cvFMaxReprojError( const Mat _m1, const Mat _m2, const Mat _model )
  {
    int i, count = _m1.rows;
    Mat m1_dbl, m2_dbl, f_dbl;
    _m1.convertTo( m1_dbl, CV_64F );
    _m2.convertTo( m2_dbl, CV_64F );
    _model.convertTo( f_dbl, CV_64F );

    const CvPoint2D64f* m1 = (const CvPoint2D64f*)m1_dbl.ptr<double>(0);
    const CvPoint2D64f* m2 = (const CvPoint2D64f*)m2_dbl.ptr<double>(0);
    const double *F = f_dbl.ptr<double>(0);

    Mat err_mat( _m1.rows, 1, CV_64F );
    double *err = err_mat.ptr<double>(0);

    for( i = 0; i < count; i++ )
    {
      double a, b, c, d1, d2, s1, s2;

      a = F[0]*m1[i].x + F[1]*m1[i].y + F[2];
      b = F[3]*m1[i].x + F[4]*m1[i].y + F[5];
      c = F[6]*m1[i].x + F[7]*m1[i].y + F[8];

      s2 = 1./(a*a + b*b);
      d2 = m2[i].x*a + m2[i].y*b + c;

      a = F[0]*m2[i].x + F[3]*m2[i].y + F[6];
      b = F[1]*m2[i].x + F[4]*m2[i].y + F[7];
      c = F[2]*m2[i].x + F[5]*m2[i].y + F[8];

      s1 = 1./(a*a + b*b);
      d1 = m1[i].x*a + m1[i].y*b + c;

      err[i] = (double)std::max(d1*d1*s1, d2*d2*s2);
    }

    return err_mat;
  }

  Mat cvHMaxReprojError( const Mat _m1, const Mat _m2, const Mat _model )
  {
    int i, count = _m1.rows;
    Mat h_dbl, m1_dbl, m2_dbl;
    _m1.convertTo( m1_dbl, CV_64F );
    _m2.convertTo( m2_dbl, CV_64F );
    _model.convertTo( h_dbl, CV_64F );
    Mat hinv_dbl = h_dbl.inv();

    const double* H = h_dbl.ptr<double>(0);
    const double* Hi = hinv_dbl.ptr<double>(0);
    const CvPoint2D64f* m1 = (const CvPoint2D64f*)m1_dbl.ptr<double>(0);
    const CvPoint2D64f* m2 = (const CvPoint2D64f*)m2_dbl.ptr<double>(0);

    Mat err_mat( _m1.rows, 1, CV_64F );
    double *err = err_mat.ptr<double>(0);

    for( i = 0; i < count; i++ )
    {
      double a, b, c, d1, d2;

      // This is H m1 
      a = H[0]*m1[i].x + H[1]*m1[i].y + H[2];
      b = H[3]*m1[i].x + H[4]*m1[i].y + H[5];
      c = H[6]*m1[i].x + H[7]*m1[i].y + H[8];

      a /= c;
      b /= c;
      d1 = (m2[i].x - a)*(m2[i].x - a) + (m2[i].y - b)*(m2[i].y - b);

      // This is H^(-1) m2
      a = Hi[0]*m2[i].x + Hi[1]*m2[i].y + Hi[2];
      b = Hi[3]*m2[i].x + Hi[4]*m2[i].y + Hi[5];
      c = Hi[6]*m2[i].x + Hi[7]*m2[i].y + Hi[8];


      a /= c;
      b /= c;
      d2 = (m1[i].x - a)*(m1[i].x - a) + (m1[i].y - b)*(m1[i].y - b);

      err[i] = (double)std::max(d1, d2);
    }

    return err_mat;
  }



  void init_reproj( Module &parent )
  {
    parent.define_module_function( "cvHMaxReprojError", &cvHMaxReprojError )
      .define_module_function( "cvFMaxReprojError", &cvFMaxReprojError );
  }

}
