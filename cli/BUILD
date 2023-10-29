load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "zxing-reader",
    srcs = [
        "src/ImageReaderSource.cpp",
        "src/ImageReaderSource.h",
        "src/jpgd.cpp",
        "src/jpgd.h",
        "src/lodepng.cpp",
        "src/lodepng.h",
        "src/main.cpp",
    ],
    deps = [
        "//core:zxing-cpp",
    ],
)

cc_binary(
    name = "zxing-writer",
    srcs = [
        "src/zxing_writer_cli.cpp",
        "src/stb_image_write.h",
    ],
    deps = [
        "//core:zxing-cpp",
    ],
)