/**
 * @file RemoveMemberCommand.cpp
 * @brief ギルドのメンバーを退会させるコマンド
 */

#include "RemoveMemberCommand.h"

#include <iostream>

#include "../App.h"

const std::string REMOVE_MEMBER_COMMAND_NAME = "ギルドメンバ退会";

RemoveMemberCommand::~RemoveMemberCommand() {
  delete character_;
}

ICommand::Result RemoveMemberCommand::Execute() {
  int input = App::Ask<int>("リストの何番目の冒険者を退会致しますか？");
  std::cout << "\n";
  std::cout << "\n";
  std::cout << "\n";
  guild_->DisplayDetailed(input);

  char yes_no = App::Ask<char>("この冒険者も退会させますか？ y/n");
  if (yes_no != 'y') return Result::CANCELED;

  Character* character = guild_->GetMember(input);
  if (character) {
    character_ = new Character(*character);
  }

  inserted_id_ = input;
  guild_->RemoveMember(input);

  SetName(REMOVE_MEMBER_COMMAND_NAME + " " + character_->GetName());
  return Result::SUCCESS;
}

ICommand::Result RemoveMemberCommand::Redo() {
  if (inserted_id_ == -1) {
    throw exception::InvalidCommandStateException(
      "Trying to redo remove member, but inserted id is null.");
  }

  guild_->RemoveMember(inserted_id_);
  return Result::SUCCESS;
}

ICommand::Result RemoveMemberCommand::Undo() {
  if (character_ == nullptr) {
    throw exception::InvalidCommandStateException(
      "Trying to undo remove member, but inserted id is null.");
  }

  inserted_id_ = guild_->AddMember(new Character(*character_));
  return Result::SUCCESS;
}

CommandSaveData RemoveMemberCommand::GetSaveData() {
  CommandSaveData data;
  data.command_type = CommandType::RemoveMemberCommand;
  data.character_ = character_->GetSaveData();
  strncpy_s(data.name_, name_.c_str(), sizeof(data.name_));
  data.inserted_id_ = inserted_id_;

  return data;
}
