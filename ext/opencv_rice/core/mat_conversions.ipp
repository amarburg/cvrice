
#include <rice/Object.hpp>
#include <rice/Array.hpp>

#ifndef __OPENCV_RICE_MAT_CONVERSIONS_IPP__
#define __OPENCV_RICE_MAT_CONVERSIONS_IPP__

VALUE matrix_load(  void );

template <typename _T>
_T matx_from_ruby( Rice::Object obj )
{
  if(obj.rb_type() == T_DATA)
    return *Rice::Data_Type< _T >::from_ruby(obj);

  //if( !RTEST(rb_cMatrix ) ) rb_cMatrix = matrix_load();
 VALUE rb_cMatrix = matrix_load();

  if( obj.is_instance_of( rb_cMatrix ) ) {
    obj =  rb_funcall( obj, rb_intern("to_a") ,0 );
  } 

  if( obj.rb_type() == T_ARRAY ) {
    const Rice::Array a( obj );

    if( a[0].rb_type() != T_ARRAY )
      rb_raise( rb_eTypeError, "Trying to convert from Array which does not contains Arrays, it contains %s", a[0].class_of().name().c_str() );

    if( _T::rows != a.size() ) 
      rb_raise( rb_eTypeError, "Trying to generate Matx33f from Array with wrong number of rows (%lu)", a.size() );

    _T m;

    for( int r = 0; r < _T::rows; ++r ) {

      if( a[r].rb_type() != T_ARRAY )
        rb_raise( rb_eTypeError, "Found element in Array which is not Array: (%s)", a[0].class_of().name().c_str() );

      const Rice::Array row( a[r] );

      if( _T::cols != row.size() ) 
        rb_raise( rb_eTypeError, "Trying to generate Matx33f from Array with wrong number of columns (%lu)", row.size() );

      for( int c = 0; c < _T::cols; ++c ) {
        m(r,c) = rb_num2dbl(row[c]);
      } 
    }

    return m;
  } 

  std::string s("Unable to convert a ");
  s += obj.class_of().name().c_str();
  s += " to a Matx";
  rb_raise( rb_eTypeError, "%s", s.c_str() );
}

#endif
