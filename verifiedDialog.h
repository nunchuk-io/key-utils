#ifndef VERIFIEDDIALOG_H
#define VERIFIEDDIALOG_H

#include <QDialog>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class verifiedDialog;
}

class verifiedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit verifiedDialog(QWidget *parent = nullptr);
    ~verifiedDialog();
    void setFilePath(QString path);
signals:
    void removeFileDone();

private slots:
    void on_yesBtn_clicked();
    void on_keepBtn_clicked();

private:
    Ui::verifiedDialog *ui;
    QString filePath;
};

#endif // VERIFIEDDIALOG_H
