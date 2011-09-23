cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake_modules/ CACHE STRING "set path to cmake_modules")

####
## settings for OpenRTM and OpenHRP
##
include(FindPkgConfig)
include(CheckIncludeFiles)
find_package(OpenRTM REQUIRED)
find_package(OpenHRP REQUIRED)
include_directories(${OPENRTM_INCLUDE_DIRS})
link_directories(${OPENRTM_LIBRARY_DIRS})
include_directories(${OPENHRP_INCLUDE_DIRS})
link_directories(${OPENHRP_LIBRARY_DIRS})
include_directories(/opt/grx/include)

if(QNXNTO)
  include_directories(/usr/pkg/include)
  set(NO_COMP true)
else()
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LINUX__" )
  set(NO_COMP false)
endif()
endif(QNXNTO)

include(GenerateStubSkel)

#generate_stub_skel(Img)
generate_hrpsys_stub_skel_wrapper(Img)

set(comp_sources ImgSK.cc ImgDynSK.cc ImgSVC_impl.cpp VideoStream.cpp camera.cpp)
add_library(VideoStream SHARED ${comp_sources})
target_link_libraries(VideoStream ${OPENHRP_LIBRARIES})
set_target_properties(VideoStream PROPERTIES PREFIX "")

if(NO_COMP)
  set(target VideoStream)
else()
  add_executable(VideoStreamComp VideoStreamComp.cpp ${comp_sources})
  target_link_libraries(VideoStreamComp ${OPENHRP_LIBRARIES} cv cvaux highgui ueye_api)
  set(target VideoStream VideoStreamComp)
endif()

install(TARGETS ${target}
  RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
  LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
)
