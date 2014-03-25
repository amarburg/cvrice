
require "rake/clean"

CLEAN << FileList.new( "ext/**/Rakefile" )
CLEAN << FileList.new( "ext/**/*.so" )
CLEAN << FileList.new( "ext/**/*.o" )

CLEAN << FileList.new( "lib/*.so" )

CLEAN.include FileList.new( "test_c/*.o" )
CLEAN.include "test_c/test_app"


