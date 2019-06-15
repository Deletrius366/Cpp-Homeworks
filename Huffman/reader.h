#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>

#ifndef HUFFMAN_READER_H
#define HUFFMAN_READER_H

struct Reader {
    virtual void read(char* ch, size_t size) = 0;

    virtual bool eof() = 0;

    virtual bool valid() = 0;

    virtual void reopen() = 0;
};






//struct FileReader : Reader {
//    std::ifstream in;
//
//    explicit FileReader(const char* filename) : in(filename, std::ios::in | std::ios::binary){
//        if (!in) {
//            throw HuffException ("file not open");
//        }
//    };
//    void read(char* ch, size_t size) {in.read(ch, size);}
//
//    bool eof() {return in.eof();}
//
//    bool valid() { return in.rdstate();}
//
//    void reopen() {in.clear();
//        in.seekg(0, std::ios::beg);}
//
//};

struct Writer {
    virtual void write(char ch) = 0;

    virtual void write(char* ch, size_t size) = 0;
};

//struct FileWriter : Writer {
//    std::ofstream out;
//
//    explicit FileWriter(const char* filename) : out(filename, std::ios::out | std::ios::binary){
//        if (!out) {
//            throw HuffException ("file not open");
//        }
//    };
//
//    void write(char ch) {out << ch;}
//
//    void write(char * ch, size_t size) {out.write(ch, size);}
//
//};



#endif //HUFFMAN_READER_H
