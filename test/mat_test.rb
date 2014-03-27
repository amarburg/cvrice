

require 'minitest/autorun'
require 'opencv-rice'
require 'matrix'

require_relative "common"

class TestMat < Minitest::Test
  include CVRice

  def test_mat
    m = Mat.new
    save_image "/tmp/foo.jpg", m
  end

  def test_conversion_from_array
    a = Mat.rows [ [1,2,3], [4,5,6] ]

    assert_equal 2, a.rows
    assert_equal 3, a.cols
  end

  def test_conversion_from_matrix
    arr = [ [1,2,3], [4,5,6] ]
    matrix = Matrix.rows arr
    mat = Mat.new matrix

      assert_equal 2, mat.rows
    assert_equal 3, mat.cols

    takes_a_mat matrix
    takes_a_mat Mat.new
    takes_a_mat arr
  end

end
