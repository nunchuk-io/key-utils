#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tapsigner_utils.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::onSelectFileBtnPressed()
{
    QFileDialog fileDialog(this, tr("Select encrypted file"));
    fileDialog.setNameFilter("AES Encrypted (*.aes *.AES);;Any file (*)");

    if (fileDialog.exec()) {
        const auto selectedFiles = fileDialog.selectedFiles();
        QFileInfo fileInfo(selectedFiles[0]);
        filePath = selectedFiles[0];
    }
}

void MainWindow::onVerifyBtnPressed()
{
    if (filePath.isEmpty()) {
        QMessageBox(QMessageBox::Critical, tr("Error"), tr("Please select file")).exec();
        return;
    }

    QFile file(filePath);
    file.open(QFile::OpenModeFlag::ReadOnly);
    auto result = tapsigner_utils::verifyTapsignerBackup(file.readAll(), ui->decryptionKeyTxt->toPlainText());

    if (!result) {
        QMessageBox(QMessageBox::Critical, tr("Error"), result.error).exec();
        return;
    }

    QMessageBox(QMessageBox::Information, tr("Success"),
                QString("Your backup is working (chain=%2). To prevent unauthorized access, please remove the backup file from this device.").arg(result.chain)).exec();
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}
