

require 'minitest/autorun'
require 'opencv-rice'
require 'matrix'

require_relative "common"

class TestMat < Minitest::Test
  parallelize_me!
  include CVRice

  def arr
    [ [1.5,2,3.2], [-4.4,5,6] ]
  end

  def test_1d_readers
    arr = [[0,1,2,3,4,5,6,7,8]].transpose
    mat = Mat.new arr
    assert_instance_of CVRice::Mat, mat
    assert_equal 9, mat.rows
    assert_equal 1, mat.cols

    9.times { |r|
      assert_in_delta arr[r][0], mat[r], 1e-2, "For (r=%d)" % r
    }
  end
  
  def assert_mat_equals_arr( mat, which = "", test_array = arr)
    assert_instance_of CVRice::Mat, mat
    assert_equal test_array.length, mat.rows
    assert_equal test_array.first.length, mat.cols

    test_array.length.times { |r|
      test_array.first.length.times { |c|
        #puts "%s: %d, %d, %.1f, %.1f" % [which, r,c,arr[r][c], mat.at_f(r,c)]
        assert_in_delta test_array[r][c], mat.at_d(r,c), 1e-2
        assert_in_delta test_array[r][c], mat[r,c], 1e-2
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

    mat = Mat.new( 3,3 )
    assert_equal 3, mat.rows
    assert_equal 3, mat.cols
    assert_equal Mat::CV_64F, mat.type

    mat = Mat.new( 4,4,Mat::CV_32F )
    assert_equal 4, mat.rows
    assert_equal 4, mat.cols
    assert_equal Mat::CV_32F, mat.type
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

  def test_to_matx33d
    mat = Mat.identity( 3 )
    matx = mat.to_matx33d

    assert_instance_of Matx33d, matx
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

  def test_add
    a = Mat.new [ [0.0, 0.5], [0.5, 1.0] ]
   b = a.transpose
   d = a+b

   assert_instance_of Mat, d
   assert_equal 2, d.rows
   assert_equal 2, d.cols
   2.times.each { |r| 2.times.each { |c| assert_in_delta (r+c), d[r,c],1e-2 }}
  end

  def test_subtract
    a = Mat.new [ [1.0, 2.0], [2.0, 1.0] ]
   b = a.transpose

   d = a-b

   assert_instance_of Mat, d
   assert_equal 2, d.rows
   assert_equal 2, d.cols
   2.times.each { |r| 2.times.each { |c| assert_in_delta 0, d[r,c],1e-2 }}
  end

  def test_map
    a = Mat.new [ [ 0.0, 2.0 ], [2.0, 4.0] ]
    d = a.map { |x| x/2 }

    assert_instance_of Mat, d
    assert_equal 2, d.rows
    assert_equal 2, d.cols
    2.times.each { |r| 2.times.each { |c| assert_in_delta (r+c), d[r,c],1e-2 }}
  end



  def test_eye
    m = Mat.identity( 3 )
    assert_equal 3, m.rows
    assert_equal 3, m.cols
    assert_equal Mat::CV_64F, m.type

    3.times.each { |r|
      3.times.each { |c|
        if r==c
          assert_equal 1, m[r,c]
        else
          assert_equal 0, m[r,c]
        end
      }
    }
  end

end


