#ifndef CPP3_SMARTCALC_V2_0_SRC_QT_VIEW_CALC_VIEW_H_
#define CPP3_SMARTCALC_V2_0_SRC_QT_VIEW_CALC_VIEW_H_

#include <QWidget>

#include "../controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcWidget;
}
QT_END_NAMESPACE

/**
 * @brief is a QWidget - main_window of calculator
 */
class CalcView : public QWidget {
  Q_OBJECT

 public:
  CalcView(QWidget *parent = nullptr, s21::Controller *c = nullptr);
  ~CalcView();

  std::string getExpression();
  std::string getXValue();

  void showResult();

 private:
  void areaOfDefinitionCheck();
  void expressionChanged();
  void xValueChanged();
  void graphButtonChecked(bool checked);
  void equalButtonClicked();
  void buildGraph();
  void cleanHistory();
  void showInfo();

  bool is_graph_mode_;
  s21::Controller *controller_;
  Ui::CalcWidget *ui;
};
#endif  // CPP3_SMARTCALC_V2_0_SRC_QT_VIEW_CALC_VIEW_H_
