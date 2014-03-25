
desc "Run a console"
task :console do
  require 'irb'
  require 'irb/completion'
  require 'opencv-rice'
  ARGV.clear
  IRB.start
end
