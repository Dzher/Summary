# add_subdirectory(keyboard)
# include_directories(mainpanel)

set(PRIVATE_SOURCE
    mainpanel/mainpanel.cpp
    mainpanel/mainpanel.h
    main.cpp
)

qt5_wrap_cpp(MOC_FILES 
    mainpanel/mainpanel.cpp
    mainpanel/mainpanel.h
)
add_executable(Summary ${PRIVATE_SOURCE} ${MOC_FILES})
target_link_libraries(Summary Qt5::Core Qt5::Gui Qt5::Widgets)