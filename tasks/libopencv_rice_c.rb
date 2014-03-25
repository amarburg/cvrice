
require "mkrf/rakehelper"
require "rake/file_list"

## Extension library...
setup_extension('opencv_rice_c', 'libopencv_rice_c')

desc "Build all extension libraries"
task :ext => :libopencv_rice_c 

file "ext/opencv_rice_c/libopencv_rice_c.so" => 
      FileList[ "ext/opencv_rice_c/*.cpp", 
                "ext/opencv_rice_c/**/*.cpp" ]




