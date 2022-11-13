/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_QRCODEWRITER_H
#define ZXING_QRCODEWRITER_H

#include <zxing/Writer.h>
#include <zxing/qrcode/encoder/QRCode.h>
#include <memory>

namespace zxing {
    namespace qrcode {
        class QRCodeWriter : public Writer {
        private:
            static int QUIET_ZONE_SIZE;

            static Ref<BitMatrix> renderResult(
                    std::shared_ptr<QRCode> code,
                    int width,
                    int height,
                    int quietZone);

        public:
            Ref<BitMatrix>
            encode(const std::vector<char> &contents,
                   BarcodeFormat format,
                   int width,
                   int height,
                   EncodeHints *hints) override;
        };
    }
}


#endif //ZXING_QRCODEWRITER_H
