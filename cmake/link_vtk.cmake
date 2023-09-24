find_package(VTK
  COMPONENTS
    CommonCore
    GUISupportQt
    IOImage
    ImagingColor
    ImagingGeneral
    InteractionImage
    InteractionStyle
    InteractionWidgets
    RenderingOpenGL2
)

# target_link_libraries(XX PRIVATE ${VTK_LIBRARIES})