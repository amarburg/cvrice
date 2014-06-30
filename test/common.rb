
require 'pathname'
require 'opencv-rice'

def test_image
  path = Pathname.new("test/images/img1.jpg")
  raise "Can't find test image" unless path.readable?
  path.to_s
end

def sample_camera_matrix
  CVRice::Mat.rows [[1258.2167650323022, 0, 491.492055209643],
            [0, 1256.1306710569052, 344.12243211337216],
            [0, 0, 1]]
end

def save_test_image( fname, mat )
  if ENV['SAVE_TEST_IMAGES']
    save_image fname, mat
  end
end
