#include "ParameterWidget.h"

ParameterWidget::ParameterWidget()
{
    setObjectName("ParameterWidget");
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget#ParameterWidget{background-color:blue}");
    setMinimumSize(50, 50);
}