
module CVRice

  class Point < Point2d
    def self.new(*args)
      Point2d.new( *args )
    end
  end

  module PointCommon

    def self.included( klass )
      klass.extend ClassMethods
    end

    def homogeneous
      vector_class.new x,y,1
    end

    def to_Vector( homogeneous = true )
      Vector[ x, y, 1.0 ]
    end

    def to_a( homogeneous = true )
      if homogeneous
        [ x, y, 1.0 ]
      else
        [ x, y ]
      end
    end

    module ClassMethods

      def new( *args )
        case args.first
        when nil
          new_c
        when Point2d, Point2f, Point2i, Point
          point_class.new args.first.x, args.first.y
        when Vec2d, Vec3d
          vec = args.first
          point_class.new *vec
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
          point_class.new( *(args.first) )
        when Matrix, Vector, Mat
          point_class.new args.first.to_a.flatten(1)
        else
          raise "Don't know how to make a Point2d from a #{args.first.class}: #{ args.map { |x| x.inspect }.join(',')}"
        end
      end
    end

  end


  class Point2f

    class <<self
      alias_method :new_c, :new

      # TODO.  This is somewhat ugly.  Can I get this through metaprogamming?
      def point_class; Point2f; end
    end

    include PointCommon

    # TODO.  Vec3f doesn't exist yet...
    def vector_class; Vec3d; end
  end

  class Point2d

    class <<self
      alias_method :new_c, :new
      # TODO.  This is somewhat ugly.  Can I get this through metaprogamming?
      def point_class; Point2d; end
    end

    include PointCommon

    def vector_class; Vec3d; end
  end

end
