
desc "Run a console"
task :console => :ext do
  #require 'irb'
  #require 'irb/completion'
  #require 'opencv-rice'
  #ARGV.clear
  #IRB.start
  sh 'bundle exec irb -ropencv-rice'
end
