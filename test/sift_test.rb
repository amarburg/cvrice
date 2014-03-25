
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

    assert kps.length > 0
    assert_kind_of Keypoint, kps.first
  end

  def test_describe
    sift = SIFT.new
    kps, desc = sift.describe( img )

    assert kps.length > 0
    assert_kind_of Keypoint, kps.first
    assert_equal kps.length,            desc.rows
    assert_equal sift.descriptor_size,  desc.cols
  end

end
