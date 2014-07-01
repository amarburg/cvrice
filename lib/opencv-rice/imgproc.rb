
require_relative 'imgproc/misc'


module CVRice

  module Convert

    # Just the subset I need for right now
    BGR2BGRA     = 0
    RGB2RGBA     = BGR2BGRA

    BGRA2BGR     = 1
    RGBA2RGB     = BGRA2BGR

    BGR2RGBA     = 2
    RGB2BGRA     = BGR2RGBA

    RGBA2BGR     = 3
    BGRA2RGB     = RGBA2BGR

    BGR2RGB      = 4
    RGB2BGR      = BGR2RGB

    BGRA2RGBA    = 5
    RGBA2BGRA    = BGRA2RGBA

    BGR2GRAY     = 6
    RGB2GRAY     = 7
    GRAY2BGR     = 8
    GRAY2RGB     = GRAY2BGR
    GRAY2BGRA    = 9
    GRAY2RGBA    = GRAY2BGRA
    BGRA2GRAY    = 10
    RGBA2GRAY    = 11

  end

  def undistort( src, camera, coeffs, newcamera = nil )
    case coeffs
    when Array, Vector
      coeffs = VecNd.new( coeffs )
    end

    case coeffs
    when Vec4d
      if newcamera
        undistort4d_newcam( src, camera, coeffs, newcamera )
      else
        undistort4d( src, camera, coeffs )
      end
    else
      raise "I don't know how to treat #{coeffs.inspect} as a set of undistort coefficients"
    end
  end

  module Interpolation
    NEAREST = 0
    LINEAR = 1
    CUBIC = 2
    AREA = 3
    LANCZOS4 = 4

    WARP_FILL_OUTLIERS   = 8
    WARP_INVERSE_MAP     = 16
  end

  module BorderMode
    CONSTANT    = 0
    REPLICATE   = 1
    REFLECT     = 2
  end

  def warp_perspective_extents( src, m, flags = nil, borderMode = nil )
    corners = [ [0,0], [src.size.width, 0], [0, src.size.height], [src.size.width, src.size.height]].map { |pt|
      mapped = m * Vec3d.new( pt[0], pt[1], 1 )
      [ mapped[0]/mapped[2], mapped[1]/mapped[2] ]
    }
    xs,ys = corners.transpose

    width = xs.max - xs.min
    height = ys.max - ys.min

    affine = Mat.rows [[1,0,-xs.min],[0,1,-ys.min],[0,0,1]]
    warp = affine * m

    args = [ src, warp, Size.new( width, height ) ]
    args << flags if flags
    args << borderMode if borderMode

    [warp_perspective(*args), warp]
  end
  module_function :warp_perspective_extents

end
