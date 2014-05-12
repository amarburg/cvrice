
require "opencv-rice"

require "minitest/autorun"

class TestDMatch < Minitest::Test
    include CVRice

    def test_dmatch
      dm = DMatch.new  4,5,1e3

      assert_equal 4, dm.queryIdx
      assert_equal 5, dm.trainIdx
      assert_in_delta 1e3, dm.distance, 1e6
    end

end

class TestDMatchVector < Minitest::Test
  include CVRice

  def test_takes_a_dmatch_vector
    takes_a_dmatch_vector []
  end

  def test_takes_a_dmatch_vector_ref
    takes_a_dmatch_vector_ref []
  end

  def test_returns_a_dmatch_vector
    assert_kind_of Array, returns_a_dmatch_vector

    takes_a_dmatch_vector returns_a_dmatch_vector
  end
end
