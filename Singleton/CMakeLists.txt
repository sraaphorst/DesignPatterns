# Googletest includes library gtest_main, which includes a simple main to execute all tests.
configure_file(capitals.txt capitals.txt COPYONLY)
add_executable(Singleton Singleton.cpp)
target_link_libraries(Singleton gtest)# gtest_main)
add_test(NAME SingletonTotalPopulationTest COMMAND RecordFinderTests)
add_test(NAME DependentTotalPopulationTest COMMAND RecordFinderTests)

add_executable(DIContainer DIContainer.cpp)

add_executable(Monostate Monostate.cpp)
