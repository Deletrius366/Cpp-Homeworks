#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>
#include "HuffmanArchiver.h"
#include "test.h"

int main(int argc, char **argv) {
    // unit_test();
    // return 0;
    bool error = false;
    if (argc > 5) {
        const char* infile = nullptr;
        const char* outfile = nullptr;
        if (!strcmp(argv[2], "-i") || !strcmp(argv[2], "--input")) {
            infile = argv[3];
        } else {
            error = true;
        }
        if (!strcmp(argv[4], "-o") || !strcmp(argv[4], "--output")) {
            outfile = argv[5];
        } else {
            error = true;
        }
        if (!strcmp(argv[1], "-a")) {
            try {
                HuffmanArchiver HuffArch(infile, outfile);
                HuffArch.archiving();
                HuffArch.get_stat();
            } catch (HuffException &e) {
                std::cout << e.get() << std::endl;
            }
        }
        if (!strcmp(argv[1], "-u")) {
            try {
                HuffmanArchiver HuffArch(infile, outfile);
                HuffArch.unzipping();
                HuffArch.get_stat();
            } catch (HuffException &e) {
                std::cout << e.get() << std::endl;
            }
        }

        if ((strcmp(argv[1], "-a") != 0) && (strcmp(argv[1], "-u") != 0)) {
            error = true;
        }

    } else {
        error = true;
    }

    if (error) {
        std::cout << "bad input parameters";
    }
    return 0;
}