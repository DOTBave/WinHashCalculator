#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <array>

void clearStream() {
    while (std::cin.get() != '\n');
}
int getHash() {
    int temp;
    std::cout << "hashing method?\nOptions:\nMD2 (1) | MD4 (2) | MD5 (3) | SHA1 (4) | SHA256(5) | SHA384(6) | SHA512(7): ";
    std::cin >> temp;
    clearStream();
    return temp;
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [FILE]" << std::endl;
        return 1;
    }

    std::string encryptions[7] = { "MD2", "MD4", "MD5", "SHA1", "SHA256", "SHA384", "SHA512"};
    // forms the file path
    std::string filePath = std::string(argv[1]);

    // add quotes around filePath (if there weren't already)
    if (!filePath.empty()) {
        if (filePath[0] != '"') {
            filePath = '"' + filePath + '"';
        }
    }
    else {
        std::cerr << "File directory empty" << std::endl;
        return 1;
    }

    // forming command
    std::string command = "certutil -hashfile " + filePath + " " + encryptions[getHash()-1];
    std::cout << "command: " << command << std::endl;

    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);

    if (!pipe) {
        std::cerr << "Error: Command failed to execute" << std::endl;
        return 1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    std::cout << "--- Results ---" << std::endl;
    std::cout << result;
    std::cout << "----------------" << std::endl;

    std::cout << "Press enter to exit...\n";
    std::cin.get();
    return 0;
}
