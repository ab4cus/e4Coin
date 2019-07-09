TARGET = qxcb

QT += core-private gui-private platformsupport-private xcb_qpa_lib-private

SOURCES = \
    qxcbmain.cpp
OTHER_FILES += xcb.json README

contains(QT_CONFIG, xcb-qt) {
    DEFINES += XCB_USE_RENDER
    XCB_DIR = ../../../3rdparty/xcb
    QMAKE_CFLAGS += -I$$XCB_DIR/include -I$$XCB_DIR/sysinclude $$QMAKE_CFLAGS_XCB
    QMAKE_CXXFLAGS += -I$$XCB_DIR/include -I$$XCB_DIR/sysinclude $$QMAKE_CFLAGS_XCB
}

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QXcbIntegrationPlugin
!equals(TARGET, $$QT_DEFAULT_QPA_PLUGIN): PLUGIN_EXTENDS = -
load(qt_plugin)
