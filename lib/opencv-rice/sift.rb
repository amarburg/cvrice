


module CVRice

  class SIFT

    alias_method :detect_c, :detect
    def detect( image, mask = nil )
      mask ||= Mat.new

      detect_c( image )
    end

    alias_method :describe_c, :describe
    def describe( image, mask = nil )
      mask ||= Mat.new
      descriptors = Mat.new

      kps = describe_c( image, mask, descriptors )
      [kps, descriptors]
    end
  end
end
