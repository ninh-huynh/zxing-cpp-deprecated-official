/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_MATRIXUTIL_H
#define ZXING_MATRIXUTIL_H

#include <zxing/qrcode/encoder/ByteMatrix.h>
#include <zxing/common/BitArray.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include <zxing/qrcode/Version.h>

#include <array>

namespace zxing {
    namespace qrcode {
        class MatrixUtil final {
        private:
            MatrixUtil() = default;

            static std::array<std::array<int, 7>, 7> POSITION_DETECTION_PATTERN;
            static std::array<std::array<int, 5>, 5> POSITION_ADJUSTMENT_PATTERN;
            static std::array<std::array<int, 7>, 40> POSITION_ADJUSTMENT_PATTERN_COORDINATE_TABLE;
            static std::array<std::array<int, 2>, 15> TYPE_INFO_COORDINATES;

            static int VERSION_INFO_POLY;
            static int TYPE_INFO_POLY;
            static int TYPE_INFO_MASK_PATTERN;

            static bool isEmpty(int value);

            static void embedTimingPatterns(std::shared_ptr<ByteMatrix> matrix);

            static void embedDarkDotAtLeftBottomCorner(std::shared_ptr<ByteMatrix> matrix);

            static void embedHorizontalSeparationPattern(int xStart, int yStart, std::shared_ptr<ByteMatrix> matrix);

            static void embedVerticalSeparationPattern(int xStart, int yStart, std::shared_ptr<ByteMatrix> matrix);

            static void embedPositionAdjustmentPattern(int xStart, int yStart, std::shared_ptr<ByteMatrix> matrix);

            static void embedPositionDetectionPattern(int xStart, int yStart, std::shared_ptr<ByteMatrix> matrix);

            static void embedPositionDetectionPatternsAndSeparators(std::shared_ptr<ByteMatrix> matrix);

            static void maybeEmbedPositionAdjustmentPatterns(Version* version, std::shared_ptr<ByteMatrix> matrix);
        public:
            static void clearMatrix(std::shared_ptr<ByteMatrix> matrix);

            static void buildMatrix(Ref<BitArray> dataBits,
                                    ErrorCorrectionLevel* ecLevel,
                                    Version* version,
                                    int maskPattern,
                                    std::shared_ptr<ByteMatrix> matrix);

            static void embedBasicPatterns(Version* version, std::shared_ptr<ByteMatrix> matrix);

            static void embedTypeInfo(ErrorCorrectionLevel* ecLevel, int maskPattern, std::shared_ptr<ByteMatrix> matrix);

            static void maybeEmbedVersionInfo(Version* version, std::shared_ptr<ByteMatrix> matrix);

            static void embedDataBits(Ref<BitArray> dataBits, int maskPattern, std::shared_ptr<ByteMatrix> matrix);

            static int findMSBSet(int value);

            static int calculateBCHCode(int value, int poly);

            static void makeTypeInfoBits(ErrorCorrectionLevel* ecLevel, int maskPattern, Ref<BitArray> bits);

            static void makeVersionInfoBits(Version* version, Ref<BitArray> bits);


        };
    }
}


#endif //ZXING_MATRIXUTIL_H
