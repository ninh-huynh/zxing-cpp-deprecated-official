/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_MASKUTIL_H
#define ZXING_MASKUTIL_H

#include <zxing/qrcode/encoder/ByteMatrix.h>

#include <memory>

namespace zxing {
    namespace qrcode {

        class MaskUtil final {
        private:
            static int N1;
            static int N2;
            static int N3;
            static int N4;

            MaskUtil() = default;

            static bool isWhiteHorizontal(const int8_t* rowArray, int from, int to, int rowArraySize);

            static bool isWhiteVertical(const int8_t* array, int col, int from, int to, int row_stride, int arraySize);

            static int applyMaskPenaltyRule1Internal(std::shared_ptr<ByteMatrix> matrix, bool isHorizontal);

        public:
            static int applyMaskPenaltyRule1(std::shared_ptr<ByteMatrix> matrix);

            static int applyMaskPenaltyRule2(std::shared_ptr<ByteMatrix> matrix);

            static int applyMaskPenaltyRule3(std::shared_ptr<ByteMatrix> matrix);

            static int applyMaskPenaltyRule4(std::shared_ptr<ByteMatrix> matrix);

            static bool getDataMaskBit(int maskPattern, int x, int y);
        };
    }
}


#endif //ZXING_MASKUTIL_H
