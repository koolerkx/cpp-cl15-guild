#pragma once
#include "Command/ICommand.h"

static constexpr int HISTORY_SIZE = 5;

class CommandHistory {
 public:
  void Execute(ICommand* cmd);
  void Undo();
  void Redo();

  CommandHistory() = default;
  ~CommandHistory();

 private:
  /**
   * @brief Command history queue
   */
  ICommand* command_history_[HISTORY_SIZE]{nullptr};
  int start_{0};
  int end_{-1};
  int current_{-1};
  int count_{0};
};
