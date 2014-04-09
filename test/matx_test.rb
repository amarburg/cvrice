
require 'minitest/autorun'
require 'opencv-rice'

class TestMatx33d < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx33d Matrix.rows [ [1,2,3],[4,5,6],[7,8,9]]
  end

end

class TestMatx33f < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx33f Matrix.rows [ [1,2,3],[4,5,6],[7,8,9]]
  end

end
