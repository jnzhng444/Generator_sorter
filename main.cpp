#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "paged_array.h"
#include "sorting_algorithms.h"

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << std::endl;
        return 1;
    }

    std::string inputFilePath, outputFilePath, algorithm;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-input") inputFilePath = argv[++i];
        else if (std::string(argv[i]) == "-output") outputFilePath = argv[++i];
        else if (std::string(argv[i]) == "-alg") algorithm = argv[++i];
    }

    std::ifstream inFile(inputFilePath, std::ios::binary | std::ios::ate);
    int numElements = inFile.tellg() / sizeof(int);
    inFile.close();

    std::ifstream src(inputFilePath, std::ios::binary);
    std::ofstream dst(outputFilePath, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    PagedArray arr(outputFilePath, numElements);

    auto start = std::chrono::high_resolution_clock::now();
    if (algorithm == "QS") {
        quickSort(arr, 0, numElements - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, numElements);
    } else if (algorithm == "BS") {
        bubbleSort(arr, numElements);
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::ofstream out(outputFilePath);
    for (int i = 0; i < numElements; i++) {
        if (i > 0) out << ",";
        out << arr[i];
    }
    out.close();

    std::cout << "Sorting completed in " << duration.count() << " seconds" << std::endl;
    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Page faults: " << arr.getPageFaults() << std::endl;
    std::cout << "Page hits: " << arr.getPageHits() << std::endl;

    return 0;
}
