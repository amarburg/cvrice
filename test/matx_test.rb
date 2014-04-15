
require 'minitest/autorun'
require 'opencv-rice'

class TestMatx22d < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx22d Matrix.rows [ [1,3],[4,6] ]
  end

end

class TestMatx22f < Minitest::Test

  include CVRice

  def test_construct_from_matrix
    takes_a_matx22f Matrix.rows [ [1,2],[4,5] ]
  end

  end

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
