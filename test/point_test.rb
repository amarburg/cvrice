
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
    [ point_klass.new( 1.1, 2.2 ),
      point_klass.new( Matrix.rows [ [1.1, 2.2] ] ),
      point_klass.new( [1.1, 2.2] ),
      point_klass.new( Vector[ 1.1, 2.2 ] ),
      point_klass.new( Point2d.new( 1.1, 2.2 )),
      point_klass.new( Point2f.new( 1.1, 2.2 )),
      point_klass.new( 2.2, 4.4, 2.0 ) ].each { |pt|
        assert_in_delta 1.1, pt.x, 1e-3
        assert_in_delta 2.2, pt.y, 1e-3
      }
  end

  def test_subtract
    a = Point2d.new( 1.0, 2.0 )
    b = Point2d.new( 0.5, 0.75 )
    c = a-b

    assert_in_delta 0.5, c.x, 1e-2
    assert_in_delta 1.25, c.y, 1e-2
  end

  def test_homogeneous
    a = Point2d.new( 3.3, 4.4 )
    v = a.homogeneous

    assert_instance_of CVRice::Vec3d, v
    assert_in_delta 3.3, v[0], 1e-2
    assert_in_delta 4.4, v[1], 1e-2
  end

  def test_accessors
    a = Point2d.new( 3.3, 4.4 )
    assert_in_delta 3.3, a.x, 1e-2
    assert_in_delta 4.4, a.y, 1e-2

    assert_in_delta 5.5, (a.x = 5.5), 1e-3
    assert_in_delta -1e3, (a.y = -1e3), 1e-3
    assert_in_delta 5.5, a.x, 1e-2
    assert_in_delta -1e3, a.y, 1e-2
  end


  def test_dot
    a = Point2d.new( 3.3, 4.4 )
    b = Point2d.new( 1.0, 2.0 )

    ans = 3.3*1.0 + 4.4*2.0
    assert_in_delta ans, a.dot(b), 1e-6
    assert_in_delta ans, b.dot(a), 1e-6
  end

end
