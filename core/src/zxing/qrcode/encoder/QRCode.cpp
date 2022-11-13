/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "QRCode.h"

namespace zxing {
    namespace qrcode {

        const int QRCode::NUM_MASK_PATTERNS = 8;

        QRCode::QRCode()
        : mode(nullptr), ecLevel(nullptr), version(nullptr), maskPattern(-1), matrix() {}

        Mode *QRCode::getMode() const {
            return mode;
        }

        void QRCode::setMode(Mode *value) {
            this->mode = value;
        }

        ErrorCorrectionLevel *QRCode::getEcLevel() const {
            return ecLevel;
        }

        void QRCode::setEcLevel(ErrorCorrectionLevel *value) {
            this->ecLevel = value;
        }

        Version *QRCode::getVersion() const {
            return version;
        }

        void QRCode::setVersion(Version *version) {
            this->version = version;
        }

        int QRCode::getMaskPattern() const {
            return maskPattern;
        }

        void QRCode::setMaskPattern(int value) {
            this->maskPattern = value;
        }

        std::shared_ptr<ByteMatrix> QRCode::getMatrix() const {
            return matrix;
        }

        void QRCode::setMatrix(std::shared_ptr<ByteMatrix> value) {
            this->matrix = value;
        }

        bool QRCode::isValidMaskPattern(int maskPattern) {
            return maskPattern >= 0 && maskPattern < NUM_MASK_PATTERNS;
        }
    }
}
