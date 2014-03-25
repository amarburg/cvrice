
require "opencv-rice"

require "minitest/autorun"

require_relative "common"

class TestHighgui < Minitest::Test
  include CVRice

  def test_load_image
    baz test_image
    foo test_image
    bar test_image


    img = load_image test_image

    assert_kind_of Mat, img


    save_image "/tmp/foo.jpg", img
  end



end
