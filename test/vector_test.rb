
require "opencv-rice"

require "minitest/autorun"

class TestVec2d < Minitest::Test
    include CVRice

    def test_empty_constructor
      v = Vec2d.new

      assert_in_delta 0, v[0], 1e-6
      assert_in_delta 0, v[1], 1e-6
    end

    def test_constructor
      v = Vec2d.new 5.24, Math::PI

      assert_in_delta 5.24,     v[0], 1e-6
      assert_in_delta Math::PI, v[1], 1e-6
    end
end

class TestVec3d < Minitest::Test
  include CVRice

  def test_to_a
    v = Vec3d.new 1.0, 2.0, 3.0
    a = v.to_a
    
    assert_instance_of Array, a
    assert_in_delta 1.0, a[0], 1e-2
    assert_in_delta 2.0, a[1], 1e-2
    assert_in_delta 3.0, a[2], 1e-2
  end

  def test_to_matx
    v = Vec3d.new 1.0, 2.0, 3.0
    m = v.to_mat

    assert_instance_of Mat, m
    assert_equal 3, m.rows
    assert_equal 1, m.cols
    3.times.each { |i|
      assert_in_delta i+1, m[i,0], 1e-2
    }
  end
end
