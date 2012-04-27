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

  if (EXISTS /usr/include/uEye.h)
    add_definitions(USE_UEYE_CAMERA)
  endif()

  include(GenerateStubSkel)
  generate_hrpsys_stub_skel_wrapper(Img)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/OpenHRPCommon)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/ModelLoader)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/World)
  generate_stub_skel_cpp(/opt/grx/share/OpenHRP-3.1/idl/OpenHRP/ViewSimulator)

  set(comp_name VideoStream)

  set(comp_sources ${comp_name}.cpp)
  set(comp_sources ${comp_sources} camera.cpp)
  set(comp_sources ${comp_sources} ImgSK.cc ImgDynSK.cc ImgSVC_impl.cpp)
  set(comp_sources ${comp_sources} OpenHRPCommonSk.cpp ModelLoaderSk.cpp WorldSk.cpp ViewSimulatorSk.cpp)
  add_library(${comp_name} SHARED ${comp_sources})
  target_link_libraries(${comp_name} ${OPENHRP_LIBRARIES})
  set_target_properties(${comp_name} PROPERTIES PREFIX "")

  add_executable(${comp_name}Comp ${comp_name}Comp.cpp ${comp_sources})

  if (EXISTS /usr/lib/libcv.so)
    target_link_libraries(${comp_name}Comp ${OPENHRP_LIBRARIES} cv cvaux highgui)
  else()
    target_link_libraries(${comp_name}Comp ${OPENHRP_LIBRARIES} opencv_core opencv_highgui opencv_imgproc opencv_objdetect)
  endif()

  if (EXISTS /usr/lib/libueye_api.so)
    target_link_libraries(${comp_name}Comp ueye_api)
  endif()

  set(target ${comp_name} ${comp_name}Comp)

  install(TARGETS ${target}
    RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
    LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
  )
endif()
