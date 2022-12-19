#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showSuccessMessage(QString msg);
    void showErrorMessage(QString msg);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void onSelectFileBtnPressed();
    void onVerifyBtnPressed();
    void on_closeButton_clicked();
    void on_advanceBtn_clicked();
    void exportXFP();

private:
    Ui::MainWindow *ui;
    QString filePath;
    QGraphicsDropShadowEffect *mDropShadow;
};
#endif // MAINWINDOW_H
