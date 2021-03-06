
## Additional steps because I'm using my mkrf from github,
#  not the Rubygems version
#ENV['DEBUG'] = '1'
#require 'rubygems'
#puts `gem env`
#p $LOAD_PATH
#
#require 'bundler'
#p Bundler.bundle_path
#
###  This is wrong...
#Bundler::Installer.install( Bundler.root, Bundler.definition )
#Bundler.setup(:default)
#
#puts `gem env`
#p $LOAD_PATH
require 'mkrf'
require_relative '../../tasks/directories'

sources = %w( opencv_rice.cpp
              core/*.cpp
              highgui/*.cpp
              imgproc/*.cpp
              calib3d/*.cpp
              nonfree/nonfree.cpp
              nonfree/sift.cpp )

Mkrf::Generator.new( 'libopencv_rice', sources, compiler: "g++" ) do |gen|
  gen.parallelize!

  # TODO.  Shouldn't be fixed paths...
  #   (need to make "mkrf-rice" to correspond to "mkmf-rice"

  gen.logger.level = Logger::DEBUG

  #gen.include_header  "rice/Class.hpp", '/home/aaron/.rvm/gems/ruby-2.0.0-p195/gems/rice-1.5.3/ruby/lib/include' 
  #gen.include_library "stdc++", "", "/usr/lib/x86_64-linux-gnu/"

  # The standard automatic library detection mechanism isn't well suited to
  # shared libraries of C++ code, so specify libraries manually for now
  #
  gen.cflags = %W( -Wall -ggdb -O0 -fPIC
                  -I#{dirs[:rice].join('include')} ).join(' ')

  # n.b.  Libraries should be specified after the object files.  
  # This 'objects' syntax causes mkrf to place this text after 
  # the list of objects on the linker command line
  # (though before the other libs)
  #
  gen.objects << %W( -L#{dirs[:rice].join('lib')} -lrice -lstdc++
                 -lopencv_core -lopencv_features2d 
                 -lopencv_calib3d
                 -lopencv_highgui -lopencv_nonfree).join(' ')
end
