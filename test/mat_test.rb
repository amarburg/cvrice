

require 'minitest/autorun'
require 'opencv-rice'
require 'matrix'

require_relative "common"

class TestMat < Minitest::Test
  include CVRice

  def arr
    [ [1.5,2,3.2], [-4.4,5,6] ]
  end

  def assert_mat_equals_arr( mat, which = "")
    assert_instance_of CVRice::Mat, mat
    assert_equal arr.length, mat.rows
    assert_equal arr.first.length, mat.cols

    arr.length.times { |r|
      arr.first.length.times { |c|
        #puts "%s: %d, %d, %.1f, %.1f" % [which, r,c,arr[r][c], mat.at_f(r,c)]
        assert_in_delta arr[r][c], mat.at_d(r,c), 1e-2
      }
    }
  end

  def test_mat
    m = Mat.new
    save_image "/tmp/foo.jpg", m
  end

  def test_constructors
    assert_mat_equals_arr Mat.rows( arr ), "Mat.rows arr"
    assert_mat_equals_arr Mat.new( arr ), "Mat.new arr"
    assert_mat_equals_arr Mat.new( Matrix.rows( arr )), "Mat.new matrix"
    assert_mat_equals_arr Mat.new( Mat.new arr ), "Mat.new Mat.new arr"
  end

  def test_svd
    m = Mat.new [ [1,2,3],[4,5,6],[7,8,9] ]
    u,d,vt = m.svd

    p u
    p d
    p vt
  end

end


class TestMatx33d < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx33d Matrix.rows [ [1,2,3],[4,5,6],[7,8,9]]
  end
end
