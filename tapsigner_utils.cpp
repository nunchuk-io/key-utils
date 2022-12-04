#include "tapsigner_utils.h"
#include <vector>
#include <QRegExp>
#include <QDebug>

#include <crypto/aes.h>
#include <util/strencodings.h>
#include <base58.h>
#include <support/cleanse.h>

static constexpr int AES_BLOCK_SIZE = 16;

template<typename It>
static std::string AES128CTRDecrypt(
        It cipher_begin, It cipher_end, It key_begin, It key_end,
        std::vector<unsigned char> counter = std::vector<unsigned char>(AES_BLOCK_SIZE, 0)) {
    auto increment_counter = [&]() {
        for (int i = AES_BLOCK_SIZE - 1; i > 0; --i) {
            if (++counter[i]) {
                break;
            }
        }
    };

    AES128_ctx ctx;
    AES128_init(&ctx, reinterpret_cast<const unsigned char*>(&(*key_begin)));

    std::string plain{cipher_begin, cipher_end};
    auto *pos = plain.data();

    int left = plain.size();
    unsigned char buf[AES_BLOCK_SIZE];
    while (left > 0) {
        AES128_encrypt(&ctx, 1, buf, counter.data());
        const int len = (left < AES_BLOCK_SIZE) ? left : AES_BLOCK_SIZE;
        for (int j = 0; j < len; j++) {
            pos[j] ^= buf[j];
        }
        pos += len;
        left -= len;
        increment_counter();
    }
    return plain;
}

namespace tapsigner_utils {

static std::pair<std::string, std::string> getKeyFingerPrint(const std::string &str) {
    static constexpr unsigned char BASE58_MAINNET_PRIV_PREFIX[] = {0x04, 0x88, 0xAD, 0xE4};
    static constexpr unsigned char BASE58_TESTNET_PRIV_PREFIX[] = {0x04, 0x35, 0x83, 0x94};
    static constexpr unsigned int BIP32_EXTKEY_SIZE = 74;

    std::string parent_fingerprint;
    std::string chain;
    std::vector<unsigned char> data;

    if (!DecodeBase58Check(str, data, 78)) {
        return {std::move(parent_fingerprint), std::move(chain)};
    }

    if (data.size() == BIP32_EXTKEY_SIZE + std::size(BASE58_MAINNET_PRIV_PREFIX) &&
            std::equal(std::begin(BASE58_MAINNET_PRIV_PREFIX), std::end(BASE58_MAINNET_PRIV_PREFIX), data.begin())) {
        chain = "mainnet";
        parent_fingerprint = HexStr(MakeSpan(data).subspan(1, 4));
    }

    if (data.size() == BIP32_EXTKEY_SIZE + std::size(BASE58_TESTNET_PRIV_PREFIX) &&
            std::equal(std::begin(BASE58_TESTNET_PRIV_PREFIX), std::end(BASE58_TESTNET_PRIV_PREFIX), data.begin())) {
        chain = "testnet";
        parent_fingerprint = HexStr(MakeSpan(data).subspan(1, 4));
    }

    if (!data.empty()) {
        memory_cleanse(data.data(), data.size());
    }
    return {std::move(parent_fingerprint), std::move(chain)};
}

VerifyTapsignerBackupResult verifyTapsignerBackup(const QByteArray &backupData, const QString &decryptionKey)
{
    static constexpr unsigned char xprv[] = {'x', 'p', 'r', 'v'};
    static constexpr unsigned char tprv[] = {'t', 'p', 'r', 'v'};

    static const QRegExp reg(R"(^[0-9A-Fa-f]{32}$)");
    if (!reg.exactMatch(decryptionKey)) {
        return VerifyTapsignerBackupResult{{}, "Invalid Backup Password. The Backup Password must have exactly 32 hexadecimal characters."};
    }

    const QByteArray key = QByteArray::fromHex(decryptionKey.toLocal8Bit());

    std::string decrypted = AES128CTRDecrypt(backupData.begin(), backupData.end(), key.begin(), key.end());
    if (!std::equal(std::begin(xprv), std::end(xprv), std::begin(decrypted)) &&
            !std::equal(std::begin(tprv), std::end(tprv), std::begin(decrypted))) {
        return VerifyTapsignerBackupResult{{}, "Invalid Backup Password or corrupted backup file"};
    }

    auto sp = QString::fromStdString(decrypted).split('\n');
    if (sp.isEmpty()) {
        return VerifyTapsignerBackupResult{{}, "Corrupted backup file"};
    }

    if (auto [fingerprint, chain] = getKeyFingerPrint(sp[0].toStdString()); fingerprint.empty()) {
        return VerifyTapsignerBackupResult{{}, "Invalid Backup Password or corrupted backup file"};
    } else {
        return VerifyTapsignerBackupResult{QString::fromStdString(fingerprint), {}, QString::fromStdString(chain)};
    }
}
}

