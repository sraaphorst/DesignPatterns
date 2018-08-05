# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set (CMAKE_PREFIX_PATH "/Applications/Qt-5.9.4/5.9.4/clang_64" CACHE PATH "")
find_package(Qt5 COMPONENTS Widgets)

add_executable(Adapter Adapter.cpp)
target_link_libraries(Adapter LINK_PUBLIC Qt5::Widgets)
