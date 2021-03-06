project(libdirectsound)

INCLUDE(CheckIncludeFile)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# libqmmp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../../../qmmp)

# Win32 DirectSound
CHECK_INCLUDE_FILE(dsound.h DSOUND_H_FOUND)

SET(libdirectsound_SRCS
  outputdirectsound.cpp
  outputdirectsoundfactory.cpp
)

SET(libdirectsound_HDRS
  outputdirectsound.h
)

SET(libdirectsound_RCCS translations/translations.qrc)

QT5_ADD_RESOURCES(libdirectsound_RCC_SRCS ${libdirectsound_RCCS})


IF(DSOUND_H_FOUND)
ADD_LIBRARY(directsound MODULE ${libdirectsound_SRCS} ${libdirectsound_RCC_SRCS} ${libdirectsound_HDRS})
add_dependencies(directsound qmmp)
target_link_libraries(directsound Qt5::Widgets -lqmmp -ldxguid -lstrmiids -ldmoguids -lmsdmo -lole32 -loleaut32 -luuid -lgdi32 -ldsound)
install(TARGETS directsound DESTINATION ${LIB_DIR}/qmmp/Output)
ENDIF(DSOUND_H_FOUND)

