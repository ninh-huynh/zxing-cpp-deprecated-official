/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_REEDSOLOMONENCODER_H
#define ZXING_REEDSOLOMONENCODER_H

#include <vector>
#include <zxing/common/Counted.h>
#include <zxing/common/Array.h>
#include <zxing/common/reedsolomon/GenericGFPoly.h>
#include <zxing/common/reedsolomon/GenericGF.h>


namespace zxing {

    class ReedSolomonEncoder {
    private:
        Ref<GenericGF> field;
        std::vector<Ref<GenericGFPoly>> cachedGenerators;

        Ref<GenericGFPoly> buildGenerator(int degree);
    public:
        ReedSolomonEncoder(Ref<GenericGF> field);

        void encode(ArrayRef<int> toEncode, int ecBytes);

    };
}


#endif //ZXING_REEDSOLOMONENCODER_H
