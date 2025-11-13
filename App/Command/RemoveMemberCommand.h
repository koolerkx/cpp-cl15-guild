#pragma once
#include "../Guild.h"
#include "ICommand.h"

class RemoveMemberCommand : public ICommand {
 private:
  Guild* guild_;

  // cache, should not be overriding
  Character* character_ = nullptr;
  int inserted_id_ = -1;

 public:
  RemoveMemberCommand(Guild* guild) : guild_(guild) {
  }
  RemoveMemberCommand(Guild* guild, const CommandSaveData& save_data)
      : guild_(guild),
        character_(new Character(save_data.character_)),
        inserted_id_(save_data.inserted_id_) {
    this->SetName(save_data.name_);
  }

  ~RemoveMemberCommand() override;
  Result Execute() override;
  Result Redo() override;
  Result Undo() override;
  CommandSaveData GetSaveData() override;
};
