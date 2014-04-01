

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

    def to_a
      arr = rows.times.map { |i|
        cols.times.map { |j|
          at_d(i,j)
        }
      }

      arr.flatten!(1) if rows == 1 or cols == 1

      arr 
    end

    def to_Matrix
      Matrix.rows to_a
    end

    def to_Vector
      raise "Mat is not a vector" unless rows == 1 or cols == 1
      Vector[ *(to_a.flatten(1)) ]
    end

    def [](a, b=0)
      at_d(r,c)
    end


    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end
  end
end
