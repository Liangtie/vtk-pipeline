cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(prelude)

project(
    vtk-pipeline
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(project-is-top-level)
include(variables)
include(link_qt)
include(link_vtk)
include(FetchContent)
include(GNUInstallDirs)

add_subdirectory(3rdparty)



if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

add_subdirectory(source)

# ---- Developer mode ----

if(NOT vtk-pipeline_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of vtk-pipeline"
  )
endif()

include(dev-mode)
