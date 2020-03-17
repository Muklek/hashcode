#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>

namespace writefile {
  class stream {
    public:
      stream(std::string, std::unordered_map<int, std::vector<int>>*, std::unordered_map<int, std::vector<int>>*, std::vector<int>*);
      stream(const stream&) = delete;
      stream(const stream&&) = delete;
      stream& operator=(const stream&) = delete;
      stream& operator=(const stream&&) = delete;
      ~stream() = default;

      void output();

    private:
      std::unordered_map<int, std::vector<int>>* books{nullptr};
      std::unordered_map<int, std::vector<int>>* libraries{nullptr};
      std::vector<int>* libIndex{nullptr};
      std::string filename;
  };
};

