#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "huffman.h"
#include "reader.h"

class HuffmanArchiver {

public:

    /*struct Reader {
        virtual void read(char* ch, size_t size) = 0;

        virtual bool eof() = 0;

        virtual bool valid() = 0;
    };

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

    };

    struct Writer {
        virtual void write(char ch) = 0;

        virtual void write(char* ch, size_t size) = 0;
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

    };*/

    // HuffmanArchiver(const char *infile, const char *outfile);

    HuffmanArchiver() = default;

    // explicit HuffmanArchiver(std::map<char, int> &m);

    void encode(Reader& reader, Writer& writer);

    void print_table(Writer &outfile);

    void read_table(Reader &infile);

    void decode(const std::shared_ptr<TreeNode> &root, Reader &infile, Writer &outfile);

    void create_table(Reader& reader, Writer& writer);

    void build_table(std::shared_ptr<TreeNode> root, std::vector<bool> &code);

    void archiving(Reader& reader, Writer& writer);

    void unzipping(Reader& reader, Writer& writer);

    void get_stat();

    std::map<char, int> get_map();

    std::map<char, std::vector<bool>> get_table();

private:
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