#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <array>

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
    std::string encryptions[7] = { "MD2", "MD4", "MD5", "SHA1", "SHA256", "SHA384", "SHA512"};
#else
    #define POPEN popen
    #define PCLOSE pclose
    std::string encryptions[7] = { "md2", "md4", "md5", "sha1", "sha256", "sha384", "sha512"};
#endif


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

    // forms the file path
    std::string filePath = std::string(argv[1]);

    // add quotes around filePath (if there weren't already)
    if (!filePath.empty()) {
        if (filePath[0] != '"') {
            #ifdef _WIN32
                filePath = '"' + filePath + '"';
            #else
                filePath = '\'' + filePath + '\'';
            #endif
        }
    }
    else {
        std::cerr << "File directory empty" << std::endl;
        return 1;
    }

    // forming command
    #ifdef _WIN32
        std::string command = "certutil -hashfile " + filePath + " " + encryptions[getHash()-1];
    #else
        std::string command = "openssl dgst -" + encryptions[getHash()-1] + " " + filePath;
    #endif
    std::cout << "command: " << command << std::endl;

    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, int(*)(FILE*)> pipe(POPEN(command.c_str(), "r"), PCLOSE);

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
