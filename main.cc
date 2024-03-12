#include <QApplication>

#include "controller.h"
#include "model/polish_calc.h"
#include "view/calc_view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/calculator_icon.ico"));
  s21::PolishCalc model;
  s21::Controller controller(&model);
  qDebug() << controller.result();
  CalcView view(nullptr, &controller);
  view.show();
  return app.exec();
}
