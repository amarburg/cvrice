
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



class TestPose < Minitest::Test
  include CVRice

  def pose_tests( pose )
    assert_instance_of CVRice::Pose, pose

    [ pose.rvec, pose.tvec ].each { |vec|
      assert_instance_of Mat, vec
      assert_equal 3, vec.rows
      assert_equal 1, vec.cols
    }

    rot = pose.rotation_matrix
    assert_instance_of Mat, rot
    assert_equal 3, rot.rows
    assert_equal 3, rot.cols

    total = pose.total
    assert_instance_of Mat, total
    assert_equal 4, total.rows
    assert_equal 4, total.cols
  end

  def test_initialise_rotation_matrix
    pose = Pose.new( Mat.identity(3), Mat.columns([ [0,0,0] ] ) )
    pose_tests( pose )
  end

  def test_initialise_rvec
    pose = Pose.new( Mat.columns([ [0,0,0] ]), Mat.columns([ [0,0,0] ] ) )
    pose_tests( pose )
  end
end


