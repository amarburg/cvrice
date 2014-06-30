
require 'opencv-rice'

require 'minitest/autorun'
require_relative '../common'

class TestUndistort < Minitest::Test
  include CVRice

  def sample_4d_distortions
    Vec4d.new( -0.10909780395014858, 0.098664366954064761, 0.0054612207540125053, 0.0019408449964044546 )
  end

  def test_undistort
    img = load_image test_image

    undistorted = undistort( img, sample_camera_matrix, sample_4d_distortions )

    assert_equal img.depth, undistorted.depth
    assert_equal img.size, undistorted.size

    save_test_image "/tmp/undistorted.jpg", undistorted
  end

end


