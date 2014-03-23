set(comp_srcs PanasonicNetworkCameraRt.cpp PanasonicNetworkCamera.cpp )
set(standalone_srcs PanasonicNetworkCameraRtComp.cpp)

if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)

# add OpenCV
find_package(OpenCV REQUIRED)
 
# add Boost
# if no specific libraries, Boost_LIBRARY_DIRS is empty
#find_package(Boost 1.55.0 REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS regex)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# add http library
set(network_camera_tmp "${PROJECT_SOURCE_DIR}/../NetworkCameraUtility")
get_filename_component(network_camera_dir ${network_camera_tmp} ABSOLUTE)
#
include_directories(${network_camera_dir}/include)

#
set(camera_lib_dir ${network_camera_dir}/build)

# find_library command can get absolute path to specified library name.
# but some library paths in VisualStudio include a configuration name, like "Release" or "Debug".
# So there are library directory and library name for VisualStudio.
set(CAMERA_UTIL_LIB "NetworkCameraUtility.lib")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/idl)
include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})
link_directories(${camera_lib_dir})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} 
          ${CAMERA_UTIL_LIB} ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES}  ${OpenCV_LIBS} 
          ${CAMERA_UTIL_LIB} ${Boost_LIBRARIES})
          
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)

