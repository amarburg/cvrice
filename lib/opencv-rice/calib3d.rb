


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

  ITERATIVE = 0
  EPNP      = 1
  P3P       = 2

  def solvePnP( obj, image, cameraMatrix, opts = {} )
    method = opts[:method] || ITERATIVE
    distortion = opts[:distortion] || Mat.new

    if opts[:rhint] and opts[:thint]

      rhint = if opts[:rhint].rows*opts[:rhint].cols == 9
                rodrigues( opts[:rhint] )
              else
                Mat.new(opts[:rhint])
              end

      thint = Mat.new( opts[:thint] )

    calculatePnPHint( obj, image, cameraMatrix, distortion, rhint, thint, method  )
    elsif opts[:rhint] or opts[:thint]
      raise "Both :rhint and :thint must be provided..."
    else
    calculatePnP( obj, image, cameraMatrix, distortion, method  )
    end
  end
  module_function :solvePnP
end
