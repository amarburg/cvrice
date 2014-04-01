

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


    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end
  end
end
