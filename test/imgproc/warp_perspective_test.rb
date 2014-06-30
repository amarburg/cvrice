
require 'opencv-rice'

require 'minitest/autorun'
require_relative '../common'

class TestWarpPerspective < Minitest::Test
  include CVRice

  def warp
    Mat.rows [[0.26,0,0],[0,1.5,0],[0,0,1]]
  end

  def test_warp_perspective
    img = load_image test_image

    warped = warp_perspective( img, warp, img.size )

    assert_equal img.depth, warped.depth
    assert_equal img.size, warped.size

    save_test_image "/tmp/warped.jpg", warped
  end

  def test_warp_perspective_extents
    img = load_image test_image

    warped = warp_perspective_extents( img, warp )

    assert_equal img.depth, warped.depth

    save_test_image "/tmp/warped_extents.jpg", warped
  end


end


