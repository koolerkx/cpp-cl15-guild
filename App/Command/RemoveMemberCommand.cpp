#include "RemoveMemberCommand.h"

#include <iostream>

#include "../App.h"

RemoveMemberCommand::~RemoveMemberCommand() {
  delete character_;
}

void RemoveMemberCommand::Execute() {
  int input = App::Ask<int>("ƒŠƒXƒg‚Ì‰½”Ô–Ú‚Ì–`Œ¯Ò‚ğ‘Ş‰ï’v‚µ‚Ü‚·‚©H");
  std::cout << "\n";
  std::cout << "\n";
  std::cout << "\n";
  guild_->DisplayDetailed(input);

  char yes_no = App::Ask<char>("‚±‚Ì–`Œ¯Ò‚à‘Ş‰ï‚³‚¹‚Ü‚·‚©H y/n");
  if (yes_no != 'y') return;

  Character* character = guild_->GetMember(input);
  if (character) {
    character_ = new Character(*character);
  }

  inserted_id_ = input;
  guild_->RemoveMember(input);
}

void RemoveMemberCommand::Redo() {
  guild_->RemoveMember(inserted_id_);
}

void RemoveMemberCommand::Undo() {
  inserted_id_ = guild_->AddMember(new Character(*character_));
}
