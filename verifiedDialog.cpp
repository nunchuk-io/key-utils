#include "verifiedDialog.h"
#include "ui_verifiedDialog.h"
#include <QFile>

verifiedDialog::verifiedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::verifiedDialog),
    filePath("")
{
    ui->setupUi(this);
}

verifiedDialog::~verifiedDialog()
{
    delete ui;
}

void verifiedDialog::setFilePath(QString path)
{
    filePath = path;
}

void verifiedDialog::on_yesBtn_clicked()
{
    QFile::remove(filePath);
    emit removeFileDone();
    close();
}

void verifiedDialog::on_keepBtn_clicked()
{
    close();
}
