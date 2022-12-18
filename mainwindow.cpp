#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tapsigner_utils.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QTimer>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);
    ui->frameFileInit->setVisible(true);
    ui->frameFileName->setVisible(false);
    ui->frameError->setVisible(false);
    ui->frameSucceed->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSuccessMessage(QString msg)
{
    ui->verifyBtn->setDisabled(true);
    ui->frameError->setVisible(false);
    ui->frameSucceed->setVisible(true);
    ui->succeedContent->setText(msg);
    QTimer::singleShot(2000, [this]() {
        ui->frameSucceed->setVisible(false);
        ui->verifyBtn->setDisabled(false);
    });
}

void MainWindow::showErrorMessage(QString msg)
{
    ui->verifyBtn->setDisabled(true);
    ui->frameSucceed->setVisible(false);
    ui->frameError->setVisible(true);
    ui->errorContent->setText(msg);

    QTimer::singleShot(2000, [this]() {
        ui->frameError->setVisible(false);
        ui->verifyBtn->setDisabled(false);
    });
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        filePath = fileName;
        if(filePath != ""){
            ui->frameFileInit->setVisible(false);
            ui->frameFileName->setVisible(true);
            ui->filenameObj->setText(filePath);
        }
    }
}

void MainWindow::onSelectFileBtnPressed()
{
    QFileDialog fileDialog(this, tr("Select encrypted file"));
    fileDialog.setNameFilter("AES Encrypted (*.aes *.AES);;Any file (*)");

    if (fileDialog.exec()) {
        const auto selectedFiles = fileDialog.selectedFiles();
        QFileInfo fileInfo(selectedFiles[0]);
        filePath = selectedFiles[0];
        if(filePath != ""){
            ui->frameFileInit->setVisible(false);
            ui->frameFileName->setVisible(true);
            ui->filenameObj->setText(filePath);
        }
    }
}

void MainWindow::onVerifyBtnPressed()
{
    if (filePath.isEmpty()) {
        showErrorMessage("Please select file");
        return;
    }
    QFileInfo info(filePath);
    QString ext = info.completeSuffix();
    qDebug() << "onVerifyBtnPressed" << ext;
    if(0 != QString::compare(ext, "aes", Qt::CaseInsensitive)){
        showErrorMessage("Please select *.AES file");
        return;
    }
    QFile file(filePath);
    file.open(QFile::OpenModeFlag::ReadOnly);
    auto result = tapsigner_utils::verifyTapsignerBackup(file.readAll(), ui->decryptionKeyTxt->toPlainText());
    if (!result) {
        showErrorMessage(result.error);
        return;
    }
    showSuccessMessage(QString("Your backup is working (chain=%1). To prevent unauthorized access, please remove the backup file from this device.")
                       .arg(result.chain));
    return;
}

void MainWindow::on_closeButton_clicked()
{
    ui->frameFileInit->setVisible(true);
    ui->frameFileName->setVisible(false);
    ui->filenameObj->setText("");
}
