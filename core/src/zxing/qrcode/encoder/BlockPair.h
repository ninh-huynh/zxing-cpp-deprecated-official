/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_BLOCKPAIR_H
#define ZXING_BLOCKPAIR_H

#include <vector>

#include <zxing/common/Array.h>

namespace zxing {
    namespace qrcode {
        class BlockPair {
        private:
            ArrayRef<int8_t> dataBytes;
            ArrayRef<int8_t> errorCorrectionBytes;

        public:
            BlockPair(ArrayRef<int8_t> dataBytes,
                      ArrayRef<int8_t> errorCorrectionBytes);

            ArrayRef<int8_t> getDataBytes() const;

            ArrayRef<int8_t> getErrorCorrectionBytes() const;
        };
    }
}


#endif //ZXING_BLOCKPAIR_H
