
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;


// Ensure the matrix packages is loaded and get the ID of the
//  Matrix class
static VALUE rb_cMatrix = Qnil;
static VALUE matrix_load(  void )
{
  rb_require( "matrix" );
  return rb_const_get( rb_cObject, rb_intern("Matrix"));
}

// TODO.  Do this better.
  template<>
Mat from_ruby<Mat>( Object obj )
{
  //  //if( obj.is_instance_of( rb_eval_string( "CVFFI::CvMat" ) ) ) {
  //  //  return cvarrToMat( ptr_from_ffi_struct<CvMat>( obj ) );
  //  //} else
  //

  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type<Mat>::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    //std::cout << "Convert from Matrix" << std::endl;
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );
    //std::cout << "Convert from Array of size " << a.size() << std::endl;

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    int num_rows = a.size(), num_cols = Array(a[0]).size();
    Mat m( num_rows, num_cols, CV_64F );

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );
      for( int c = 0; c < num_cols; ++c ) {
        m.at<double>(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += '(';
  s+= (int)obj.rb_type();
  s+= ')';
  s += " to Mat";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}


// TODO.  Can I template my specialization for the variety of Matx<>
// ... and how would I "instantiate" it?
template<> 
cv::Matx33d from_ruby< cv::Matx33d >( Rice::Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type< Matx33d >::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );
    //std::cout << "Convert from Array of size " << a.size() << std::endl;

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    if( 3 != a.size() ) 
      rb_raise( rb_eTypeError, "Trying to generate Matx from Array with wrong number of rows" );

    int num_rows = 3, num_cols = 3;
    Mat m( num_rows, num_cols, CV_64F );

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );

      if( 3 != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx from Array with wrong number of columns" );

      for( int c = 0; c < num_cols; ++c ) {
        m.at<double>(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx33d";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}



