
TEMPLATE = app
DESTDIR = .
CONFIG += console c++14
QT -= gui core

HEADERS += custom.hpp

SOURCES += main.cpp

TEST_CFG_FILES += test.cfg

include( ../../test.pri)

INCLUDEPATH += $$PWD/../../..
DEPENDPATH += $$PWD/../../..

TO_GENERATE = test.cfgfile

QMAKE_EXTRA_COMPILERS += generate_cfg
generate_cfg.name = CONF_GEN
generate_cfg.input = TO_GENERATE
generate_cfg.output = ${QMAKE_FILE_BASE}.hpp
generate_cfg.CONFIG = no_link
generate_cfg.variable_out = HEADERS

generate_cfg.commands = $$shell_path( $$absolute_path( $${OUT_PWD}/../../../cfgfile.generator ) ) \
-i ${QMAKE_FILE_IN} \
-o $${OUT_PWD}/${QMAKE_FILE_BASE}.hpp

PRE_TARGETDEPS += compiler_generate_cfg_make_all
