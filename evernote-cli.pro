TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += /usr/local/include/thrift

LIBS += -lboost_program_options -lthrift

SOURCES += main.cpp \
    sdk-evernote/Errors_constants.cpp \
    sdk-evernote/Errors_types.cpp \
    sdk-evernote/Limits_constants.cpp \
    sdk-evernote/Limits_types.cpp \
    sdk-evernote/NoteStore_constants.cpp \
    sdk-evernote/NoteStore_types.cpp \
    sdk-evernote/NoteStore.cpp \
    sdk-evernote/Types_constants.cpp \
    sdk-evernote/Types_types.cpp \
    sdk-evernote/UserStore_constants.cpp \
    sdk-evernote/UserStore_types.cpp \
    sdk-evernote/UserStore.cpp \
    Evernote/evernote.cpp \
    Evernote/note.cpp \
    Evernote/notebook.cpp \
    Evernote/notes.cpp \
    Evernote/resource.cpp \
    Evernote/tag.cpp

HEADERS += \
    sdk-evernote/Errors_constants.h \
    sdk-evernote/Errors_types.h \
    sdk-evernote/Limits_constants.h \
    sdk-evernote/Limits_types.h \
    sdk-evernote/NoteStore_constants.h \
    sdk-evernote/NoteStore_types.h \
    sdk-evernote/NoteStore.h \
    sdk-evernote/Types_constants.h \
    sdk-evernote/Types_types.h \
    sdk-evernote/UserStore_constants.h \
    sdk-evernote/UserStore_types.h \
    sdk-evernote/UserStore.h \
    consoleutils.h \
    Evernote/evernote.h \
    Evernote/note.h \
    Evernote/notebook.h \
    Evernote/notes.h \
    Evernote/resource.h \
    Evernote/tag.h

OTHER_FILES += \
    build-Debug/config.ini \
    TODO.txt
