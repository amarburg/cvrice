


module CVRice

  ALL_POINTS = 0
  RANSAC = 4
  LMEDS = 8

  def findHomography( a, b, method = ALL_POINTS, reproj_threshold = 3, mask = nil )
    mask ||= Mat.new

    # TODO.  Convoluted because I can't figure out how to handle the mask as an 
    # optional/default value argument in Rice.
    calculateHomography( a, b, mask ,method, reproj_threshold )
  end
  module_function :findHomography

end
