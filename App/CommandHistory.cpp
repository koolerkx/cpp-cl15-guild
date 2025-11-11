#include "CommandHistory.h"

CommandHistory::~CommandHistory() {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    delete command_history_[i];
  }
}

void CommandHistory::Execute(ICommand* cmd) {
  if (!cmd) return;

  // Execute the command
  cmd->Execute();

  // Move to next position in circular array
  int next_pos = (current_ + 1) % HISTORY_SIZE;

  // Delete the command that will be overwritten (if any)
  delete command_history_[next_pos];
  command_history_[next_pos] = nullptr;

  // If history is full, move start forward
  if (count_ == HISTORY_SIZE) {
    start_ = (start_ + 1) % HISTORY_SIZE;
  } else {
    count_++;
  }

  // Store the new command
  command_history_[next_pos] = cmd;
  current_ = next_pos;
  end_ = current_;
}

void CommandHistory::Undo() {
  // Check if there's anything to undo
  if (count_ == 0 || current_ == -1) return;

  // Check if we're at the start (can't undo further)
  if (current_ == start_) {
    // Special case: undo the first command
    command_history_[current_]->Undo();
    current_ = -1;  // Mark as "before first command"
    return;
  }

  // If current is -1, we're already before the first command
  if (current_ == -1) return;

  // Undo the current command
  command_history_[current_]->Undo();

  // Move current back
  current_ = (current_ - 1 + HISTORY_SIZE) % HISTORY_SIZE;
}

void CommandHistory::Redo() {
  // Check if there's anything to redo
  if (count_ == 0) return;

  // If current_ == end_, we're at the latest command already
  if (current_ == end_) return;

  // Move current forward (or from -1 to start)
  if (current_ == -1) {
    current_ = start_;
  } else {
    current_ = (current_ + 1) % HISTORY_SIZE;
  }

  // Redo the command
  command_history_[current_]->Execute();
}
