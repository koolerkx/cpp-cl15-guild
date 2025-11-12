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
    try {
      Menu::ShowMainMenu();
      MenuOption selected_option = static_cast<MenuOption>(Ask<char>());
      std::cout << "\n";

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
    } catch (const exception::InvalidCommandStateException& e) {
      // コマンド履歴をリセットする
      std::cerr << "[App エラー] " << e.what() << "\n";
      delete command_history_;
      command_history_ = new CommandHistory();
    } catch (const exception::Exception& e) {
      std::cerr << "[App エラー] " << e.what() << "\n";
    } catch (const std::exception& e) {
      std::cerr << "[Std エラー] " << e.what() << "\n";
    } catch (...) {
      std::cerr << "予期せぬエラーが発生しました。\n";
    }
  } while (true);
}
