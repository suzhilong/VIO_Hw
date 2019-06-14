cmake_minimum_required( VERSION 2.8 )
project( Hw1 )

find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )

add_executable( updateRotate updateRotate.cpp )
target_link_libraries( updateRotate ${Sophus_LIBRARIES} )
