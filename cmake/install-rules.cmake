install(
    TARGETS vtk_pipeline
    RUNTIME COMPONENT vtk-pipeline_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
