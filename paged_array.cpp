#include "paged_array.h"
#include <fstream>
#include <cstdlib>

PagedArray::PagedArray(const std::string& path, int elements) : filePath(path), numElements(elements), pageFaults(0), pageHits(0) {
    for (int i = 0; i < NUM_PAGES; ++i) {
        pages[i].resize(PAGE_SIZE, 0);
    }
}

int& PagedArray::operator[](int index) {
    int pageIndex = index / PAGE_SIZE;
    int pageOffset = index % PAGE_SIZE;
    int pageLocation = loadPage(pageIndex);
    return pages[pageLocation][pageOffset];
}

int PagedArray::loadPage(int pageIndex) {
    if (pageTable.find(pageIndex) != pageTable.end()) {
        pageHits++;
        return pageTable[pageIndex];
    }

    int pageToReplace = rand() % NUM_PAGES;

    if (!pages[pageToReplace].empty()) {
        std::ofstream out(filePath, std::ios::in | std::ios::out | std::ios::binary);
        out.seekp(pageToReplace * PAGE_SIZE * sizeof(int));
        out.write(reinterpret_cast<char*>(pages[pageToReplace].data()), PAGE_SIZE * sizeof(int));
        out.close();
    }

    pages[pageToReplace].resize(PAGE_SIZE);
    std::ifstream in(filePath, std::ios::binary);
    in.seekg(pageIndex * PAGE_SIZE * sizeof(int));
    in.read(reinterpret_cast<char*>(pages[pageToReplace].data()), PAGE_SIZE * sizeof(int));
    in.close();

    pageTable[pageIndex] = pageToReplace;
    pageFaults++;
    return pageToReplace;
}

int PagedArray::getPageFaults() const {
    return pageFaults;
}

int PagedArray::getPageHits() const {
    return pageHits;
}
