#ifndef CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_

#include <QString>
#include <QVector>

#include "model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* m) : model(m) {}
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

  void calcVectorsGraph(const char* expression, double x_begin, double x_end) {
    model->calcVectorsWithPoints(expression, x_begin, x_end);
  }

  QVector<double> getXVector() {
    std::vector<double>& std_x = model->getVectorX();
    QVector<double> x(std_x.begin(), std_x.end());
    return x;
  }

  QVector<double> getYVector() {
    std::vector<double>& std_y = model->getVectorY();
    QVector<double> y(std_y.begin(), std_y.end());
    return y;
  }

  void calcReset() { model->calcReset(); }

  double result() { return model->result(); }
  Status status() { return model->status(); }

 private:
  Model* model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_SRC_CONTROLLER_H_
