#include "FieldPlane.h"
#include "ui_FieldPlane.h"
#include "GameWorker.h"
#include "ClickableLabel.h"
#include <QGridLayout>

FieldPlane::FieldPlane(QWidget *parent) :
    QDialog(parent), ui(new Ui::FieldPlane) {
    ui->setupUi(this);
    setModal(true);
    m_worker = nullptr;
    m_fieldLayout = new QGridLayout();
    ui->field->setLayout(m_fieldLayout);
    connect(ui->pushButton_close, &QPushButton::clicked, this, &FieldPlane::close);
}

FieldPlane::~FieldPlane() {
    delete ui;
}

void FieldPlane::setWorker(GameWorker *worker) {
    m_worker = worker;
}

void FieldPlane::showField() {
    for (int i = 0; i < GameWorker::FIELD_HEIGHT; i++) {
        for (int j = 0; j < GameWorker::FIELD_WIDTH; j++) {
            auto label = new ClickableLabel(this);
            label->setAlignment(Qt::AlignCenter);

            label->setText(tr("Label (%1; %2)").arg(i).arg(j));
            label->setProperty("type", "field-label");
            label->setProperty("row", i);
            label->setProperty("col", j);

            switch (m_worker->getType(i, j)) {
                case GameWorker::BlueCard:
                    label->setStyleSheet("color: blue");
                    break;
                case GameWorker::RedCard:
                    label->setStyleSheet("color: red");
                    break;
                case GameWorker::WhiteCard:
                    label->setStyleSheet("color: gray");
                    break;
                case GameWorker::BlackCard:
                    label->setStyleSheet("color: black");
                    break;
                case GameWorker::Invalid:
                    Q_UNREACHABLE();
            }
            m_fieldLayout->addWidget(label, i, j);
        }
    }
}
