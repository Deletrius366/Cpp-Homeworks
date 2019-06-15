#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "huffman.h"
#include "reader.h"

class HuffmanArchiver {

public:

    // HuffmanArchiver(const char *infile, const char *outfile);

    HuffmanArchiver() = default;

    // explicit HuffmanArchiver(std::map<char, int> &m);

    void archiving(Reader& reader, Writer& writer);

    void unzipping(Reader& reader, Writer& writer);

    void get_stat();

    std::map<char, int> get_map();

    std::map<char, std::vector<bool>> get_table();

private:

    void encode(Reader& reader, Writer& writer);

    void print_table(Writer &outfile);

    void read_table(Reader &infile);

    void decode(const std::shared_ptr<TreeNode> &root, Reader &infile, Writer &outfile);

    void create_table(Reader& reader, Writer& writer);

    void build_table(std::shared_ptr<TreeNode> root, std::vector<bool> &code);

    // FileReader reader;
    // FileWriter writer;
    // const char *infile{};
    // const char *outfile{};
    std::map<char, int> map;
    std::map<char, std::vector<bool>> table;
    int size_infile = 0;
    int size_outfile = 0;
    int size_table = 0;
};


#endif