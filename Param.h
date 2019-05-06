#ifndef PARAM_H
#define PARAM_H

#include <cstdint>

enum Lang : uint8_t {
    EN,
    JP
};

struct Param {
    Param() 
      : lang(Lang::EN)
    {}

    Lang        lang;
    std::string word;
};

#endif
