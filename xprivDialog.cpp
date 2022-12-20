#include "xprivDialog.h"
#include "ui_xprivDialog.h"
#include <QTextDocument>
#include <QClipboard>

xprivDialog::xprivDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xprivDialog)
{
    ui->setupUi(this);
}

xprivDialog::~xprivDialog()
{
    delete ui;
}

void xprivDialog::setPrivKey(QString value)
{
    ui->xprivKey->setText(value);
}

void xprivDialog::on_copyBtn_clicked()
{
     QApplication::clipboard()->setText(ui->xprivKey->toPlainText());
}

void xprivDialog::on_doneBtn_clicked()
{
    this->close();
}
