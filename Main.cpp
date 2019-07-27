#include <cstdio>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include <getopt.h>

#include "Param.h"
#include "WikiParser.h"

static constexpr struct option longopts[] = {
    { "japanese", no_argument, nullptr, 'j' },
    { 0,                    0,       0,  0  },
};

static void usage() noexcept {
    std::printf(
        "Usage: wikilead \n"
        " -j, --japanese Access to japanese version.\n"
    );        

    return; 
}

static int parseCommandLine(int argc, char** argv, Param& param) noexcept {
    int opt = 0, longIndex = 0;
    while ((opt = getopt_long(argc, argv, ":j", longopts, &longIndex)) != -1) {
        switch (opt) {
        case 'j': { param.lang = Lang::JP; break; }
        default:  { 
            std::fprintf(stderr, "Invalid option '%c'\n", opt);
            return -1;
        }
        }
    }    

    if (argc <= optind) {
        usage();
        return -1;
    } else {
        param.word = argv[optind];
    }

    return 0;
}

int main(int argc, char** argv) {
    Param param;
    if (parseCommandLine(argc, argv, param) != 0) {
        return -1;
    }

    WikiParser wikiParser;    
    if (wikiParser.parse(param) != 0) {
        return -1;
    }

    return 0;
}

