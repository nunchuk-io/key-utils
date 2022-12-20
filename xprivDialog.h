#ifndef XPRIVDIALOG_H
#define XPRIVDIALOG_H

#include <QDialog>

namespace Ui {
class xprivDialog;
}

class xprivDialog : public QDialog
{
    Q_OBJECT

public:
    explicit xprivDialog(QWidget *parent = nullptr);
    ~xprivDialog();
    void setPrivKey(QString value);

private slots:
    void on_copyBtn_clicked();
    void on_doneBtn_clicked();

private:
    Ui::xprivDialog *ui;
};

#endif // XPRIVDIALOG_H
