
require 'bundler/setup'

class DirectorySet

  def initialize
    @dirs = {}

    @dirs[:top] = Pathname.new(__FILE__).parent.parent.expand_path

    paths = []; topdir.descend{ |p| paths << p }
    @dirs[:workspace] = paths.reverse.find { |p| p.basename.to_s =~ /workspace/ }

    @dirs[:gtest] = workspace.join("gtest")
    raise "Couldn't find gtest" unless @dirs[:gtest].directory?

    @dirs[:gem] = Pathname.new( `rvm gemdir`.chomp )
    raise "Couldn't find gemdir" unless @dirs[:gem].directory?

    @dirs[:rice] = gem_path( "rice" ).join('ruby','lib')
    raise "Couldn't find the Rice source files \"%s\"" % @dirs[:rice] unless @dirs[:rice]
  end

  def gem_path( gem )
    Pathname.new(Bundler.setup.gems[gem].first.bin_dir).parent
  end

  def dir( a )
    @dirs[a]
  end

  def [](a)
    @dirs[a]
  end

  # Convenience macros
  def topdir; dir( :top ); end
  def top; dir(:top); end
  def workspace; dir( :workspace ); end

  def ruby_cflags
    [ "-I#{rbconfig_dir('rubyhdrdir')}",
      "-I#{rbconfig_dir('rubyarchhdrdir')}" ]
  end

  def ruby_ldflags
    [ rbconfig('LIBRUBYARG') ]
  end

  def rbconfig(a) 
    RbConfig::CONFIG[a]
  end

  def rbconfig_dir( a )
    Pathname.new( rbconfig a )
  end

#  def set_env_paths
#    ENV['TOP_DIR'] = topdir.to_s
#    ENV['GTEST_DIR'] = gtest.to_s
#    ENV['RICE_DIR'] = dir(:rice).to_s
#    ENV['RB_LIB_ARGS'] = rbconfig('LIBRUBYARG')
#    ENV['RB_INCLUDE_ARGS'] = [ "-I" + rbconfig_dir('rubyhdrdir').join("ruby").to_s,
#                               "-I" + rbconfig_dir('rubyarchhdrdir').join("ruby").to_s ].join(' ')
#
#    # TODO:  How to get ruby libdir automatically?
#    ENV['LD_LIBRARY_PATH'] = [ rbconfig('rubylibdir') + "/lib",
#                               topdir.join("lib") ].join(':')
#  end
end

def dirs
  @dirs ||= DirectorySet.new
end

dirs


