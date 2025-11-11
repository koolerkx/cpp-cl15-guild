#pragma once
#include "Guild.h"

enum class MenuOption : int {
  QUIT = 0,
  ADD_MEMBER = 1,
  REMOVE_MEMBER = 2,
  DISPLAY_LIST = 3,
  DISPLAY_DETAIL = 4
};

class App {
 public:
  App();
  ~App();

  void Run();

 private:
  Guild* guild_;

  template <typename T>
  T Ask(const std::string& message = "") const;
};
