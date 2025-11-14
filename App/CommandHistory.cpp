/**
 * @file CommandHistory.cpp
 * @brief 操作履歴の管理
 */
#include "CommandHistory.h"

#include <iostream>

#include "Command/AddMemberCommand.h"
#include "Command/RemoveMemberCommand.h"

CommandHistory::CommandHistory(Guild* guild,
                               const CommandHistoryInitProps& save_data) {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    switch (save_data.commands->command_type) {
      case CommandType::AddMemberCommand:
        command_history_[i] =
          new AddMemberCommand(guild, save_data.commands[i]);
        break;
      case CommandType::RemoveMemberCommand:
        command_history_[i] =
          new RemoveMemberCommand(guild, save_data.commands[i]);
        break;
    }
  }

  count_ = save_data.count_;
  start_ = save_data.start_;
  end_ = save_data.end_;
  current_ = save_data.current_;
}

CommandHistory::~CommandHistory() {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    delete command_history_[i];
  }
}

void CommandHistory::GetSaveData(CommandHistoryInitProps* buffer) const {
  if (count_ > 0) {
    for (int i = 0; i < HISTORY_SIZE; i++) {
      if (command_history_[i] == nullptr) continue;
      buffer->commands[i] = command_history_[i]->GetSaveData();
    }
  }
  buffer->start_ = start_;
  buffer->end_ = end_;
  buffer->current_ = current_;
  buffer->count_ = count_;
}

void CommandHistory::Execute(ICommand* cmd) {
  if (cmd == nullptr) {
    throw std::invalid_argument(
      "コマンドExecute関数はnullptrで、実行できません");
  }

  ICommand::Result result = cmd->Execute();
  if (result != ICommand::Result::SUCCESS) {
    return;
  }

  int next_pos = (current_ + 1) % HISTORY_SIZE;
  delete command_history_[next_pos];
  command_history_[next_pos] = nullptr;

  if (count_ == HISTORY_SIZE) {
    start_ = (start_ + 1) % HISTORY_SIZE;
  } else {
    count_++;
  }

  command_history_[next_pos] = cmd;
  current_ = next_pos;
  end_ = current_;

  if (count_ == 1) {
    start_ = 0;
  }
}

void CommandHistory::Undo() {
  if (count_ == 0) {
    std::cout << "取り消し履歴がないため、取り消しを実行できません。" << "\n";
    return;
  }
  if (current_ == -1) {
    std::cout << "これ以上過去の操作を取り消すことはできません。" << "\n";
    return;
  }

  command_history_[current_]->Undo();
  std::cout << "コマンドの取り消しを実行しました。" << "\n";

  current_ =
    current_ == start_ ? -1 : (current_ - 1 + HISTORY_SIZE) % HISTORY_SIZE;
}

void CommandHistory::Redo() {
  if (count_ == 0) {
    std::cout << "やり直し履歴がないため、やり直しを実行できません。" << "\n";
    return;
  }

  if (current_ == end_) {
    std::cout << "これ以上先の操作をやり直すことはできません。" << "\n";
    return;
  }

  current_ = current_ == -1 ? start_ : (current_ + 1) % HISTORY_SIZE;

  command_history_[current_]->Redo();
  std::cout << "コマンドのやり直しを実行しました。" << "\n";
}

void CommandHistory::DisplayHistory() const {
  std::cout << "==== 操作履歴 ====" << "\n";

  if (count_ <= 0) {
    std::cout << "履歴がありません。" << "\n";
  } else {
    for (int i = 0; i < count_; i++) {
      // if (current_ == -1) continue;

      const int pos = (start_ + i) % HISTORY_SIZE;
      std::cout << " " << i + 1 << " " << command_history_[pos]->GetName();

      if (pos == current_) {
        std::cout << " <- いまここまで実行した" << "\n";
        break;
      }
      std::cout << "\n";
    }
  }

  std::cout << "=================" << "\n";
  std::cout << "保存上限: " << HISTORY_SIZE << "\n";
  std::cout << "=================" << "\n";
}
