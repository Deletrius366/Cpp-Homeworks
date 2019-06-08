#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "huffman.h"

class HuffmanArchiver {

public:

    struct Reader {
        std::ifstream in;

        explicit Reader(const char* filename) : in(filename, std::ios::in | std::ios::binary){
            if (!in) {
                throw HuffException ("file not open");
            }
        };

        void read(char* ch, size_t size) {in.read(ch, size);}

        bool eof() {return in.eof();}

        bool valid() { return in.rdstate();}

    };

    struct Writer {
        std::ofstream out;

        explicit Writer(const char* filename) : out(filename, std::ios::out | std::ios::binary){
            if (!out) {
                throw HuffException ("file not open");
            }
        };

        void write(char ch) {out << ch;}

        void write(char * ch, size_t size) {out.write(ch, size);}

    };

    HuffmanArchiver(const char *infile, const char *outfile);

    HuffmanArchiver() = default;

    // explicit HuffmanArchiver(std::map<char, int> &m);

    void encode();

    void print_table(Writer &outfile);

    void read_table(Reader &infile);

    void decode(const std::shared_ptr<TreeNode> &root, Reader &infile, Writer &outfile);

    void create_table();

    void build_table(std::shared_ptr<TreeNode> root, std::vector<bool> &code);

    void archiving();

    void unzipping();

    void get_stat();

    std::map<char, int> get_map();

    std::map<char, std::vector<bool>> get_table();

private:
    Reader reader;
    Writer writer;
    // const char *infile{};
    // const char *outfile{};
    std::map<char, int> map;
    std::map<char, std::vector<bool>> table;
    int size_infile = 0;
    int size_outfile = 0;
    int size_table = 0;
};


#endif