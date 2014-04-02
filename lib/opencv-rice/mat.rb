

module CVRice

  class Mat
    include Enumerable

    # TODO:  Think of a better way to do this
    CV_32F = 5
    CV_64F = 6

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
            Mat::from_ruby arg
          when Vector
            Mat::columns [ arg.to_a ]
          when CVRice::Mat
            Mat::copy_constructor arg
          else 
            raise "Don't know how to make a Mat from a #{args.first.class}"
          end
        when 2..3
          if Numeric === args[0] and Numeric === args[1]
            Mat.new_c *(args.first(3))
          end
        else
          raise "Don't know how to make a Mat from: %s" % args.map {|x| x.inspect}.join(', ')
        end
      end

      def rows( arr )
        Mat.new arr
      end

      def columns( arr )
        Mat.rows(arr.transpose)
      end

      def diagonal( *elems )
        Mat.new Matrix.diagonal(*elems)
      end

      def identity( r, c = r, type = CV_64F )
        Mat::eye( r, c, type )
      end
    end

    # For compatability with Matrix
    alias_method :row_count, :rows
    alias_method :column_count, :cols

    def inspect
      "Mat: %d x %d" % [rows,cols]
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

    def *(b)
      case b
      when Vector,Matrix,Mat
        mult_mat(b)
      when Vec3d
        mult_mat( b.to_mat )
      when Numeric
        mult_const(b)
      else
        raise "Don't know how to multiply a Matrix be a #{b.class}"
      end
    end

    def each
      if block_given?
        rows.times { |r|
          cols.times { |c|
            yield at_d(r,c)
          }
        }
      else
      raise "Enumerator form of Mat::each only makes sense if Matrix has 1 row or 1 column" unless rows == 1 or cols == 1
        # Assumed to be less efficient because the temporary Array is created...
        (to_a.flatten(1)).each
      end
    end

    def each_with_index
      if block_given?
        rows.times { |r|
          cols.times { |c|
            yield at_d(r,c),r,c
          }
        }
      else
        raise "Enumerator form of Mat::each_with_index doesn't exist (yet)..."
      end
    end

    def map
      if block_given?
        out = Mat.new rows, cols, type
        rows.times {|r| cols.times {|c|
          out.set_d( r, c, (yield at_d(r,c)) )
        } }
        out
      else
        raise "Enumerator for of Mat::map doesn't exist (yet)..."
      end
    end

    def row_vectors
      to_a.map! { |arr|
        Vector[ *arr ]
      }
    end

    # TODO:  Need this now, could be done many ways, each
    # better than this...
    def to_matx33d
      raise "This mat isn't 3x3, can't convert to matx33d" unless rows ==3 and cols == 3
      a = Matx33d::from_ruby to_a
    end

    def to_Matrix
      Matrix.rows to_a
    end

    def to_Vector
      raise "Mat is not a vector" unless rows == 1 or cols == 1
      Vector[ *(to_a.flatten(1)) ]
    end

    def [](r,c=0)
      at_d(r,c)
    end

    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end

    def print( opts = {} )
      caption = case opts
                when ::String
                  opts
                when Hash
                  opts[:caption]
                end

      puts "#{caption}  (%dx%d)= " % [rows,cols] if caption
      rows.times { |r|
        puts cols.times.map { |c| 
          "%.5f" % at_d(r,c)
        }.join(' ')
      }
    end
  end
end
