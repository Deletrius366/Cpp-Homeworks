#include "HuffmanArchiver.h"
#include "reader.h"

const int bit_in_byte = 8;

// HuffmanArchiver::HuffmanArchiver() = default;;

//HuffmanArchiver::HuffmanArchiver(std::map<char, int> &map_) {
//    map = map_;
//}

void set_bit(char &byte, int i, int j) {
    byte = byte | j << (bit_in_byte - 1 - i);
}

bool get_bit(char &byte, int i) {
    return byte & (1 << (bit_in_byte - 1 - i));
}

void print_one_char(char &buf, int &count,  Writer &out, int &size_outfile, int j) {
    set_bit(buf, count, j);
    count++;
    if (count == bit_in_byte) {
        count = 0;
        out.write(buf);
        size_outfile++;
        buf = false;
    }
}

void print_residue(char &buf, int &count, Writer &out, int &size_outfile) {
    if (count != 0) {
        out.write(buf);
        size_outfile++;
    }
}

void HuffmanArchiver::encode(Reader& reader, Writer& writer) {
//    std::ifstream in(infile, std::ios::in | std::ios::binary);
//    if (!in) {
//        throw HuffException("file not open");
//    }
//    std::ofstream out(outfile, std::iRos::out | std::ios::binary);
//    if (!out) {
//        throw HuffException("file not open");
//    }
    // FileReader reader(infile);
    // FileWriter writer(outfile);
    reader.reopen();
    print_table(writer);
    int count = 0;
    char buf = 0;
    char ch = 0;
    if (map.size() == 1) {
        auto it = map.begin();
        for (int i = 0; i < it->second; i++) {
            print_one_char(buf, count, writer, size_outfile, 0);
        }
        print_residue(buf, count, writer, size_outfile);
        return;
    }
    if (!reader.eof()) {
        reader.read(&ch, sizeof(char));
    }

    while (!reader.eof()) {
        if (reader.valid())
            throw HuffException("illegal input");
        std::vector<bool> x = table[ch];
        for (auto &&i : x) {
            print_one_char(buf, count, writer, size_outfile, i);
        }
        reader.read(&ch, sizeof(char));
    }
    print_residue(buf, count, writer, size_outfile);

    // in.close();
    // out.close();
}

void HuffmanArchiver::print_table(Writer &out) {
    int size = map.size();
    out.write((char *) &size, sizeof(int));
    std::map<char, int>::iterator it;
    for (it = map.begin(); it != map.end(); it++) {
        out.write((char *) &it->first, sizeof(char));
        out.write((char *) &it->second, sizeof(int));
    }
}

int byte_from_bit(int bit) {
    return (bit + bit_in_byte - 1) / bit_in_byte;
}

void HuffmanArchiver::decode(const std::shared_ptr<TreeNode> &root, Reader &reader, Writer &out) {
    std::shared_ptr<TreeNode> node = root;
    int count = 0;
    char byte;
    int already_print = 0;

    if (map.size() == 1) {
        auto it = map.begin();
        for (int i = 0; i < it->second; i++) {
            out.write(it->first);
        }
        size_infile = byte_from_bit(map.begin()->second);
        return;
    }

    reader.read(&byte, sizeof(char));
    size_infile++;
    while (!reader.eof()) {
        if (reader.valid())
            throw HuffException("illegal input");
        bool bit = get_bit(byte, count);
        if (bit) {
            node = node->get_right();
        } else {
            node = node->get_left();
        }
        if (node->get_left() == nullptr && node->get_right() == nullptr) {
            out.write(node->get_ch());
            already_print++;
            if (already_print == size_outfile) {
                break;
            }
            node = root;
        }
        count++;
        if (count == bit_in_byte) {
            count = 0;
            reader.read(&byte, sizeof(char));
            size_infile++;
        }
    }
}

void HuffmanArchiver::create_table(Reader& reader, Writer& writer) {
//     std::ifstream in(infile, std::ios::in | std::ios::binary);
//    if (!in) {
//        throw HuffException("file not open");
//    }
    size_infile = 0;
    char ch = ' ';
    if (!reader.eof()) {
        reader.read(&ch, sizeof(char));
    }
    while (!reader.eof()) {
        if (reader.valid())
            throw HuffException("illegal input");
        map[ch]++;
        size_infile++;
        reader.read(&ch, sizeof(char));
    }
    // in.close();
}

void HuffmanArchiver::archiving(Reader& reader, Writer& writer) {
    try {
        create_table(reader, writer);
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }
    size_table = map.size();
    if (map.empty()) {
//        std::ofstream out(outfile, std::ios::out | std::ios::binary);
//        if (!out) {
//            throw HuffException("file not open");
//        }
        print_table(writer);
        return;
    }
    HuffTree tree;
    tree.init(map);
    try {
        tree.build();
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }
    std::shared_ptr<TreeNode> root = tree.root();
    std::vector<bool> code;
    build_table(root, code);
    try {
        encode(reader, writer);
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }

}

void HuffmanArchiver::build_table(std::shared_ptr<TreeNode> root, std::vector<bool> &code) {
    if (root->get_left() != nullptr) {
        code.push_back(false);
        build_table(root->get_left(), code);
    }

    if (root->get_right() != nullptr) {
        code.push_back(true);
        build_table(root->get_right(), code);
    }

    if (root->get_left() == nullptr && root->get_right() == nullptr) {
        table[root->get_ch()] = code;
    }
    if (!code.empty())
        code.pop_back();
}

void HuffmanArchiver::unzipping(Reader& reader, Writer& writer) {
//    std::ifstream in(infile, std::ios::in | std::ios::binary);
//    if (!in) {
//        throw HuffException("file not open");
//    }
//    std::ofstream out(outfile, std::ios::out | std::ios::binary);
//    if (!out) {
//        throw HuffException("file not open");
//    }
    read_table(reader);
    size_table = map.size();
    if (map.empty()) {
        return;
    }
    HuffTree tree;
    tree.init(map);
    try {
        tree.build();
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }
    std::shared_ptr<TreeNode> root = tree.root();
    decode(root, reader, writer);
    // out.close();
    // in.close();
}

void HuffmanArchiver::read_table(Reader & reader) {
    reader.read((char *) &size_table, sizeof(int));
    for (int i = 0; i < size_table; i++) {
        if (reader.valid())
            throw HuffException("illegal input");
        char ch;
        reader.read(&ch, sizeof(char));
        int frequence;
        reader.read((char *) &frequence, sizeof(int));
        map[ch] = frequence;
        size_outfile += frequence;
    }
}

void HuffmanArchiver::get_stat() {
    std::cout << "Size of input file: " << size_infile << std::endl;
    std::cout << "Size of output file: " << size_outfile << std::endl;
    std::cout << "Size of Huffman table: " << size_table * (sizeof(int) + sizeof(char)) + sizeof(int) << std::endl;
}

std::map<char, int> HuffmanArchiver::get_map() {
    return map;
}

std::map<char, std::vector<bool>> HuffmanArchiver::get_table() {
    return table;
}
