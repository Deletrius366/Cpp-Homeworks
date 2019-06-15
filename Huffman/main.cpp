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
#include "reader.h"

struct FileReader : Reader {
    std::ifstream in;

    explicit FileReader(const char* filename) : in(filename, std::ios::in | std::ios::binary){
        if (!in) {
            throw HuffException ("file not open");
        }
    };
    void read(char* ch, size_t size) {in.read(ch, size);}

    bool eof() {return in.eof();}

    bool valid() { return in.rdstate();}

    void reopen() {in.clear();
        in.seekg(0, std::ios::beg);}

};

struct FileWriter : Writer {
    std::ofstream out;

    explicit FileWriter(const char* filename) : out(filename, std::ios::out | std::ios::binary){
        if (!out) {
            throw HuffException ("file not open");
        }
    };

    void write(char ch) {out << ch;}

    void write(char * ch, size_t size) {out.write(ch, size);}

};

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
                HuffmanArchiver HuffArch;
                FileReader reader(infile);
                FileWriter writer(outfile);

                HuffArch.archiving(reader, writer);
                HuffArch.get_stat();
            } catch (HuffException &e) {
                std::cout << e.get() << std::endl;
            }
        }
        if (!strcmp(argv[1], "-u")) {
            try {
                HuffmanArchiver HuffArch;
                FileReader reader(infile);
                FileWriter writer(outfile);

                HuffArch.unzipping(reader, writer);
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