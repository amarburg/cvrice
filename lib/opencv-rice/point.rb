
module CVRice

  class Point < Point2d; end

  class Point2f
    def to_Vector( homogeneous = true )
      Vector[ x, y, 1.0 ]
    end
  end

  class Point2d
    def to_Vector( homogeneous = true )
      Vector[ x, y, 1.0 ]
    end
  end

end
