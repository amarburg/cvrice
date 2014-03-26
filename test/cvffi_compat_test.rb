
require 'opencv-rice'
require 'opencv-ffi-wrappers'

require "minitest/autorun"

require_relative "common"

class TestCVFFICompat < Minitest::Test
  include CVRice

  def img
    @img ||= load_image test_image
  end

  def test_cvmat_to_mat
    cvmat = CVFFI::cvLoadImageM( test_image )
    mat = cvmat_to_mat  cvmat

    assert_instance_of Mat, mat
  end

  def test_save_cvmat
    cvmat = CVFFI::cvLoadImageM( test_image )

    save_image "/tmp/bar.jpg", cvmat_to_mat(cvmat)
  end
end


