/*
 * Created by Ninh Huynh on 11/14/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include <zxing/Writer.h>
#include <zxing/qrcode/QRCodeWriter.h>
#include <zxing/common/StringUtils.h>
#include <memory>

#include <iostream>

#include <ZXingVersion.h>

using namespace zxing;

int main(int argc, char **argv) {
    std::cout << "ZXing Version " << ZXing_VERSION_MAJOR << "." << ZXing_VERSION_MINOR << "." << ZXing_VERSION_PATCH << std::endl;
    std::unique_ptr<Writer> writer(new qrcode::QRCodeWriter());

    std::string content_str = "this is a secret message";
    EncodeHints hints;
    hints.put(EncodeHintType::CHARACTER_SET, common::StringUtils::UTF8);
    hints.put(EncodeHintType::MARGIN, "2");
    hints.put(EncodeHintType::ERROR_CORRECTION, "M");

    Ref<BitMatrix> matrix;

    try {
        matrix = writer->encode(std::vector<char>(content_str.begin(), content_str.end()),
                                BarcodeFormat::QR_CODE,
                                300,
                                300,
                                &hints);
    } catch (const std::exception &e) {
        std::cout << "Exception occur during encode: " << e.what() << std::endl;
    }

    if (matrix != nullptr) {
        std::vector<uint8_t> image_data(matrix->getWidth() * matrix->getHeight(), 0);
        int row_stride = matrix->getWidth();

        for (int i = 0; i < matrix->getHeight(); i++) {
            for (int j = 0; j < matrix->getWidth(); j++) {
                if (matrix->get(j, i) == 0) {
                    image_data[i * row_stride + j] = 255;
                } else {
                    image_data[i * row_stride + j] = 0;
                }
            }
        }

        stbi_write_jpg("qr_output.jpg", matrix->getWidth(), matrix->getHeight(), 1, image_data.data(), 90);
        std::cout << "Encode \"" << content_str << "\" to qr_output.jpg successfully!" << std::endl;
    }

    return 0;
}
