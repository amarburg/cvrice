


module CVRice

  class KeyPoint 

    def dup
      Keypoint.new( *to_a )
    end

    def to_a
      [ x, y, size, angle, response, octave ]
    end

    def self.from_a( arr )
      Keypoint.new( *arr )
    end
  end

  class Keypoint < KeyPoint
  end

end
