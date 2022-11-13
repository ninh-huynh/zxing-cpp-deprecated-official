/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "ByteMatrix.h"

namespace zxing {
    namespace qrcode {

        ByteMatrix::ByteMatrix(int width, int height)
                : width(width), height(height), bytes(width * height) {}

        int ByteMatrix::getWidth() const {
            return width;
        }

        int ByteMatrix::getHeight() const {
            return height;
        }

        int8_t ByteMatrix::get(int x, int y) const {
            return bytes[y * getWidth() + x];
        }

        const std::vector<int8_t> &ByteMatrix::getArray() const {
            return bytes;
        }

        void ByteMatrix::set(int x, int y, int8_t value) {
            bytes[y * width + x] = value;
        }

        void ByteMatrix::set(int x, int y, int value) {
            this->set(x, y, (int8_t) value);
        }

        void ByteMatrix::set(int x, int y, bool value) {
            this->set(x, y, (int8_t) (value ? 1 : 0));
        }

        void ByteMatrix::clear(int8_t value) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    bytes[y * width + x] = value;
                }
            }
        }
    }
}
