#pragma once
#include <string>

#include "../Guild.h"
#include "ICommand.h"

class AddMemberCommand : public ICommand {
 private:
  Guild* guild_;

  // cache, should not be overriding
  Character* character_ = nullptr;
  int inserted_id_ = -1;

 public:
  AddMemberCommand(Guild* guild) : guild_(guild) {
  }

  ~AddMemberCommand() override;
  Result Execute() override;
  Result Redo() override;
  Result Undo() override;
};
