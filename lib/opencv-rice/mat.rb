

module CVRice

  class Mat
    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end
  end

end
