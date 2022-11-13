/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#ifndef ZXING_ENCODER_H
#define ZXING_ENCODER_H

#include <zxing/qrcode/encoder/ByteMatrix.h>
#include <zxing/qrcode/encoder/QRCode.h>
#include <zxing/qrcode/decoder/Mode.h>
#include <zxing/common/CharacterSetECI.h>
#include <zxing/EncodeHints.h>


#include <array>
#include <string>

namespace zxing {
    namespace qrcode {
        class Encoder final {
        private:
            static std::array<int, 96> ALPHANUMERIC_TABLE;

            Encoder() = default;

            static int calculateMaskPenalty(std::shared_ptr<ByteMatrix> matrix);

            static Mode* chooseMode(const std::vector<char> &content, std::string encoding);

            static bool isOnlyDoubleByteKanji(const std::vector<char> &content);

            static int chooseMaskPattern(Ref<BitArray> bits,
                                         ErrorCorrectionLevel* ecLevel,
                                         Version* version,
                                         std::shared_ptr<ByteMatrix> matrix);

            static Version* chooseVersion(int numInputBits, ErrorCorrectionLevel* ecLevel);

            static void appendECI(common::CharacterSetECI* eci, Ref<BitArray> bits);

        public:
            static std::string DEFAULT_BYTE_MODE_ENCODING;


            static std::unique_ptr<QRCode> encode(
                    const std::vector<char> &content, ErrorCorrectionLevel *ecLevel
            );

            static std::unique_ptr<QRCode> encode(
                    const std::vector<char> &content, ErrorCorrectionLevel *ecLevel,
                    EncodeHints* hints
            );

            static int getAlphanumericCode(int code);

            static Mode* chooseMode(const std::vector<char> &content);

            static void terminateBits(int numDataBytes, Ref<BitArray> bits);

            static void getNumDataBytesAndNumECBytesForBlockID(int numTotalBytes,
                                                                 int numDataBytes,
                                                                 int numRSBlocks,
                                                                 int blockID,
                                                                 ArrayRef<int> numDataBytesInBlock,
                                                                 ArrayRef<int> numECBytesInBlock);


            static Ref<BitArray> interleaveWithECBytes(Ref<BitArray> bits,
                                                       int numTotalBytes,
                                                       int numDataBytes,
                                                       int numRSBlocks);

            static ArrayRef<int8_t> generateECBytes(ArrayRef<int8_t> dataBytes, int numEcBytesInBlock);

            static void appendModeInfo(Mode* mode, Ref<BitArray> bits);

            static void appendLengthInfo(int numLetters, Version* version, Mode* mode, Ref<BitArray> bits);

            static void appendBytes(const std::vector<char> &content, Mode* mode, Ref<BitArray> bits, std::string encoding);

            static void appendNumericBytes(const std::vector<char> &content, Ref<BitArray> bits);

            static void appendAlphanumericBytes(const std::vector<char> &content, Ref<BitArray> bits);

            static void append8BitBytes(const std::vector<char> &content, Ref<BitArray> bits, std::string encoding);

            static void appendKanjiBytes(const std::vector<char> &content, Ref<BitArray> bits);


        };
    }
}


#endif //ZXING_ENCODER_H
