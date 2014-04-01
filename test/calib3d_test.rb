
require "opencv-rice"

require "minitest/autorun"

class TestCalib3d < Minitest::Test

    def setup
      @rows = 10
      # Must ensure points are non-colinear
      @m1 = Array.new(@rows) { |i| [ Math::sin(i), Math::cos(i) ] }
      @m2 = Array.new(@rows) { |i| [ Math::sin(i), Math::cos(i)+1 ] }
    end

    def test_find_homography
      h = CVRice::findHomography( @m1, @m2 )

      assert_equal 3, h.rows
      assert_equal 3, h.cols
      #rows.times.each do |i|
      #  assert_in_delta 45.0, err.at_d( i )
      #end
    end

    def test_find_homography_ransac
      h = CVRice::findHomography( @m1, @m2, CVRice::RANSAC )
      assert_equal 3, h.rows
      assert_equal 3, h.cols
    end

    def test_find_homography_lmeds
      h = CVRice::findHomography( @m1, @m2, CVRice::LMEDS )
      assert_equal 3, h.rows
      assert_equal 3, h.cols
    end
end
