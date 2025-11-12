#include "AddMemberCommand.h"

#include <iostream>

#include "../App.h"

AddMemberCommand::~AddMemberCommand() {
  delete character_;
}

void AddMemberCommand::Execute() {
  std::string name = App::Ask<std::string>("入会の名前を入力してください。\n");
  std::string job_name =
    App::Ask<std::string>("入会の職業を入力してください。\n");
  Job job{job_name};

  int age = App::Ask<int>("入会の年齢を入力してください。\n");
  int hp = App::Ask<int>("入会のHPを入力してください。\n");
  int mp = App::Ask<int>("入会のMPを入力してください。\n");

  std::cout << "\n";
  std::cout << "\n";
  std::cout << "\n";

  std::cout << "名前" << name << "\n";
  std::cout << "職業" << job.GetName() << "\n";
  std::cout << "年齢" << age << "歳\n";
  std::cout << "HP: " << hp << "\n";
  std::cout << "MP: " << mp << "\n";
  std::cout << "----------------------\n";

  char is_confirm =
    App ::Ask<char>("この冒険者を登録致します。よろしいですが？ y/n\n");
  if (is_confirm == 'y') {
    character_ = new Character{name, job_name, age, hp, mp};
    inserted_id_ = guild_->AddMember(new Character(*character_));
  } else {
    std::cout << "登録をキャンセルしました。\n";
  }
}

void AddMemberCommand::Redo() {
  inserted_id_ = guild_->AddMember(new Character(*character_));
}

void AddMemberCommand::Undo() {
  if (inserted_id_ != -1) {
    guild_->RemoveMember(inserted_id_);
    inserted_id_ = -1;
  }
}
