


module CVRice

  class VecNd
    def self.new( *args )
      raise "Not implemented yet..."
    end
  end

  class Vec3d
    def to_vector
      Vector[ *(to_a) ]
    end

    def print(*args)
      Mat.columns( [to_a] ).print( *args )
    end
  end
end
