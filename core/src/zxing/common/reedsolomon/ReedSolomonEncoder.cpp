/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "ReedSolomonEncoder.h"
#include <zxing/common/IllegalArgumentException.h>

namespace zxing {
    ReedSolomonEncoder::ReedSolomonEncoder(zxing::Ref<zxing::GenericGF> field)
            : field(field), cachedGenerators() {

        ArrayRef<int> tempIntArr(1);
        tempIntArr[0] = 1;

        cachedGenerators.push_back(Ref<GenericGFPoly>(new GenericGFPoly(*field, tempIntArr)));
    }

    Ref<GenericGFPoly> ReedSolomonEncoder::buildGenerator(int degree) {
        if (degree >= cachedGenerators.size()) {
            Ref<GenericGFPoly> lastGenerator = cachedGenerators.at(cachedGenerators.size() - 1);
            for (int d = cachedGenerators.size(); d <= degree; d++) {
                ArrayRef<int> tempIntArr(2);
                tempIntArr[0] = 1;
                tempIntArr[1] = field->exp(d - 1 + field->getGeneratorBase());

                Ref<GenericGFPoly> nextGenerator = lastGenerator->multiply(
                        Ref<GenericGFPoly>(new GenericGFPoly(*field, tempIntArr))
                );

                cachedGenerators.push_back(nextGenerator);
                lastGenerator = nextGenerator;
            }
        }
        return cachedGenerators.at(degree);
    }

    void ReedSolomonEncoder::encode(ArrayRef<int> toEncode, int ecBytes) {
        if (ecBytes == 0) {
            throw IllegalArgumentException("No error correction bytes");
        }

        int dataBytes = toEncode->size() - ecBytes;
        if (dataBytes <= 0) {
            throw IllegalArgumentException("No data bytes provided");
        }

        Ref<GenericGFPoly> generator = buildGenerator(ecBytes);
        ArrayRef<int> infoCoefficients(dataBytes);
        memcpy(&infoCoefficients[0], &toEncode[0], sizeof(int) * dataBytes);
        Ref<GenericGFPoly> info(new GenericGFPoly(*field, infoCoefficients));
        info = info->multiplyByMonomial(ecBytes, 1);
        Ref<GenericGFPoly> remainder = info->divide(generator)[1];
        ArrayRef<int> coefficients = remainder->getCoefficients();
        int numZeroCoefficients = ecBytes - coefficients->size();
        for (int i = 0; i < numZeroCoefficients; i++) {
            toEncode[dataBytes + i] = 0;
        }

        memcpy(&toEncode[dataBytes + numZeroCoefficients],
               &coefficients[0],
               sizeof(int) * coefficients->size());
    }


}

