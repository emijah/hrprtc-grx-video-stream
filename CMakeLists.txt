cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
if (NOT CMAKE_MODULE_PATH)
  set(CMAKE_MODULE_PATH /opt/grx/share/hrpsys/cmake_modules/ CACHE STRING "set path to cmake_modules")
endif(NOT CMAKE_MODULE_PATH)

####
## settings for OpenRTM and OpenHRP
##
if(NOT QNXNTO)
  include(FindPkgConfig)
  include(CheckIncludeFiles)
  find_package(OpenRTM REQUIRED)
  find_package(OpenHRP REQUIRED)
  include_directories(${OPENRTM_INCLUDE_DIRS})
  link_directories(${OPENRTM_LIBRARY_DIRS})
  include_directories(${OPENHRP_INCLUDE_DIRS})
  link_directories(${OPENHRP_LIBRARY_DIRS})
  include_directories(/opt/grx/include)

  if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LINUX__" )
  endif()

  include(GenerateStubSkel)
  generate_hrpsys_stub_skel_wrapper(Img)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/OpenHRPCommon)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/ModelLoader)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/World)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/ViewSimulator)

  set(comp_sources ImgSK.cc ImgDynSK.cc ImgSVC_impl.cpp VideoStream.cpp camera.cpp)
  set(comp_sources ${comp_sources} OpenHRPCommonSk.cpp ModelLoaderSk.cpp WorldSk.cpp ViewSimulatorSk.cpp)
  add_library(VideoStream SHARED ${comp_sources})
  target_link_libraries(VideoStream ${OPENHRP_LIBRARIES})
  set_target_properties(VideoStream PROPERTIES PREFIX "")

  add_executable(VideoStreamComp VideoStreamComp.cpp ${comp_sources})
  target_link_libraries(VideoStreamComp ${OPENHRP_LIBRARIES} cv cvaux highgui ueye_api)
  set(target VideoStream VideoStreamComp)
  install(TARGETS ${target}
    RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
    LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
  )
endif()
