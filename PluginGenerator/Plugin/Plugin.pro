ENVISION_ROOT_DIR = $$PWD/..
CONFIG(release, debug|release):BUILD_DIR = $${ENVISION_ROOT_DIR}/ReleaseBuild
CONFIG(debug, debug|release):BUILD_DIR = $${ENVISION_ROOT_DIR}/DebugBuild
PLUGINS_DIR = $${BUILD_DIR}/plugins
CONFIG(debug, debug|release):DEFINES += DEBUG
QMAKE_CXXFLAGS += -Werror

INCLUDEPATH += ./headers \
	./src \
	./test \
    $${ENVISION_ROOT_DIR}/Core/headers \
    $${ENVISION_ROOT_DIR}
TARGET = PLUGINNAME_LOWERCASE
DEFINES += PLUGINNAME_UPPERCASE_LIBRARY
win32:LIBS += -L$${PLUGINS_DIR} \
    -llogger \
    -lselftest
QT = core
TEMPLATE = lib
CONFIG += plugin warn_on thread
target.path = $$PLUGINS_DIR
pluginmeta.path = $$PLUGINS_DIR
pluginmeta.files = $${TARGET}.plugin
INSTALLS += target pluginmeta
HEADERS += headers/PLUGINNAME_LOWERCASE_api.h \
    src/PLUGINNAME_LOWERCASE.h
SOURCES += src/PLUGINNAME_LOWERCASE.cpp \
	test/SimpleTest.cpp