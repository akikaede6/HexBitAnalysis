project(HexBitAnalysis)
cmake_minimum_required(VERSION 3.23)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES
  src/main.cpp
  src/analsiswidget.cpp
  src/binarywidget.cpp
  src/widget/fontdialog.cpp
  src/mainwindow.cpp
  src/widget/mousegroupbox.cpp
  src/widget/bitdialog.cpp
  src/selectedwidget.cpp
  src/util.cpp
  icon/image.qrc
  icon/appicon.rc
  HexBitAnalysis.desktop
)
set(HEADER_FILES
  src/analsiswidget.h
  src/binarywidget.h
  src/widget/fontdialog.h
  src/mainwindow.h
  src/widget/mousegroupbox.h
  src/selectedwidget.h
  src/util.h
  src/widget/bitdialog.h
  )
add_executable(HexBitAnalysis ${SOURCES})
target_link_libraries(HexBitAnalysis PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(HexBitAnalysis PROPERTIES WIN32_EXECUTABLE TRUE)
install(TARGETS HexBitAnalysis DESTINATION bin)
install(FILES HexBitAnalysis.desktop DESTINATION share/applications)
install(FILES icon/app.png icon/minus.png icon/plus.png DESTINATION share/HexBitAnalysis)
