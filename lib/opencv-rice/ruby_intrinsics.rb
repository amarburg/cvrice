
class Float
  alias_method :add_real, :+
  def +(b)
    case b
    when CVRice::Mat
      b + self
    else
      add_real( b )
    end
  end

  alias_method :subtract_real, :-
  def -(b)
    case b
    when CVRice::Mat
      b.subtract_reverse_const( self )
    else
      subtract_real b
    end
  end

  alias_method :multiply_real, :*
  def *(b)
    case b
    when CVRice::Mat
      b * self
    else
      multiply_real b
    end
  end
end

#class Array
#  def merge( type = :CV_32FC3 )
#    a = self
#    a << nil while a.length < 4
#
#    # TODO.  Automatically determine multichannel type based on types and number of arguments
#    dst = CVFFI::Mat.new( a.first.rows, a.first.cols, type: type )
#    args = a.first(4) + [dst]
#    cvMerge( *args )
#    dst
#  end
#end
#
## Monkey with Matrix and Vector's coercion functions
#class Vector
#  alias :coerce_orig :coerce
#  def coerce(other)
#    case other
#    when CvMat
#      nil
#    else
#      coerce_orig(other)
#    end
#  end
#end


