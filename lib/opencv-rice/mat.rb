
require 'matrix'

module CVRice

  class Mat
    include Enumerable

    # TODO:  Think of a better way to do this
    CV_8U = 0
    CV_8S = 1
    CV_16U = 2
    CV_16S = 3
    CV_32S = 4
    CV_32F = 5
    CV_64F = 6

    # Emulate the overloaded constructor in Ruby
    class << self
      def new( *args )
        case args.length
        when 0
          a = allocate
          a.send( :initialize )
          a
        when 1
          arg = args.pop
          case arg
          when Array, Matrix
            Mat::from_ruby arg
          when Vector
            Mat::columns [ arg.to_a ]
          when Matx22f, Matx22d, Matx33f, Matx33d
            arg.to_mat
          when CVRice::Mat
            Mat::copy_constructor arg
          else 
            raise "Don't know how to make a Mat from a #{args.first.class}"
          end
        when 2..3
          if Numeric === args[0] and Numeric === args[1]
            a=allocate
            a.send( :initialize,  *(args.first(3)) )
            a
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

    def self.arithmatic_operator( operator, mat_function, const_function, msg = nil )

      msg ||= '"Don\'t know how to %s a #{b.class} from a CVRice::Mat"' % operator

      self.send :define_method, operator, Proc.new { |b|
        case b
        when Vector,Matrix,Mat
          send( mat_function, b )
        when Vec3d
          send( mat_function, b.to_mat )
        when Numeric
          send( const_function, b )
        else
          raise msg % [b.class] 
        end
      }
    end

    arithmatic_operator :+, :add_mat, :add_const, '"Don\'t know how to add a %s to a CVRice::Mat"'
    arithmatic_operator :-, :subtract_mat, :subtract_const, '"Dont\'t know how to subtract a %s from a CVRice::Mat"'
    arithmatic_operator :*, :mult_mat, :mult_const, '"Dont\'t know how to multiply a CVRice::Mat by a %s"'

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
      Matx33d::from_ruby to_a
    end

    def to_matx33f
      raise "This mat isn't 3x3, can't convert to matx33f" unless rows ==3 and cols == 3
      Matx33f::from_ruby to_a
    end

    def to_matx22d
      raise "This mat isn't 2x2, can't convert to matx22d" unless rows ==2 and cols == 2
      Matx22d::from_ruby to_a
    end

    def to_matx22f
      raise "This mat isn't 2x2, can't convert to matx22f" unless rows ==2 and cols == 2
      Matx22f::from_ruby to_a
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
                  st = opts
                  opts = {}
                  st
                when Hash
                  opts[:caption]
                end

      puts "#{caption}  (%dx%d)= " % [rows,cols] if caption
      rows.times { |r|
        puts cols.times.map { |c| 
          format = case opts[:format]
                   when :exp
                     "%-5.2e" 
                   when nil
                     "%.5f"
                   else
                     opts[:format]
                   end
          format % at_d(r,c)
        }.join(' ')
      }
    end
  end
end
