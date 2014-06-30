
require "opencv-rice"

require "minitest/autorun"
require_relative '../common'

class TestScalar < Minitest::Test
  include CVRice

  EPSILON = 1e-6

  def test_null_constructor
    s = Scalar.new
    4.times.each { |i| assert_in_delta  0, s[i], EPSILON }
  end

  def test_constructor
    s = Scalar.new( 2.0, 4.0 )
    assert_in_delta 2.0, s[0], EPSILON
    assert_in_delta 4.0, s[1], EPSILON
    assert_in_delta 0.0, s[2], EPSILON
    assert_in_delta 0.0, s[3], EPSILON
  end


end

