
require "rake/clean"

CLEAN.include FileList.new( "ext/**/Rakefile" )
CLEAN.include FileList.new( "ext/**/*.so" )
CLEAN.include FileList.new( "ext/**/*.o" )

CLEAN.include FileList.new( "lib/*.so" )

CLEAN.include FileList.new( "test_c/*.o" )
CLEAN.include "test_c/test_app"


