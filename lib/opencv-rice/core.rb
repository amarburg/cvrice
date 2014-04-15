


module CVRice

  class Size < Size2i; end

  class Keypoint 
    def to_a
      [ x, y, size, angle, response, octave ]
    end

    def self.from_a( arr )
      Keypoint.new( *arr )
    end
  end

end
