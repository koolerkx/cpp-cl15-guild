#include "App.h"

#include <iostream>
#include <sstream>

#include "Command/AddMemberCommand.h"
#include "Command/RemoveMemberCommand.h"
#include "CommandHistory.h"
#include "Menu.h"

App::App() {
  guild_ = new Guild();
  command_history_ = new CommandHistory();
}

App::~App() {
  delete guild_;
  delete command_history_;
}

void App::Run() {
  Menu::ShowWelcomeMessage();

  do {
    Menu::ShowMainMenu();
    MenuOption selected_option = static_cast<MenuOption>(Ask<char>());

    int input;

    switch (selected_option) {
      case MenuOption::QUIT:
        return;
      case MenuOption::ADD_MEMBER:
        command_history_->Execute(new AddMemberCommand(guild_));
        break;
      case MenuOption::REMOVE_MEMBER:
        command_history_->Execute(new RemoveMemberCommand(guild_));
        break;
      case MenuOption::DISPLAY_LIST:
        guild_->DisplayList();
        break;
      case MenuOption::DISPLAY_DETAIL:
        input = Ask<int>("名簿を検索しますか？");
        guild_->DisplayDetailed(input);
        break;
      case MenuOption::UNDO:
        command_history_->Undo();
        break;
      case MenuOption::REDO:
        command_history_->Redo();
        break;
    }
  } while (true);
}
