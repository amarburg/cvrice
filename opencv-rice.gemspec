# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'opencv-rice/version'

Gem::Specification.new do |spec|
  spec.name          = "opencv-rice"
  spec.version       = CVRice::VERSION
  spec.authors       = ["Aaron Marburg"]
  spec.email         = ["amarburg@notetofutureself.org"]
  spec.summary       = %q{Interface to OpenCV Computer Vision library using RICE.}
  spec.description   = %q{...}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.extensions    = "ext/opencv_rice/mkrf_conf.rb"

  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"

  spec.add_development_dependency "minitest"
  
  spec.add_dependency "rice"
  spec.add_dependency "mkrf"
end
