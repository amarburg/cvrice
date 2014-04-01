

require 'minitest/autorun'
require 'opencv-rice'
require 'matrix'

require_relative "common"

class TestMat < Minitest::Test
  include CVRice

  def arr
    [ [1.5,2,3.2], [-4.4,5,6] ]
  end

  def assert_mat_equals_arr( mat, which = "", test_array = arr)
    assert_instance_of CVRice::Mat, mat
    assert_equal test_array.length, mat.rows
    assert_equal test_array.first.length, mat.cols

    test_array.length.times { |r|
      test_array.first.length.times { |c|
        #puts "%s: %d, %d, %.1f, %.1f" % [which, r,c,arr[r][c], mat.at_f(r,c)]
        assert_in_delta test_array[r][c], mat.at_d(r,c), 1e-2
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

  def assert_arr_equals_arr( a, which = "" )
    assert_equal 2, a.length
    arr.length.times { |r|
      assert_equal 3, a[r].length

      arr[r].length.times { |c|
        assert_in_delta arr[r][c], a[r][c], 1e-2
      }
    }
  end

  def test_to_a
    mat = Mat.new( arr )
    a = mat.to_a
    assert_arr_equals_arr a, "to_a"
  end

  def test_to_Matrix
    mat = Mat.new( arr )
    m = mat.to_Matrix
    assert_arr_equals_arr m.to_a, "to_Matrix"
  end

  def test_set_d
    mat = Mat.new( arr )
    assert_mat_equals_arr mat, "test_set_d"
    mat.set_d( 0,0, 0.0 )
    mat.set_d( 1,2, 5.5 )

    # modify the template as well
    test_arr = arr
    test_arr[0][0] = 0.0
    test_arr[1][2] = 5.5
    assert_mat_equals_arr mat, "test_set_d", test_arr
  end

  def test_each
    mat = Mat.new [[0,1,2,3,4,5,6,7,8]]

    # As enumerator
    count = 0
    mat.each.with_index {  |x,i|
      assert_in_delta i, x, 1e-2
      count += 1
    }
    assert_equal 9, count

    # W/o enumerator
    count = 0
    mat.each {  |x|
      assert_in_delta count, x, 1e-2
      count += 1
    }
    assert_equal 9, count
  end

  def test_svd
    m = Mat.new [ [1,2,3],[4,5,6],[7,8,9] ]
    u,d,vt = m.svd

  end

end


class TestMatx33d < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx33d Matrix.rows [ [1,2,3],[4,5,6],[7,8,9]]
  end
end
