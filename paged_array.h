#ifndef PAGED_ARRAY_H
#define PAGED_ARRAY_H

#include <iostream>
#include <vector>
#include <unordered_map>

class PagedArray {
private:
    static const int PAGE_SIZE = 1024; // Tamaño de página
    static const int NUM_PAGES = 4; // Número de páginas en memoria

    std::string filePath;
    int numElements;
    std::vector<int> pages[NUM_PAGES]; // Espacios para páginas en memoria
    std::unordered_map<int, int> pageTable; // Mapea el índice de la página a su posición en memoria
    int pageFaults;
    int pageHits;

    int loadPage(int pageIndex);

public:
    PagedArray(const std::string& path, int elements);
    int& operator[](int index);
    int getPageFaults() const;
    int getPageHits() const;
};

#endif // PAGED_ARRAY_H
