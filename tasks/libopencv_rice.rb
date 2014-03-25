
require "mkrf/rakehelper"
require "rake/file_list"

## Extension library...
setup_extension('opencv_rice', 'libopencv_rice')

desc "Build all extension libraries"
task :ext => :libopencv_rice 

file "ext/opencv_rice/libopencv_rice.so" => 
FileList[ "ext/opencv_rice/mkrf_conf.rb",
          "ext/opencv_rice/opencv_rice/*.h",
          "ext/opencv_rice/opencv_rice/*.cpp",
          "ext/opencv_rice/opencv_rice/*/*.h",
          "ext/opencv_rice/opencv_rice/*/*.cpp" ]




