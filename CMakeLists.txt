cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
option(CMAKE_MODULE_PATH ../../cmake_modules/)

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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LINUX__")
endif()
endif(QNXNTO)

include(GenerateStubSkel)

generate_stub_skel(VideoStreamService)
generate_hrpsys_stub_skel_wrapper(JointDataTypes)

set(comp_sources VideoStreamServiceSk.cpp VideoStreamServiceSVC_impl.cpp VideoStream.cpp camera.cpp)
add_library(VideoStream SHARED ${comp_sources})
target_link_libraries(VideoStream ${OPENHRP_LIBRARIES})
set_target_properties(VideoStream PROPERTIES PREFIX "")

if(NO_COMP)
  set(target VideoStream)
else()
  add_executable(VideoStreamComp VideoStreamComp.cpp ${comp_sources})
  target_link_libraries(VideoStreamComp ${OPENHRP_LIBRARIES})
  set(target VideoStream VideoStreamComp)
endif()

install(TARGETS ${target}
  RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
  LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
)

if(ENABLE_COMMERCIAL)
  target_link_libraries(VideoStream certify)
  target_link_libraries(VideoStreamComp certify)
endif()
