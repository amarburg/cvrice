
module CVRice

  class Point < Point2d
    def self.new(*args)
      Point2d.new *args
    end
  end

  class Point2f
    def to_Vector( homogeneous = true )
      Vector[ x, y, 1.0 ]
    end
  end

  class Point2d

    class <<self

      # TODO:  How to "templatize" this so I can replicate it for Point2f
      # with DRY
      #
      alias_method :new_c, :new
      def new( *args )
        case args.first
        when Point2d, Point2f, Point2i, Point
          Point2d.new args.first.x, args.first.y
        when Numeric
          case args.length
          when 2
            new_c args[0], args[1]
          when 3
            new_c args[0].to_f/args[2], args[1].to_f/args[2]
          else
            raise "Can't make a Point2d from #{args.length} values"
          end
        when Array
          Point2d.new *(args.first)
        when Matrix, Vector, Mat
          Point2d.new args.first.to_a.flatten(1)
        else
          raise "Don't know how to make a Point2d from a #{args.first.class}: #{ args.map { |x| x.inspect }.join(',')}"
        end
      end

    end

    def homogeneous
      Vec3d.new x,y,1
    end

    def to_Vector( homogeneous = true )
      Vector[ x, y, 1.0 ]
    end
  end

end
