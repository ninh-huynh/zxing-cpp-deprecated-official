/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "BlockPair.h"

namespace zxing {
    namespace qrcode {

        BlockPair::BlockPair(ArrayRef<int8_t> dataBytes,
                             ArrayRef<int8_t> errorCorrectionBytes)
                : dataBytes(dataBytes), errorCorrectionBytes(errorCorrectionBytes) {}

        ArrayRef<int8_t> BlockPair::getDataBytes() const {
            return dataBytes;
        }

        ArrayRef<int8_t> BlockPair::getErrorCorrectionBytes() const {
            return errorCorrectionBytes;
        }

    }
}

