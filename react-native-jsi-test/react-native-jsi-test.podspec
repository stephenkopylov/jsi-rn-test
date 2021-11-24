require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-jsi-test"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => "10.0" }
  s.source       = { :git => "https://github.com/stephenkopylov/react-native-jsi-test.git", :tag => "#{s.version}" }

  s.source_files = "ios/**/*.{h,m,mm}", "cpp/**/*.{h,hpp,c,cpp}", "thirdParty/rapidjson/*.{hpp,cpp,h,c}", "thirdParty/rapidjson/error/*.{hpp,cpp,h,c}", "thirdParty/rapidjson/internal/*.{hpp,cpp,h,c}"

	s.xcconfig = { 'HEADER_SEARCH_PATHS' => '"${PODS_TARGET_SRCROOT}/thirdParty"' }
	
  s.dependency "React-Core"
	s.dependency "ReactCommon"
end
