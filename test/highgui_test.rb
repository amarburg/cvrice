
require "opencv-rice"

require "minitest/autorun"

require_relative "common"

class TestHighgui < Minitest::Test
  include CVRice

  def test_load_image
    img = load_image test_image

    assert_kind_of Mat, img

    save_test_image "/tmp/foo.jpg", img
  end

end
