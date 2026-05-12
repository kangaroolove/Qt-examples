#include "RulerWidget.h"

RulerWidget::RulerWidget()
{
    setObjectName("RulerWidget");
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget#RulerWidget{background-color:red}");
    setMinimumSize(50, 50);
}