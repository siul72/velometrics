# ============================================================================
# Qt Licensing Notes
# ============================================================================
#
# This project currently uses:
#
#   - QtCore
#   - QtNetwork
#   - QtDBus
#
# These modules are available under the Qt Commercial License,
# LGPLv3 and GPLv3 licensing options. They may be used in
# proprietary applications provided that the requirements of
# LGPLv3 are fully respected.
#
# Developers adding new Qt modules should verify the licensing
# terms of each module before introducing additional dependencies.
# Some Qt add-on modules are available only under GPL or commercial
# licensing terms and may not be suitable for proprietary products.
#
# When using Qt under LGPLv3, typical obligations include:
#
#   - Dynamic linking to Qt libraries.
#   - Distribution of applicable LGPL notices.
#   - Providing access to the Qt source code used, including any
#     modifications made to Qt itself.
#   - Allowing end users to replace the LGPL Qt libraries with
#     compatible versions.
#
# References:
#   https://doc.qt.io/qt-6/licensing.html
#   https://www.qt.io/development/open-source-lgpl-obligations
#
# ============================================================================

cmake_minimum_required(VERSION 3.24)
project(velometrics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
add_subdirectory(tests)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(yaml-cpp REQUIRED)

add_executable(velometrics src/velometrics-designer/main.cpp
        src/velometrics-designer/MainWindow.cpp
        src/velometrics-designer/MainWindow.h
        src/velometrics-designer/PropertiesDock/PropertiesDock.cpp
        src/velometrics-designer/PropertiesDock/PropertiesDock.h
        src/velometrics-designer/ElementsDock/ElementsDock.cpp
        src/velometrics-designer/ElementsDock/ElementsDock.h
        src/velometrics-designer/MainToolBar/MainToolBar.cpp
        src/velometrics-designer/MainToolBar/MainToolBar.h
        src/velometrics-designer/Canvas/CanvasWidget.cpp
        src/velometrics-designer/Canvas/CanvasWidget.h
        src/velometrics-designer/Canvas/CanvasScene.cpp
        src/velometrics-designer/Canvas/CanvasScene.h
        src/velometrics-designer/VelometricsMenuBar/VelometricsMenuBar.cpp
        src/velometrics-designer/VelometricsMenuBar/VelometricsMenuBar.h
        src/velometrics-designer/ActionManager/ActionManager.cpp
        src/velometrics-designer/ActionManager/ActionManager.h
        src/velometrics-designer/common/ElementType.h
        src/velometrics-designer/common/ElementType.cpp
        src/velometrics-designer/common/CanvasItem.h)

target_link_libraries(velometrics PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets yaml-cpp)
install(TARGETS velometrics RUNTIME DESTINATION bin)
install(FILES resources/velometrics-config.yaml DESTINATION share/velometrics)
