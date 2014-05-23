
require "opencv-rice"

require "minitest/autorun"

class TestKeyPoint < Minitest::Test
  include CVRice

  def test_default_constructor
    kp = KeyPoint.new

    assert_equal 0, kp.x
    assert_equal 0, kp.y
  end

  def setup
    @x = -5.5
    @y = 2.3
    @size = 12.0
    @angle = -0.4
    @response = 2.3e4
    @octave = 2

    @kp = KeyPoint.new( @x, @y, @size, @angle, @response, @octave )
  end

  def epsilon; 1e-2; end

  def test_constructor
    kp = @kp

    assert_in_delta @x, kp.x, epsilon
    assert_in_delta @y, kp.y, epsilon
    assert_in_delta @size, kp.size, epsilon
    assert_in_delta @angle, kp.angle, epsilon
    assert_in_delta @response, kp.response, epsilon
    assert_in_delta @octave, kp.octave, epsilon
  end

  def test_point_accessors
    kp = @kp

    assert_instance_of Point2f, kp.pt
    assert_in_delta @x, kp.pt.x, epsilon
    assert_in_delta @y, kp.pt.y, epsilon
    assert_in_delta @x, kp.x, epsilon
    assert_in_delta @y, kp.y, epsilon

    kp.pt = Point2f.new 3.0, 4.0
    assert_in_delta 3.0, kp.pt.x, epsilon
    assert_in_delta 4.0, kp.pt.y, epsilon

    kp.x = 6.0
    assert_in_delta 6.0, kp.pt.x, epsilon
    assert_in_delta 4.0, kp.pt.y, epsilon

    kp.y = 8.0
    assert_in_delta 6.0, kp.pt.x, epsilon
    assert_in_delta 8.0, kp.pt.y, epsilon
    
  end



end
