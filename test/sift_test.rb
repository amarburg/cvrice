
require "opencv-rice"

require "minitest/autorun"

require_relative "common"

class TestSIFT < Minitest::Test
  include CVRice

  def img
    @img ||= load_image test_image
  end

  def test_default_constructor
    sift = SIFT.new

    assert_equal 128, sift.descriptor_size
  end

  def test_detect
    sift = SIFT.new
    kps = sift.detect( img )

    puts kps.length
    p kps.first

  end

end
