/*
 * Created by Ninh Huynh on 11/13/2022.
 *
 * Copyright 2008 ZXing authors.
 * Copyright 2022 Ninh Huynh.
 */

#include "EncodeHints.h"

namespace zxing {

    EncodeHints::EncodeHints() : hints() {}

    std::string EncodeHints::get(EncodeHintType key) const {
        std::string val;

        auto it = hints.find(key);
        if (it != hints.end()) {
            val = it->second;
        }

        return val;
    }

    bool EncodeHints::containsKey(EncodeHintType key) const {
        auto it = hints.find(key);
        return it != hints.end();
    }

    void EncodeHints::put(EncodeHintType key, const std::string &val) {
        hints[key] = val;
    }


}
