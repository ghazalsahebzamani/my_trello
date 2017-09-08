#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T14:45:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newqt
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    client_socket.cpp \
    tools.cpp \
    card.cpp \
    board.cpp \
    comment.cpp \
    funcs.cpp \
    list.cpp \
    trello.cpp \
    signup.cpp \
    dialog.cpp \
    name.cpp \
    login.cpp \
    logged_in_menu.cpp \
    show_boards.cpp \
    enter_board.cpp \
    add_new_member.cpp \
    find_mem.cpp \
    entered_board_menu.cpp \
    add_list.cpp \
    remove_list.cpp
 INCLUDEPATH += $$../Desktop/newqt
HEADERS  += mainwindow.h \
    client_socket.h \
    tools.h \
    exp.h \
    trello.h \
    board.h \
    list.h \
    card.h \
    member.h \
    comment.h \
    funcs.h \
    network_exception.h \
    newfuncs.h \
    signup.h \
    dialog.h \
    name.h \
    login.h \
    logged_in_menu.h \
    show_boards.h \
    enter_board.h \
    add_new_member.h \
    find_mem.h \
    entered_board_menu.h \
    add_list.h \
    remove_list.h

FORMS    += mainwindow.ui \
    signup.ui \
    dialog.ui \
    name.ui \
    login.ui \
    logged_in_menu.ui \
    show_boards.ui \
    enter_board.ui \
    add_new_member.ui \
    find_mem.ui \
    entered_board_menu.ui \
    add_list.ui \
    remove_list.ui
