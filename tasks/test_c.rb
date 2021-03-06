## C++-language testing

require_relative "directories"

desc "Run the C/C++ language test suite."

task :test_c => "test_c:run"
namespace :test_c do

  test_app = "test_c/test_app"
  srcs     = Dir.glob('test_c/*.cpp')
  objs     = srcs.map { |f| Pathname.new(f).sub_ext('.o').to_s }

  cpp      = 'g++'
  cflags   = dev_dirs.ruby_cflags + 
             %W( -ggdb
                 -I#{dev_dirs.topdir.join('ext')}
                 -I#{dev_dirs[:rice].join('include')}
                 -I#{dev_dirs[:gtest]}/include )
  ldflags  = cflags
  libs  = dev_dirs.ruby_ldflags + 
          %W( -L#{dev_dirs[:gtest]}/build -lgtest
              -lopencv_core -lopencv_calib3d
              -lpthread
              -Llib -lopencv_rice
              -Wl,-rpath=lib )

  file test_app => [:ext] + objs do
    sh [ cpp,  *ldflags, 
         '-o', test_app, *objs, *libs ].join(' ')
  end

  srcs.each { |src|
    obj = Pathname.new(src).sub_ext('.o').to_s
    file obj => src do
      sh [ cpp, '-c', *cflags, '-o', obj, src ].join(' ')
    end
  }

  task :run => test_app do
    sh test_app
  end

  task :gdb => test_app do
    sh "gdb #{test_app}"
  end

  clean_files = %w( test_c/*.o
        test_c/test_app )

  task :clean do
    clean_files.each { |path|
      Dir.glob( path ).each { |file|
        File.unlink( file )
      }
    }
  end
end

