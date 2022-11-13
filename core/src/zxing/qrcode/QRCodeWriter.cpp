/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "QRCodeWriter.h"

#include <zxing/common/IllegalArgumentException.h>
#include <zxing/IllegalStateException.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include <zxing/qrcode/encoder/Encoder.h>
#include <algorithm>

namespace zxing {
    namespace qrcode {

        int QRCodeWriter::QUIET_ZONE_SIZE = 4;

        Ref<BitMatrix>
        QRCodeWriter::encode(const std::vector<char> &contents, BarcodeFormat format, int width,
                             int height, EncodeHints *hints) {
            if (contents.empty()) {
                throw IllegalArgumentException("Found empty contents");
            }

            if (format != BarcodeFormat::QR_CODE) {
                throw IllegalArgumentException("Can only encode QR_CODE, but got "/* + format*/);
            }

            if (width < 0 || height < 0) {
                throw IllegalArgumentException("Requested dimensions are too small: "/* + width + 'x' +
                                                   height*/);
            }

            ErrorCorrectionLevel errorCorrectionLevel = ErrorCorrectionLevel::L;
            int quietZone = QUIET_ZONE_SIZE;
            if (hints != nullptr) {
                auto eclStr = hints->get(EncodeHintType::ERROR_CORRECTION);
                if (!eclStr.empty()) {
                    errorCorrectionLevel = ErrorCorrectionLevel::fromString(eclStr);
                }

                auto marginStr = hints->get(EncodeHintType::MARGIN);
                if (!marginStr.empty()) {
                    quietZone = std::stoi(marginStr);
                }
            }

            std::shared_ptr<QRCode> code = Encoder::encode(contents, &errorCorrectionLevel, hints);
            return renderResult(code, width, height, quietZone);
        }

        // Note that the input matrix uses 0 == white, 1 == black, while the output matrix uses
        // 0 == black, 255 == white (i.e. an 8 bit greyscale bitmap).
        Ref<BitMatrix>
        QRCodeWriter::renderResult(std::shared_ptr<QRCode> code, int width, int height,
                                   int quietZone) {
            std::shared_ptr<ByteMatrix> input = code->getMatrix();
            if (input == nullptr) {
                throw IllegalStateException();
            }
            int inputWidth = input->getWidth();
            int inputHeight = input->getHeight();
            int qrWidth = inputWidth + (quietZone << 1);
            int qrHeight = inputHeight + (quietZone << 1);
            int outputWidth = std::max(width, qrWidth);
            int outputHeight = std::max(height, qrHeight);

            int multiple = std::min(outputWidth / qrWidth, outputHeight / qrHeight);
            // Padding includes both the quiet zone and the extra white pixels to accommodate the requested
            // dimensions. For example, if input is 25x25 the QR will be 33x33 including the quiet zone.
            // If the requested size is 200x160, the multiple will be 4, for a QR of 132x132. These will
            // handle all the padding from 100x100 (the actual QR) up to 200x160.
            int leftPadding = (outputWidth - (inputWidth * multiple)) / 2;
            int topPadding = (outputHeight - (inputHeight * multiple)) / 2;

            Ref<BitMatrix> output(new BitMatrix(outputWidth, outputHeight));

            for (int inputY = 0, outputY = topPadding;
                 inputY < inputHeight; inputY++, outputY += multiple) {
                // Write the contents of this row of the barcode
                for (int inputX = 0, outputX = leftPadding;
                     inputX < inputWidth; inputX++, outputX += multiple) {
                    if (input->get(inputX, inputY) == 1) {
                        output->setRegion(outputX, outputY, multiple, multiple);
                    }
                }
            }

            return output;
        }
    }
}
