
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
