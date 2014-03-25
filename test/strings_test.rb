
require "opencv-rice"

require "minitest/autorun"

class TestHighgui < Minitest::Test
  include CVRice

  def test_strings
    baz test_image
    foo test_image
    bar test_image
  end

end


