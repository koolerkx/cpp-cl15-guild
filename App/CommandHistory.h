#pragma once
#include "Command/ICommand.h"
#include "Guild.h"

static constexpr int HISTORY_SIZE = 5;

// using CommandHistoryInitProps = CommandSaveData[HISTORY_SIZE];
struct CommandHistoryInitProps {
  int count_{0};
  int start_{0};
  int end_{-1};
  int current_{-1};
  CommandSaveData commands[HISTORY_SIZE];
};

class CommandHistory {
 public:
  void Execute(ICommand* cmd);
  void Undo();
  void Redo();

  void DisplayHistory() const;

  CommandHistory() = default;
  CommandHistory(Guild* guild, const CommandHistoryInitProps& save_data);
  ~CommandHistory();

  void GetSaveData(CommandHistoryInitProps* buffer) const;

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
