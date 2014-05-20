

module CVRice

  class Size < Size2i; end

  class Size2i
    def to_a
      [width,height]
    end
  end
end
