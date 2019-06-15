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

/*const int TEST_COUNT = 5;

int random_test(const char *input, const char *output_encode, const char *output_decode, int num) {
    std::cout << "Random test #" << num << ":\n";
    std::cout << "Encoding:...";
    HuffmanArchiver HuffCod(input, output_encode);
    try {
        HuffCod.archiving();
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }
    std::cout << "complete!\n";
    std::cout << "Stats:\n";
    HuffCod.get_stat();

    std::cout << "Decoding:...";

    HuffmanArchiver HuffDec(output_encode, output_decode);
    try {
        HuffDec.unzipping();
    } catch (HuffException &e) {
        std::cout << e.get() << std::endl;
    }

    std::cout << "complete!\n";
    std::cout << "Stats:\n";
    HuffDec.get_stat();
    return 0;
}


int unit_test() {
    random_test(R"(C:\Users\User\CLionProjects\Huffman\empty.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 1);
    random_test(R"(C:\Users\User\Documents\EVE\logs\Chatlogs\Corp_20180402_201143.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 1);
    random_test(R"(C:\Users\User\Documents\EVE\logs\Chatlogs\Corp_20180402_202857.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 2);
    random_test(R"(C:\Users\User\Documents\EVE\logs\Chatlogs\Corp_20180403_122011.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 3);
    random_test(R"(C:\Users\User\Documents\EVE\logs\Chatlogs\Corp_20180403_124546.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 4);
    random_test(R"(C:\Users\User\Documents\EVE\logs\Chatlogs\Corp_20180404_162658.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\input.txt)",
                R"(C:\Users\User\CLionProjects\Huffman\output.txt)", 5);
    return 0;
}
*/