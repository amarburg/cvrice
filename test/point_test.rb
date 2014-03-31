
require "opencv-rice"

require "minitest/autorun"


module TestPointCommon
  def test_constructor
    pt = point_klass.new

    assert_equal 0, pt.x
    assert_equal 0, pt.y
  end
end

class TestPoint2i < Minitest::Test
  include CVRice
  include TestPointCommon

  def point_klass; Point2i; end
end

class TestPoint2f < Minitest::Test
  include CVRice
  include TestPointCommon

  def point_klass; Point2f; end

  def test_constructor
    pt = point_klass.new( 1.1, 2.2 )
    assert_in_delta 1.1, pt.x, 1e-3
    assert_in_delta 2.2, pt.y, 1e-3
  end

end

class TestPoint2d < Minitest::Test
  include CVRice
  include TestPointCommon

  def point_klass; Point2d; end

  def test_constructor
    pt = point_klass.new( 1.1, 2.2 )
    assert_in_delta 1.1, pt.x, 1e-3
    assert_in_delta 2.2, pt.y, 1e-3
  end

end
