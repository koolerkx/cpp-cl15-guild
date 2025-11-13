#pragma once

#include <fstream>
#include <string>

#include "Exception.h"

template <typename SaveDataT>
class File {
 public:
  File(const std::string& filename) {
    filename_ = filename;
  }

  void Save(SaveDataT save_data) const {
    std::ofstream ofs(filename_, std::ios::binary);
    if (!ofs.is_open()) {
      throw exception::FileOutputFailedException();
    }
    
    ofs.write(reinterpret_cast<const char*>(&save_data), sizeof(SaveDataT));
    ofs.close();
  }

  SaveDataT Load() {
    std::ifstream ifs(filename_, std::ios::binary);
    if (!ifs.is_open()) {
      throw exception::FileInputFailedException();
    }
    
    SaveDataT save_data{};
    ifs.read(reinterpret_cast<char*>(&save_data), sizeof(SaveDataT));
    ifs.close();

    return save_data;
  }

 private:
  std::string filename_;
};
