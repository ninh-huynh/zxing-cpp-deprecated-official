/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "Writer.h"

namespace zxing {

    Ref<BitMatrix>
    Writer::encode(const std::vector<char> &contents, BarcodeFormat format, int width, int height) {
        return encode(contents, format, width, height, nullptr);
    }
}
