
set(MAIN_PANEL
    mainpanel/mainpanel.cpp
    mainpanel/mainpanel.h
    main.cpp
)

set(SUMMARY_TOOLS
    tools/pathhelper.cpp
    tools/pathhelper.h
    utils/logger.cpp
    utils/logger.h
)

set(KEYBOARD_COUNTER
    keyboard/keycounter.cpp
    keyboard/keycounter.h
    keyboard/barchartdlg.cpp
    keyboard/barchartdlg.h
    keyboard/keytype.cpp
    keyboard/keytype.h
)

qt5_wrap_cpp(KEYBOARD_COUNTER_MOC_FILES ${KEYBOARD_COUNTER})

qt5_wrap_cpp(MAIN_PANEL_MOC_FILES 
    mainpanel/mainpanel.cpp
    mainpanel/mainpanel.h
)

add_executable(Summary 
                ${MAIN_PANEL} 
                ${SUMMARY_TOOLS}
                ${KEYBOARD_COUNTER} 
                ${KEYBOARD_COUNTER_MOC_FILES} 
                ${MAIN_PANEL_MOC_FILES}
)
target_link_libraries(Summary Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_SOURCE_DIR}/include/config.h @ONLY)
