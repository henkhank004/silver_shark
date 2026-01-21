#pragma once

#include <string>

namespace err {
    enum ErrorCode {
        OK = 0,
        INCORRECT_TYPE,
        FILE_LOAD_FAILED,
        JSON_PARSE_FAILED,
        ITEM_FIELD_MISSING,
        RECIPE_FIELD_MISSING,
        OUT_OF_BOUNDS
    };

    struct Error {
        ErrorCode code;
        std::string msg;
    };
}