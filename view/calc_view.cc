#include "calc_view.h"

#include "../controller.h"
#include "ui_calcwidget.h"

CalcView::CalcView(QWidget* parent, s21::Controller* c)
    : QWidget(parent),
      is_graph_mode_(false),
      controller_(c),
      ui(new Ui::CalcWidget) {
  ui->setupUi(this);
  ui->clean_button->hide();
  ui->graph_view->hide();
  ui->info_view->hide();
  ui->q_custom_plot->setBackground(QColor(0, 0, 0, 0));
  QRegularExpressionValidator* area_validator = new QRegularExpressionValidator(
      QRegularExpression("^-?(1000000|[0-9]{1,6}(\\.[0-9]{1,7})?$)"));
  ui->x_min_val->setValidator(area_validator);
  ui->x_max_val->setValidator(area_validator);
  ui->y_min_val->setValidator(area_validator);
  ui->y_max_val->setValidator(area_validator);
  connect(ui->expression_input, &QTextEdit::textChanged, this,
          &CalcView::expressionChanged);
  connect(ui->x_value_input, &QLineEdit::textChanged, this,
          &CalcView::xValueChanged);
  connect(ui->equal_button, &QPushButton::clicked, this,
          &CalcView::equalButtonClicked);
  connect(ui->graph_button, &QPushButton::clicked, this,
          &CalcView::graphButtonChecked);
  connect(ui->clean_button, &QPushButton::clicked, this,
          &CalcView::cleanHistory);
  connect(ui->info_button, &QPushButton::clicked, this, &CalcView::showInfo);
}

CalcView::~CalcView() { delete ui; }

std::string CalcView::getExpression() {
  std::string expression = ui->expression_input->toPlainText().toStdString();
  return expression;
}

std::string CalcView::getXValue() {
  std::string x_value = ui->x_value_input->text().toStdString();
  return x_value;
}

void CalcView::buildGraph() {
  ui->q_custom_plot->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui->q_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                     QCP::iSelectPlottables);

  areaOfDefinitionCheck();
  double x_begin = ui->x_min_val->text().toDouble();
  double x_end = ui->x_max_val->text().toDouble();
  double y_min = ui->y_min_val->text().toDouble();
  double y_max = ui->y_max_val->text().toDouble();
  double step = (x_end - x_begin) / 1000;
  QVector<double> x, y;

  if (x_begin < x_end) {
    for (double i = x_begin; i <= x_end; i += step) {
      controller_->calculate(getExpression().c_str(), i);
      if (controller_->status() == s21::Status::kOk) {
        x.push_back(i);
        y.push_back(controller_->result());
      } else {
        qDebug() << i;
      }
    }
    ui->q_custom_plot->xAxis->setRange(x_begin, x_end);
    ui->q_custom_plot->yAxis->setRange(y_min, y_max);
    ui->q_custom_plot->graph(0)->setData(x, y);
    ui->q_custom_plot->replot();
  }
}

void CalcView::showResult() {
  if (ui->graph_button->isChecked()) {
    ui->result_output->clear();
    buildGraph();
  } else {
    controller_->calculate(getExpression().c_str(), getXValue().c_str());
    if (controller_->status() == s21::Status::kOk) {
      ui->result_output->setText(
          QString::number(controller_->result(), 'g', 7));
    }
  }
}

void CalcView::expressionChanged() {
  if (ui->expression_input->toPlainText().isEmpty()) {
    ui->expression_input->setFontPointSize(18);
    ui->result_output->clear();
    return;
  }
  if (ui->x_value_input->text().isEmpty()) {
    ui->x_value_input->setText("0");
  }
  showResult();
}

void CalcView::xValueChanged() {
  if (ui->x_value_input->text().isEmpty() ||
      ui->expression_input->toPlainText().isEmpty()) {
    ui->result_output->setText("invalid value for x");
  } else {
    showResult();
  }
}

void CalcView::graphButtonChecked(bool checked) {
  is_graph_mode_ = checked;
  if (is_graph_mode_) {
    ui->clean_button->hide();
    ui->info_button->hide();
    ui->info_view->hide();
    ui->graph_view->show();
    ui->q_custom_plot->clearGraphs();
    ui->q_custom_plot->clearPlottables();
    ui->q_custom_plot->addGraph();
    expressionChanged();
  } else {
    ui->graph_view->hide();
    if (ui->history_list->count()) {
      ui->clean_button->show();
    } else {
      ui->info_button->show();
    }
    ui->q_custom_plot->removeGraph(0);
    ui->q_custom_plot->replot();
    expressionChanged();
  }
}

void CalcView::equalButtonClicked() {
  expressionChanged();

  ui->info_view->hide();
  ui->info_button->hide();
  if (is_graph_mode_ == false && controller_->status() == s21::Status::kOk) {
    ui->clean_button->show();
    ui->history_list->addItem(controller_->getExpression());
    ui->history_list->addItem(controller_->getReversePolish());
    ui->history_list->addItem(ui->result_output->text());
    ui->history_list->addItem("-----------------");
    qDebug() << controller_->result();
  } else if (controller_->status() == s21::Status::kInvalidExpression) {
    ui->result_output->setText("Invalid expression");
  }
}

void CalcView::showInfo() {
  ui->info_view->show();
  ui->info_button->hide();
  ui->clean_button->show();
}

void CalcView::cleanHistory() {
  ui->info_view->hide();
  ui->history_list->clear();
  ui->clean_button->hide();
  ui->info_button->show();
}

void CalcView::areaOfDefinitionCheck() {
  if (ui->x_min_val->text().isEmpty()) {
    ui->x_min_val->setText("-10.00");
  }
  if (ui->x_max_val->text().isEmpty()) {
    ui->x_max_val->setText("10.00");
  }
  if (ui->y_min_val->text().isEmpty()) {
    ui->y_min_val->setText("-10.00");
  }
  if (ui->y_max_val->text().isEmpty()) {
    ui->y_max_val->setText("10.00");
  }
}
