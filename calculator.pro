QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/expression.cc \
    model/lexems.cc \
    model/polish_calc.cc \
    model/qcustomplot.cpp \
    model/shanting_yard.cc \
    view/calc_view.cc \
    main.cc

HEADERS += \
  controller.h \
  model/expression.h \
  model/lexems.h \
  model/polish_calc.h \
  model/qcustomplot.h \
  model/shanting_yard.h \
  view/calc_view.h

FORMS += \
    view/calcwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    view/icons/icons.qrc

ICON = view/icons/calculator_icon.ico
