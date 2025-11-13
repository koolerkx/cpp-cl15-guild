#include "AddMemberCommand.h"

#include <iostream>

#include "../App.h"

const std::string ADD_MEMBER_COMMAND_NAME = "ギルドメンバー追加";

AddMemberCommand::~AddMemberCommand() {
  delete character_;
}

ICommand::Result AddMemberCommand::Execute() {
  std::string name = App::Ask<std::string>("入会の名前を入力してください。\n");
  std::string job_name =
    App::Ask<std::string>("入会の職業を入力してください。\n");
  Job job{job_name};

  int age = App::Ask<int>("入会の年齢を入力してください。\n");
  int hp = App::Ask<int>("入会のHPを入力してください。\n");
  int mp = App::Ask<int>("入会のMPを入力してください。\n");

  std::cout << "\n";

  std::cout << "名前" << name << "\n";
  std::cout << "職業" << job.GetName() << "\n";
  std::cout << "年齢" << age << "歳\n";
  std::cout << "HP: " << hp << "\n";
  std::cout << "MP: " << mp << "\n";
  std::cout << "----------------------\n";

  char is_confirm =
    App ::Ask<char>("この冒険者を登録致します。よろしいですが？ y/n\n");
  if (is_confirm != 'y') {
    std::cout << "登録をキャンセルしました。\n";
    return Result::CANCELED;
  }

  character_ = new Character{name, job_name, age, hp, mp};
  inserted_id_ = guild_->AddMember(new Character(*character_));

  SetName(ADD_MEMBER_COMMAND_NAME + " " + character_->GetName());
  return Result::SUCCESS;
}

ICommand::Result AddMemberCommand::Redo() {
  if (character_ == nullptr) {
    throw exception::InvalidCommandStateException(
      "[invariant] character_ が nullptr のため処理を実行できません");
  }

  inserted_id_ = guild_->AddMember(new Character(*character_));
  return Result::SUCCESS;
}

ICommand::Result AddMemberCommand::Undo() {
  if (inserted_id_ == -1)
    throw exception::InvalidCommandStateException(
      "[invariant] inserted_id_ が無効なため処理を実行できません");

  guild_->RemoveMember(inserted_id_);
  inserted_id_ = -1;
  return Result::SUCCESS;
}

CommandSaveData AddMemberCommand::GetSaveData() {
  CommandSaveData data;
  data.command_type = CommandType::AddMemberCommand;
  data.character_ = character_->GetSaveData();
  strncpy_s(data.name_, name_.c_str(), sizeof(data.name_));
  data.inserted_id_ = inserted_id_;

  return data;
}
