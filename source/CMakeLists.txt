
if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()


file(GLOB_RECURSE VTK_PIPELINE_SRC *.cpp )

qt_add_resources(
    VTK_PIPELINE_RES
    ${CMAKE_CURRENT_LIST_DIR}/vtk-pipeline.qrc
)

if (WIN32)
    add_executable(vtk_pipeline
        ${VTK_PIPELINE_SRC}
        ${VTK_PIPELINE_RES}
        ${CMAKE_CURRENT_LIST_DIR}/vtk-pipeline.rc
    )
else ()
    add_executable(vtk_pipeline
        ${VTK_PIPELINE_SRC}
        ${VTK_PIPELINE_RES}
    )
endif ()


target_link_libraries(vtk_pipeline PRIVATE
    ${QT_LIBRARIES}
    ${VTK_LIBRARIES}
)

target_include_directories(
    vtk_pipeline ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)


set_target_properties(vtk_pipeline PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.vtk_pipeline.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)