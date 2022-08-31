#ifndef CODENAMESGAME_CLICKABLELABEL_H
#define CODENAMESGAME_CLICKABLELABEL_H

#include <QLabel>
#include <Qt>

class ClickableLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    ~ClickableLabel() override;

signals:

    void clicked();

    void doubleClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif //CODENAMESGAME_CLICKABLELABEL_H
