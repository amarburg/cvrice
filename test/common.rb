
require 'pathname'

def test_image
  path = Pathname.new("test/images/img1.jpg")
  raise "Can't find test image" unless path.readable?
  path.to_s
end
