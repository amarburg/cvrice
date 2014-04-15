
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
// 
Mat mat_from_ruby( Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Rice::Data_Type<Mat>::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

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


// TODO.  Can I template my specialization for the variety of Matx<>
// ... and how would I "instantiate" it?
  Matx33d matx33d_from_ruby( Object obj )
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
      rb_raise( rb_eTypeError, "Trying to generate Matx33d from Array with wrong number of rows (%lu)", a.size() );

    const int num_rows = 3, num_cols = 3;
    Matx33d m;

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );

      if( 3 != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx33d from Array with wrong number of columns (%lu)", row.size() );

      for( int c = 0; c < num_cols; ++c ) {
        m(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx33d";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}



  Matx33f matx33f_from_ruby( Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type< Matx33f >::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    if( 3 != a.size() ) 
      rb_raise( rb_eTypeError, "Trying to generate Matx33f from Array with wrong number of rows (%lu)", a.size() );

    const int num_rows = 3, num_cols = 3;
    Matx33f m;

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );

      if( 3 != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx33f from Array with wrong number of columns (%lu)", row.size() );

      for( int c = 0; c < num_cols; ++c ) {
        m(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx33f";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}



  Matx22d matx22d_from_ruby( Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type< Matx22d >::from_ruby(obj);
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

    if( 2 != a.size() ) 
      rb_raise( rb_eTypeError, "Trying to generate Matx22d from Array with wrong number of rows (%lu)", a.size() );

    const int num_rows = 2, num_cols = 2;
    Matx22d m;

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );

      if( 2 != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx22d from Array with wrong number of columns (%lu)", row.size() );

      for( int c = 0; c < num_cols; ++c ) {
        m(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx22d";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}



  Matx22f matx22f_from_ruby( Object obj )
{
  if(obj.rb_type() == T_DATA)
  {
    return *Data_Type< Matx22f >::from_ruby(obj);
  } 

  if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Array a( obj );

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    if( 2 != a.size() ) 
      rb_raise( rb_eTypeError, "Trying to generate Matx22f from Array with wrong number of rows (%lu)", a.size() );

    const int num_rows = 2, num_cols = 2;
    Matx22f m;

    for( int r = 0; r < num_rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Array row( a[r] );

      if( 2 != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx22f from Array with wrong number of columns (%lu)", row.size() );

      for( int c = 0; c < num_cols; ++c ) {
        m(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx22f";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}

