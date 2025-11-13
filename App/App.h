#pragma once
#include <iostream>
#include <sstream>

#include "CommandHistory.h"
#include "Exception.h"
#include "File.h"
#include "Guild.h"

const std::string SAVE_FILE_PATH = "save.dat";

struct SaveData {
  GuildInitProps characters{};
  CommandHistoryInitProps command_history_[HISTORY_SIZE]{};
};

enum class MenuOption : char {
  QUIT = '0',
  ADD_MEMBER = '1',
  REMOVE_MEMBER = '2',
  DISPLAY_LIST = '3',
  DISPLAY_DETAIL = '4',
  REDO = '+',
  UNDO = '-',
  HISTORY = '=',
};

class App {
 public:
  App();
  ~App();

  void Run();

  // for std::string, no space is allowed, otherwise, it will break other input
  template <typename T>
  static T Ask(const std::string& message = "") {
    std::cout << message << "> ";

    std::string raw_input;
    std::getline(std::cin, raw_input);

    std::istringstream iss(raw_input);
    T result{};
    if (!(iss >> result)) {
      throw exception::InvalidInputException();
    }

    return result;
  }

 private:
  Guild* guild_{nullptr};
  CommandHistory* command_history_{nullptr};

  File<SaveData>* file_{nullptr};

  void Save() const;
  using LoadDataReturn = std::tuple<bool, SaveData>;
  LoadDataReturn Load() const;
};
