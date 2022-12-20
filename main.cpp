#include "mainwindow.h"

#include <QApplication>
#include "tapsigner_utils.h"

int main(int argc, char *argv[])
{
    if (argc == 3) {
        QFile file(argv[1]);
        file.open(QFile::OpenModeFlag::ReadOnly);
        auto result = tapsigner_utils::verifyTapsignerBackup(file.readAll(), argv[2]);
        if (result) {
            puts("Your backup file is valid");
            return 0;
        }
        puts(result.error.toStdString().c_str());
        return 1;
    }

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/FileIcon.svg"));
    MainWindow w;
    w.setWindowTitle("Tapsigner tool");
    w.show();
    return a.exec();
}
