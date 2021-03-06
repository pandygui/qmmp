project(libstatusicon)

# qt plugin
ADD_DEFINITIONS( -Wall )
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)
ADD_DEFINITIONS(-DQT_THREAD)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

SET(QT_INCLUDES
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../
)

# libqmmpui & libqmmp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../qmmpui)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../qmmp)

SET(libstatusicon_SRCS
    settingsdialog.cpp
    statusicon.cpp
    statusiconfactory.cpp
    qmmptrayicon.cpp
    statusiconpopupwidget.cpp
    coverwidget.cpp
)

SET(libstatusicon_RCCS 
    translations/translations.qrc
    images/tray_images.qrc)

QT4_ADD_RESOURCES(libstatusicon_RCC_SRCS ${libstatusicon_RCCS})

# user interface


SET(libstatusicon_UIS
    settingsdialog.ui
)

QT4_WRAP_UI(libstatusicon_UIS_H ${libstatusicon_UIS})
# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

ADD_LIBRARY(statusicon MODULE ${libstatusicon_SRCS} ${libstatusicon_UIS_H} ${libstatusicon_RCC_SRCS})
add_dependencies(statusicon qmmpui libqmmp)
target_link_libraries(statusicon ${QT_LIBRARIES} qmmpui libqmmp)
install(TARGETS statusicon DESTINATION ${LIB_DIR}/qmmp/General)
