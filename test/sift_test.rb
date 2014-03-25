
require "opencv-rice"

require "minitest/autorun"

class TestSIFT < Minitest::Test
  include CVRice


  def test_default_constructor
    sift = SIFT.new

    assert_equal 128, sift.descriptor_size
  end

end
