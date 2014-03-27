

module CVRice

  class Mat

    # My version of an overloaded constructor
    class << self
      alias :new_c :new

      def new( *args )
        case args.length
        when 0
          Mat.new_c
        when 1
          case args.first
          when Matrix, Array
            CVRice::array_to_mat args.first.to_a
          end
        end
      end

      def rows( arr )
        CVRice::array_to_mat arr 
      end
    end


    def to_CvMat
      CVRice::mat_to_cvmat( self )
    end
  end

end
