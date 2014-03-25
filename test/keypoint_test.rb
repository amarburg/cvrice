
require "opencv-rice"

require "minitest/autorun"

class TestKeypoint < Minitest::Test
  include CVRice

  def test_default_constructor
    kp = Keypoint.new

    assert_equal 0, kp.x
    assert_equal 0, kp.y
  end

  def test_constructor
    x = -5.5
    y = 2.3
    size = 12.0
    angle = -0.4
    response = 2.3e4
    octave = 2
    epsilon = 1e-2

    kp = Keypoint.new( x, y, size, angle, response, octave )

    assert_in_delta x, kp.x, epsilon
    assert_in_delta y, kp.y, epsilon
    assert_in_delta size, kp.size, epsilon
    assert_in_delta angle, kp.angle, epsilon
    assert_in_delta response, kp.response, epsilon
    assert_in_delta octave, kp.octave, epsilon
  end

end
