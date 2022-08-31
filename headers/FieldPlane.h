#ifndef CODENAMESGAME__FIELDPLANE_H_
#define CODENAMESGAME__FIELDPLANE_H_

#include <QDialog>

class GameWorker;

class QGridLayout;

QT_BEGIN_NAMESPACE
namespace Ui { class FieldPlane; }
QT_END_NAMESPACE

class FieldPlane : public QDialog {
 Q_OBJECT

 public:
    explicit FieldPlane(QWidget *parent = nullptr);
    ~FieldPlane() override;

    void setWorker(GameWorker *worker);

    void showField();

 private:
    Ui::FieldPlane *ui;
    GameWorker *m_worker;
    QGridLayout *m_fieldLayout;
};

#endif //CODENAMESGAME__FIELDPLANE_H_
