/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_WRITEREXCEPTION_H
#define ZXING_WRITEREXCEPTION_H

#include <zxing/Exception.h>

namespace zxing {
    class WriterException: public Exception {
    public:
        WriterException() throw() {}
        WriterException(char const* msg) throw(): Exception(msg) {}
        ~WriterException() throw() {}
    };
}

#endif //ZXING_WRITEREXCEPTION_H
