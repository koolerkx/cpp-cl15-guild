/**
 * @file ICommand.h
 * @brief コマンドの基底クラス
 */
#pragma once

#include <cstdint>
#include <string>

#include "../Character.h"

enum class CommandType : uint8_t {
  AddMemberCommand,
  RemoveMemberCommand,
};

struct CommandSaveData {
  CommandType command_type;
  CharacterSaveData character_;
  int inserted_id_{-1};
  char name_[256]{""};
};

class ICommand {
 public:
  /// @brief コマンドの実行結果
  enum class Result : uint8_t { SUCCESS, CANCELED, FAILED };

  ICommand() = default;
  ICommand(const std::string& name) {
    this->name_ = name;
  }
  virtual ~ICommand() = default;
  virtual Result Execute() = 0;

  virtual Result Redo() = 0;
  virtual Result Undo() = 0;
  virtual CommandSaveData GetSaveData() = 0;

  const std::string& GetName() {
    return name_;
  }

 protected:
  std::string name_;
  void SetName(const std::string& name) {
    name_ = name;
  }
};
