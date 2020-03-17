#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<numeric>
#include<cmath>


namespace indexes {
  constexpr int numBook{0};
  constexpr int signup{1};
  constexpr int bookProcess{2};
  constexpr int totalProcess{3};
  constexpr int weight{4};
};

class BookSorter {
  public:
    BookSorter(int*, int*, int*, std::vector<int>*,
        std::unordered_map<int, std::vector<int>>*,
        std::unordered_map<int, std::vector<int>>*);
    BookSorter(const BookSorter&) = delete;
    BookSorter(const BookSorter&&) = delete;
    BookSorter& operator=(const BookSorter&) = delete;
    BookSorter& operator=(const BookSorter&&) = delete;
    ~BookSorter() = default;

    std::vector<int>* getLibraries();

    void processLibraries();

  private:
    int* numLibrary{nullptr};
    int* numBooks{nullptr};
    int* deadline{nullptr};
    std::unordered_map<int, std::vector<int>>* properties{nullptr};
    std::unordered_map<int, std::vector<int>>* books{nullptr};
    std::vector<int>* scores{nullptr};

    std::vector<int> libIndex;
    std::unordered_map<int, int> bookTracker;

    inline void sortLibraries(int, int, int, auto);
    inline void sortBooks(int);

    inline void cleanDuplicates(int, int);
    inline void cleanLibraries();

    inline void storeBookTracker(int, int);
    inline bool hasEqualSignup(const int&, const int&);

    inline void updateLibraryProperties(int, int);
};

