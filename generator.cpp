#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

enum Size {
    SMALL = 512 * 1024 * 1024,
    MEDIUM = 1024 * 1024 * 1024,
    LARGE = 2048LL * 1024 * 1024
};

Size getSize(const std::string& sizeStr) {
    if (sizeStr == "SMALL") return SMALL;
    if (sizeStr == "MEDIUM") return MEDIUM;
    if (sizeStr == "LARGE") return LARGE;
    throw std::invalid_argument("Invalid size argument");
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: generator --size <SIZE> --output <OUTPUT FILE PATH>\n";
        return 1;
    }

    std::string sizeStr = argv[2];
    std::string outputFilePath = argv[4];

    Size size;
    try {
        size = getSize(sizeStr);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Cannot open file: " << outputFilePath << "\n";
        return 1;
    }

    std::srand(std::time(nullptr));
    int totalIntegers = size / sizeof(int);
    for (int i = 0; i < totalIntegers; ++i) {
        int randomInt = std::rand();
        outputFile.write(reinterpret_cast<char*>(&randomInt), sizeof(int));
    }

    outputFile.close();
    std::cout << "File generated successfully: " << outputFilePath << "\n";
    return 0;
}
