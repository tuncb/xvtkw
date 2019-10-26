PROJECT(xvtkw_tester)
cmake_minimum_required(VERSION 3.10)

set(SOURCES
  "./source/main.cpp"
  "./source/vtu_pvd_file_tester.cpp"
)
set(XVTKW_LIB
  ../xvtkw/include/xvtkw/byteorder.h
  ../xvtkw/include/xvtkw/ByteOrder.h
  ../xvtkw/include/xvtkw/DataSet.h
  ../xvtkw/include/xvtkw/InternalUtilities.h
  ../xvtkw/include/xvtkw/PvdFile.h
  ../xvtkw/include/xvtkw/Version.h
  ../xvtkw/include/xvtkw/VtuFile.h
  ../xvtkw/include/xvtkw/VtuType.h
  ../xvtkw/include/xvtkw/VtuWriter.h
)

add_executable(xvtkw_tester ${SOURCES} ${XVTKW_LIB})
target_include_directories(xvtkw_tester PRIVATE "../xvtkw/include/")
target_include_directories(xvtkw_tester PRIVATE "./external/")

target_compile_options(xvtkw_tester PRIVATE "/std:c++latest")

source_group("xvtkw_library" FILES ${XVTKW_LIB})

