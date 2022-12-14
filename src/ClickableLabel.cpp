#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f)
        : QLabel(parent) {
}

ClickableLabel::~ClickableLabel() = default;

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}
