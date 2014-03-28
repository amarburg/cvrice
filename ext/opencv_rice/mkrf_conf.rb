
require 'mkrf'
require_relative '../../tasks/directories'

sources = %w( opencv_rice.cpp
              core/core.cpp
              core/mat.cpp
              core/dmatch.cpp
              core/keypoint.cpp
              core/cvffi_compat.cpp
              highgui/highgui.cpp
              nonfree/nonfree.cpp
              nonfree/sift.cpp )

Mkrf::Generator.new( 'libopencv_rice', sources, compiler: "g++" ) do |gen|
  # TODO.  Shouldn't be fixed paths...
  #   (need to make "mkrf-rice" to correspond to "mkmf-rice"

  gen.logger.level = Logger::DEBUG

  #gen.include_header  "rice/Class.hpp", '/home/aaron/.rvm/gems/ruby-2.0.0-p195/gems/rice-1.5.3/ruby/lib/include' 
  #gen.include_library "stdc++", "", "/usr/lib/x86_64-linux-gnu/"

  # The standard automatic library detection mechanism isn't well suited to
  # shared libraries of C++ code, so specify libraries manually for now
  #
  gen.cflags << [ '-ggdb', '-O0', '-fPIC',
                  "-I#{dirs.rice}/include",
                  "-I#{dirs.gemdir}/gems/ffi-1.9.3/ext" ].join(' ')

  # n.b.  Libraries should be specified after the object files.  
  # This 'objects' syntax causes mkrf to place this text after 
  # the list of objects on the linker command line
  # (though before the other libs)
  #
  gen.objects << %W( -L#{dirs.rice}/lib -lrice -lstdc++
                 -L#{dirs.ffi}/lib -lffi_c
                 -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_nonfree).join(' ')
end
