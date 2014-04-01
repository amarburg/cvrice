
require "opencv-rice"

require "minitest/autorun"

class TestReproj < Minitest::Test
    include CVRice

    def test_dmatch
      rows = 10
      m1 = Array.new(rows) { |i| [ i-5, 0 ] }
      m2 = Array.new(rows) { |i| [ i+1, 3 ] }
      h = Matrix.identity(3)

      err = computeHomographyReprojError( m1, m2, h )

      assert_equal 10, err.rows
      assert_equal 1, err.cols
      rows.times.each do |i|
        assert_in_delta 45.0, err.at_d( i )
      end
    end

end
