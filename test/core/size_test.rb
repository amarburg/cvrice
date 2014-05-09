
require "opencv-rice"

require "minitest/autorun"

class TestSize2i < Minitest::Test
  include CVRice

  def test_implicit_cast
    takes_a_size2f Size2i.new
    takes_a_size2f Size2i.new
  end

end

class TestSize2f < Minitest::Test
  include CVRice

  def test_implicit_cast
    takes_a_size2i Size2f.new
    takes_a_size2f Size2f.new
  end
end


