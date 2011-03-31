PROJECT(PhotoCL)

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
endif(COMMAND cmake_policy)

IF (WIN32)
  # expect that classes are being imported
  # Note: MSVC doesn't like when the macros are quotes
  # and MSYS doesn't like them unqouted (bacause of braces)
  IF (MSVC)
    ADD_DEFINITIONS("-DMS_DLL_SPEC=__declspec(dllimport)")
  ELSE (MSVC)
    ADD_DEFINITIONS("-UMS_DLL_SPEC \"-DMS_DLL_SPEC=__declspec(dllimport)\"")
  ENDIF (MSVC)
ELSE (WIN32)
  ADD_DEFINITIONS(-DMS_DLL_SPEC=)
ENDIF (WIN32)

#MinGW seems to build the exe in Release mode but plugins in Debug mode as default
ADD_DEFINITIONS(-DQT_NO_DEBUG)

# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_find_rules ${CMAKE_MODULE_PATH})

SET (PCL_DEBUG_MESSAGES FALSE CACHE BOOL "Flag to indicate of debug messages should be displayed")
IF (PCL_DEBUG_MESSAGES)
  ADD_DEFINITIONS(-DPCLDEBUG=1)
ENDIF (PCL_DEBUG_MESSAGES)

IF( MSVC )
  SET (QT_USE_QTMAIN TRUE)
ENDIF ( MSVC )

SET (QT_USE_QT3SUPPORT FALSE)
SET (QT_USE_QTGUI TRUE)
SET (QT_USE_QTNETWORK TRUE)
SET (QT_USE_QTSQL TRUE)
SET (QT_USE_QTSVG TRUE)
SET (QT_USE_QTWEBKIT TRUE)
SET (QT_USE_QTXML TRUE)
FIND_PACKAGE(Qt4 REQUIRED)


# set up the install locations
IF ( WIN32 )
  SET ( CMAKE_INSTALL_PREFIX   ./install )
  SET ( PHOTOCL_BIN_SUBDIR     . )
  SET ( PHOTOCL_LIB_SUBDIR     . )
  SET ( PHOTOCL_PLUGIN_SUBDIR  ./plugins )
  SET ( PHOTOCL_INCLUDE_SUBDIR ./include/photocl )
  
ELSE ( WIN32 )
  SET ( CMAKE_INSTALL_PREFIX   /usr/local )
  SET ( PHOTOCL_BIN_SUBDIR     bin )
  SET ( PHOTOCL_LIB_SUBDIR     lib )
  SET ( PHOTOCL_PLUGIN_SUBDIR  lib/photocl )
  SET ( PHOTOCL_INCLUDE_SUBDIR include/photocl )
ENDIF ( WIN32 )

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.in_cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake")



INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
  ${PhotoCL_SOURCE_DIR}/src/app
  ${PhotoCL_SOURCE_DIR}/src/core
  ${CMAKE_BINARY_DIR}/src/ui
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

SUBDIRS( src )


# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH ".:/usr/lib:/usr/local/lib:/usr/local/lib/photocl:/usr/lib/photocl")

SET( PhotoCL_APP_SRCS
     src/main.cpp
   )

IF( WIN32 )
  IF ( PCL_DEBUG_MESSAGES )
	ADD_EXECUTABLE( photocl ${PhotoCL_APP_SRCS})
  ELSE ( PCL_DEBUG_MESSAGES )
    ADD_EXECUTABLE( photocameralocator WIN32 ${PhotoCL_APP_SRCS})
  ENDIF ( PCL_DEBUG_MESSAGES )

ELSE( WIN32 )
  ADD_EXECUTABLE( photocameralocator ${PhotoCL_APP_SRCS} )
ENDIF( WIN32 )

SET_TARGET_PROPERTIES( photocameralocator PROPERTIES
  INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${PHOTOCL_LIB_SUBDIR}
  INSTALL_RPATH_USE_LINK_PATH true
  )

TARGET_LINK_LIBRARIES( photocameralocator photocl ${QT_LIBRARIES} )

INSTALL( TARGETS photocameralocator DESTINATION ${PHOTOCL_BIN_SUBDIR} )
