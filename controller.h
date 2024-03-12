#ifndef CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_

#include <QString>

#include "model/polish_calc.h"

namespace s21 {

class Controller {
 public:
  Controller(PolishCalc* m) : model(m) {}
  void calculate(const char* expression, const char* x_value) {
    model->calculate(expression, x_value);
  }
  void calculate(const char* expression, double x_value) {
    model->calculate(expression, std::to_string(x_value).c_str());
  }

  QString getExpression() {
    return QString::fromStdString(model->getExpression());
  }
  QString getReversePolish() {
    return QString::fromStdString(model->getReversePolish());
  }
  double result() { return model->result(); }
  Status status() { return model->status(); }

 private:
  PolishCalc* model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_
