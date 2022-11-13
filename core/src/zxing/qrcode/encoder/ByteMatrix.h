/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_BYTEMATRIX_H
#define ZXING_BYTEMATRIX_H

#include<zxing/common/Counted.h>
#include<vector>

namespace zxing {
    namespace qrcode {
        class ByteMatrix final {
        private:
            std::vector<int8_t> bytes;
            int width;
            int height;

        public:
            ByteMatrix(int width, int height);

            int getWidth() const;

            int getHeight() const;

            int8_t get(int x, int y) const;

            const std::vector<int8_t>& getArray() const;

            void set(int x, int y, int8_t value);

            void set(int x, int y, int value);

            void set(int x, int y, bool value);

            void clear(int8_t value);

        };
    }
}


#endif //ZXING_BYTEMATRIX_H
