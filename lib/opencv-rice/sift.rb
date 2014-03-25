


module CVRice

  class SIFT

    alias_method :detect_c, :detect
    def detect( image, mask = nil )
      kps = [] # KeypointArray.new
      mask ||= Mat.new

      detect_c( image )
    end

  end
end
