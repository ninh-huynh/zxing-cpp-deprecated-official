/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_WRITER_H
#define ZXING_WRITER_H

#include <zxing/common/BitMatrix.h>
#include <zxing/BarcodeFormat.h>
#include <zxing/EncodeHints.h>
#include <vector>

namespace zxing {
    class Writer {
    protected:
        Writer() = default;

    public:
        virtual Ref<BitMatrix> encode(
                const std::vector<char> &contents,
                BarcodeFormat format,
                int width,
                int height);

        virtual Ref<BitMatrix> encode(
                const std::vector<char> &contents,
                BarcodeFormat format,
                int width,
                int height,
                EncodeHints *hints) = 0;

        virtual ~Writer() = default;
    };
}


#endif //ZXING_WRITER_H
