

module CVRice

  class Mat

    # Emulate the overloaded constructor in Ruby
    class << self
      alias :new_c :new

      def new( *args )
        case args.length
        when 0
          Mat.new_c
        when 1
          arg = args.pop
          case arg
          when Array, Matrix
            CVRice::from_ruby arg
          when CVRice::Mat
            CVRice::Mat::copy_constructor arg
          end
        end
      end

      def rows( arr )
        Mat.new arr
      end
    end

    alias_method :svd_c, :svd
    def svd( opts = {} )
      flags = 0
      flags += 1 if opts[:modify_a]
      flags += 2 if opts[:no_uv]
      flags += 4 if opts[:full_uv]

      w = Mat.new
      u = Mat.new
      vt = Mat.new

      svd_c( w,u,vt, flags )

      [u,w,vt]
    end


    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end
  end
end
