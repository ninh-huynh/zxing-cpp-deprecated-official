/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_QRCODE_H
#define ZXING_QRCODE_H

#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include <zxing/qrcode/Version.h>
#include <zxing/qrcode/decoder/Mode.h>
#include <zxing/qrcode/encoder/ByteMatrix.h>

#include <memory>

namespace zxing {
    namespace qrcode {
        class QRCode final {
        private:
            Mode* mode;
            ErrorCorrectionLevel* ecLevel;
            Version* version;
            int maskPattern;
            std::shared_ptr<ByteMatrix> matrix;

        public:
            static const int NUM_MASK_PATTERNS;

            QRCode();

            Mode *getMode() const;

            void setMode(Mode *value);

            ErrorCorrectionLevel *getEcLevel() const;

            void setEcLevel(ErrorCorrectionLevel *value);

            Version *getVersion() const;

            void setVersion(Version *version);

            int getMaskPattern() const;

            void setMaskPattern(int value);

            std::shared_ptr<ByteMatrix> getMatrix() const;

            void setMatrix(std::shared_ptr<ByteMatrix> value);

            static bool isValidMaskPattern(int maskPattern);
        };
    }
}


#endif //ZXING_QRCODE_H
