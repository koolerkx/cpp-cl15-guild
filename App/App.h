#pragma once
#include <iostream>
#include <sstream>

#include "CommandHistory.h"
#include "Exception.h"
#include "Guild.h"

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
  Guild* guild_;
  CommandHistory* command_history_;
};
