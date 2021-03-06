PROJECT(cleaver-gui)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(QT_VERSION 4 CACHE PATH "Choose between 4 or 5")

FIND_PACKAGE(OpenGL QUIET)

if(${QT_VERSION} MATCHES "5")
   add_definitions(-DUSING_QT5)
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   set(CMAKE_AUTOMOC ON)
   if(WIN32)
      cmake_policy(SET CMP0020 OLD)
   endif()

   # Find QT5
   find_package(Qt5Widgets REQUIRED)
   find_package(Qt5OpenGL REQUIRED)
   find_package(Qt5Core REQUIRED)
   find_package(Qt5Gui REQUIRED)

   #headers
   include_directories(${Qt5Widgets_INCLUDE_DIRS})
   include_directories(${Qt5OpenGL_INCLUDE_DIRS})
   include_directories(${Qt5Core_INCLUDE_DIRS})
   include_directories(${Qt5Gui_INCLUDE_DIRS})
   include_directories(${GLEXT_INCLUDE_DIR})

   #defines
   add_definitions(${Qt5Widgets_DEFINITIONS})
   add_definitions(${Qt5OpenGL_DEFINITIONS})
   add_definitions(${Qt5Core_DEFINITIONS})
   add_definitions(${Qt5Gui_DEFINITIONS})


   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
elseif(${QT_VERSION} MATCHES "4")

   # Find QT4, OpenGL
   FIND_PACKAGE(Qt4 QUIET)
   if(NOT QT4_FOUND)
      MESSAGE(STATUS "Unable to find Qt4. Cannot build Cleaver GUI")
      return()
   endif()

   if(WIN32)
      FIND_PACKAGE(GLEW)
   endif()
   # Ensure GUI and OpenGL Work
   SET( QT_USE_QTGUI TRUE )
   SET( QT_USE_QTOPENGL TRUE )
   SET( QT_USE_THREAD TRUE )
   SET( QT_USE_QTXML TRUE )

   # Qt Includes
   INCLUDE( ${QT_USE_FILE} )
   include_directories(${GLEW_INCLUDE_DIR})
else()
   message(FATAL_ERROR "Cannot build with specified Qt Version")
endif()

OPTION(BUILD_CLEAVER_APP "Build Cleaver GUI App (REQUIRES TEEM)" ON)

# Ensure GUI and OpenGL Work
ADD_DEFINITIONS(-DTETLIBRARY)

SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")

INCLUDE_DIRECTORIES(./Application ./Application/DataWidgets)

FILE(GLOB moc_srcs ./Application/*.cpp ./Application/Data/*.cpp ./Application/DataWidgets/*.cpp ./Application/ToolWidgets/*.cpp ./Application/ViewWidgets/*.cpp)
FILE(GLOB moc_hdrs ./Application/MainWindow.h   ./Application/Data/*.h   ./Application/DataWidgets/*.h   ./Application/ToolWidgets/*.h   ./Application/ViewWidgets/MeshViewOptionsWidget.h ./Application/ViewWidgets/MeshWindow.h)

# Add QT Files
FILE(GLOB Forms_UIS ./Application/*.ui ./Application/DataWidgets/*.ui ./Application/ToolWidgets/*.ui ./Application/ViewWidgets/*.ui)
FILE(GLOB RCC_FILES ./Resources/*.qrc)

# Add library incl1udes
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

# Add Source Files
FILE(GLOB srcs *.cpp ./Main/*.cpp )
FILE(GLOB hdrs *.h   ./Main/*.h   )

# Add Shader Files
FILE(GLOB vert ./Application/Shaders/*.vert)
FILE(GLOB frag ./Application/Shaders/*.frag)
FILE(GLOB vf_h ./Application/Shaders/*.h)

ADD_CUSTOM_COMMAND(
   OUTPUT  default_vert.h
   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Application/Shaders/default.vert ${CMAKE_CURRENT_SOURCE_DIR}/default.vert
   COMMAND xxd -i default.vert default_vert.h
   DEPENDS ./Application/Shaders/default.vert
   )

ADD_CUSTOM_COMMAND(
   OUTPUT  default_frag.h
   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Application/Shaders/default.frag ${CMAKE_CURRENT_SOURCE_DIR}/default.frag
   COMMAND xxd -i default.frag default_frag.h
   DEPENDS ./Application/Shaders/default.frag
   )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ./)

# Generate QT Stuff
if(${QT_VERSION} MATCHES "5")
   QT5_WRAP_UI(UI_SRC ${Forms_UIS})
   QT5_ADD_RESOURCES(RCC_SRC ${RCC_FILES})
elseif(${QT_VERSION} MATCHES "4")
   QT4_WRAP_UI(UI_SRC ${Forms_UIS})
   QT4_WRAP_CPP(MOC_SRC ${moc_hdrs})
   QT4_ADD_RESOURCES(RCC_SRC ${RCC_FILES})
endif()

ADD_CUSTOM_TARGET(comp_shaders
   DEPENDS ${default_vertex_shader} ${default_fragment_shader})
if(APPLE)
   ADD_EXECUTABLE(cleaver-gui MACOSX_BUNDLE ${srcs} ${hdrs} ${moc_srcs} ${MOC_SRC} ${UI_SRC} ${RCC_SRC} ${vert} ${frag} ${vf_h})
else()
ADD_EXECUTABLE(cleaver-gui ${srcs} ${hdrs} ${moc_srcs} ${MOC_SRC} ${UI_SRC} ${RCC_SRC} ${vert} ${frag} ${vf_h})
endif()

IF(WIN32) # Check if we are on Windows
   if(MSVC) # Check if we are using the Visual Studio compiler
      set_target_properties(cleaver-gui PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"")
   else()
      message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC)")
   endif()
ENDIF()

if(${QT_VERSION} MATCHES "5")
   if(WIN32)
      TARGET_LINK_LIBRARIES(cleaver-gui
         cleaver
         nrrd2cleaver
         teem
         synthetic
         ${OPENGL_LIBRARIES}
         ${QT_LIBRARIES}
         Qt5::Widgets
         Qt5::OpenGL
         Qt5::Core
         Qt5::Gui
         ${GLEXT_LIBRARY}
         ${QT_QTMAIN_LIBRARY}
         )
   else()
      TARGET_LINK_LIBRARIES(cleaver-gui
         cleaver
         nrrd2cleaver
         teem
         synthetic
         ${OPENGL_LIBRARIES}
         ${QT_LIBRARIES}
         Qt5::Widgets
         Qt5::OpenGL
         Qt5::Core
         Qt5::Gui
         ${OPTIONAL_LIBS})
   endif()
elseif(${QT_VERSION} MATCHES "4")
   if(WIN32)
      TARGET_LINK_LIBRARIES(cleaver-gui cleaver nrrd2cleaver teem synthetic ${OPENGL_LIBRARIES} ${QT_LIBRARIES} ${GLEW_LIBRARIES} )
   else()
      TARGET_LINK_LIBRARIES(cleaver-gui cleaver nrrd2cleaver teem synthetic ${OPTIONAL_LIBS} ${OPENGL_LIBRARIES} ${QT_LIBRARIES} )
   endif()
endif()

ADD_DEPENDENCIES(cleaver-gui comp_shaders)
