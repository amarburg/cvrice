
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

    save_image "/tmp/grey.jpg", grey
  end

  def test_canny
    img = load_image test_image
    grey = cvtcolor( img, Convert::BGR2GRAY )
    edges = canny grey, 1.0, 2.0

    save_image "/tmp/canny.jpg", edges
  end

  def test_houghlines
    img = load_image test_image
    grey = cvtcolor( img, Convert::BGR2GRAY )
    edges = canny grey, 1.0, 2.0

    lines = houghlines edges, 2, Math::PI/20, 2
    lines.print('lines')
    puts lines.type
  end

end


