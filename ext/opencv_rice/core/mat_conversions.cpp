
#include <rice/Array.hpp>
using namespace Rice;

#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
using namespace cv;


// Ensure the matrix packages is loaded and get the ID of the
//  Matrix class
//  FIX:  Having problems sharing the shared library.  Related to use of statics?
//static VALUE rb_cMatrix = Qnil;
VALUE matrix_load(  void )
{
  rb_require( "matrix" );
  return rb_const_get( rb_cObject, rb_intern("Matrix"));
}

// TODO.  Do this better.
Mat mat_from_ruby( Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Rice::Data_Type<Mat>::from_ruby(obj);
  } 

 // if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();
 VALUE rb_cMatrix = matrix_load();

 // TODO.  Get this working?
  // Since Matrix stores the data internally as an Array, this is no
  // more efficient than just getting the internal Array and dealing with 
  // that
//  if( obj.is_instance_of( rb_cMatrix ) ) {
//    int num_rows = FIX2INT(rb_funcall( obj, rb_intern("row_size"), 0 )),
//        num_cols = FIX2INT(rb_funcall( obj, rb_intern("column_size"), 0 ));
//
//    Mat m( num_rows, num_cols, CV_64F );
//
//
//    for( int r = 0; r < num_rows; ++r ) {
//      for( int c = 0; c < num_cols; ++c ) {
//        m.at<double>(r,c) = rb_num2dbl( rb_funcall( obj, rb_intern("[]"), 2, INT2FIX(r), INT2FIX(c) ) );
//      }
//    }
//
//    return m;
//  } else
    
    
  if( obj.is_instance_of( rb_cMatrix ) ) 
    obj = rb_funcall( obj, rb_intern("rows"), 0 );

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );
    //std::cout << "Convert from Array of size " << a.size() << std::endl;

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    int num_rows = a.size(), num_cols = Array(a[0]).size();
    Mat m( num_rows, num_cols, CV_64F );
    double *dbl = m.ptr<double>(0);
    int i = 0;

    for( Array::const_iterator row = a.begin(); row != a.end(); ++row ) {

      Object o( *row );
      if( o.rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", o.class_of().name().c_str() );

      const Array thisrow( o );
      for( Array::const_iterator col = thisrow.begin(); col != thisrow.end(); ++col, ++i ) {
        dbl[i] = rb_num2dbl( *col );
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


