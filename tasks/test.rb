
require "rake/testtask"
require_relative "rake_gdb"

# Testing cruft
Rake::TestTask.new do |t|
  t.libs.push "lib"
  t.test_files = FileList['test/**/*_test.rb'] 
  t.verbose = true
end

task :test     => :ext
task :test_gdb => :ext

