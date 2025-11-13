#include "App.h"

#include <iostream>
#include <sstream>
#include <tuple>

#include "Command/AddMemberCommand.h"
#include "Command/RemoveMemberCommand.h"
#include "CommandHistory.h"
#include "File.h"
#include "Menu.h"

App::App() {
  file_ = new File<SaveData>(SAVE_FILE_PATH);

  LoadDataReturn loaded_data = Load();
  bool load_result;
  SaveData save_data;

  std::tie(load_result, save_data) = loaded_data;

  if (load_result) {
    std::cout << "保存データを読み込みました。\n";
    guild_ = new Guild(save_data.characters);
    command_history_ = new CommandHistory(guild_, *save_data.command_history_);
  } else {
    guild_ = new Guild();
    command_history_ = new CommandHistory();
  }
}

App::~App() {
  delete guild_;
  delete command_history_;
  delete file_;
}

void App::Run() {
  Menu::ShowWelcomeMessage();

  do {
    try {
      Menu::ShowMainMenu();
      MenuOption selected_option = static_cast<MenuOption>(Ask<char>());
      std::cout << "\n";

      switch (selected_option) {
        case MenuOption::QUIT:
          break;
        case MenuOption::ADD_MEMBER:
          command_history_->Execute(new AddMemberCommand(guild_));
          break;
        case MenuOption::REMOVE_MEMBER:
          command_history_->Execute(new RemoveMemberCommand(guild_));
          break;
        case MenuOption::DISPLAY_LIST:
          guild_->DisplayList();
          break;
        case MenuOption::DISPLAY_DETAIL: {
          guild_->DisplayDetailed(Ask<int>("名簿を検索しますか？"));
          break;
        }
        case MenuOption::UNDO:
          command_history_->Undo();
          break;
        case MenuOption::REDO:
          command_history_->Redo();
          break;
        case MenuOption::HISTORY:
          command_history_->DisplayHistory();
          break;
      }

      if (selected_option == MenuOption::QUIT) {
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

  Save();
  std::cout << "データが保存されました。" << "\n";
  std::cin.get();
}

void App::Save() const {
  try {
    SaveData save_data;
    guild_->GetSaveData(&save_data.characters);
    command_history_->GetSaveData(save_data.command_history_);

    file_->Save(save_data);
  } catch (const exception::FileInputFailedException& e) {
    std::cout << e.what() << "\n";
  }
}

App::LoadDataReturn App::Load() const {
  try {
    SaveData save_data = file_->Load();
    return std::make_tuple(true, save_data);
  } catch (const exception::FileInputFailedException& e) {
    std::cout << e.what() << "\n";

    return std::make_tuple(false, SaveData{});
  }
}
