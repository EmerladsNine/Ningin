# CMake generated Testfile for 
# Source directory: C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner
# Build directory: C:/Users/User/Downloads/jsoncpp-1.9.5/out/build/x64-Debug/src/jsontestrunner
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(jsoncpp_readerwriter "C:/Users/User/AppData/Local/Programs/Python/Python312/python.exe" "-B" "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/runjsontests.py" "C:/Users/User/Downloads/jsoncpp-1.9.5/out/build/x64-Debug/bin/jsontestrunner_exe.exe" "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter PROPERTIES  WORKING_DIRECTORY "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/CMakeLists.txt;43;add_test;C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/CMakeLists.txt;0;")
add_test(jsoncpp_readerwriter_json_checker "C:/Users/User/AppData/Local/Programs/Python/Python312/python.exe" "-B" "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/runjsontests.py" "--with-json-checker" "C:/Users/User/Downloads/jsoncpp-1.9.5/out/build/x64-Debug/bin/jsontestrunner_exe.exe" "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter_json_checker PROPERTIES  WORKING_DIRECTORY "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/CMakeLists.txt;47;add_test;C:/Users/User/Downloads/jsoncpp-1.9.5/src/jsontestrunner/CMakeLists.txt;0;")
