
require 'opencv-rice'

require 'minitest/autorun'
require_relative 'common'

class TestImgproc < Minitest::Test
  include CVRice

  def test_cvt_color
    img = load_image test_image

    assert_equal 3, img.channels
    assert_equal 0, img.depth

    grey = cvtcolor( img, Convert::BGR2GRAY )

    assert_equal 1, grey.channels
    assert_equal img.depth, grey.depth
    assert_equal img.size, grey.size
  end

end


