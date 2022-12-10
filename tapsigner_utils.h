#ifndef TAPSIGNER_UTILS_H
#define TAPSIGNER_UTILS_H

#include <QByteArray>
#include <QString>

namespace tapsigner_utils {

    struct VerifyTapsignerBackupResult {
        QString fingerprint;
        QString xpriv;
        QString error;
        QString chain;

        explicit operator bool() const noexcept { return error.isEmpty(); }
    };

    VerifyTapsignerBackupResult verifyTapsignerBackup(const QByteArray &backup, const QString &decryptionKey);
}


#endif // TAPSIGNER_UTILS_H
