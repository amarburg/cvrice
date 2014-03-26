
require "opencv-rice"

require "minitest/autorun"

require_relative "common"

class TestMat < Minitest::Test
  include CVRice

  def test_mat
    m = Mat.new
    save_image "/tmp/foo.jpg", m
  end

end
