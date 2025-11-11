#include "App.h"

#include <iostream>
#include <sstream>

#include "Menu.h"

App::App() {
  guild_ = new Guild();
}

App::~App() {
  delete guild_;
}

void App::Run() {
  Menu::ShowWelcomeMessage();

  do {
    Menu::ShowMainMenu();
    MenuOption selected_option = static_cast<MenuOption>(Ask<int>());

    int input;

    char yes_no;
    switch (selected_option) {
      case MenuOption::QUIT:
        return;
      case MenuOption::ADD_MEMBER: {
        int age, hp, mp;
        std::string name, job_name;
        Job job{job_name};

        std::cout << "入会の名前を入力してください。\n>";
        std::cin >> name;
        std::cout << "入会の職業を入力してください。\n>";
        std::cin >> job_name;
        std::cout << "入会の年齢を入力してください。\n>";
        std::cin >> age;
        std::cout << "入会のHPを入力してください。\n>";
        std::cin >> hp;
        std::cout << "入会のMPを入力してください。\n>";
        std::cin >> mp;
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "名前" << name << "\n";
        std::cout << "職業" << job.GetName() << "\n";
        std::cout << "年齢" << age << "歳\n";
        std::cout << "HP: " << hp << "\n";
        std::cout << "MP: " << mp << "\n";
        std::cout << "----------------------\n";

        yes_no = Ask<char>("この冒険者を登録致します。よろしいですが？ y/n");
        if (yes_no == 'y') {
          guild_->AddMember(new Character{name, job_name, age, hp, mp});
        } else {
          std::cout << "登録をキャンセルしました。\n";
        }
        break;
      }
      case MenuOption::REMOVE_MEMBER:
        input = Ask<int>("リストの何番目の冒険者を退会致しますか？");
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        guild_->DisplayDetailed(input);

        yes_no = Ask<char>("この冒険者も退会させますか？ y/n");
        if (yes_no == 'y') {
          guild_->RemoveMember(input);
        }
        break;
      case MenuOption::DISPLAY_LIST:
        guild_->DisplayList();
        break;
      case MenuOption::DISPLAY_DETAIL:
        input = Ask<int>("名簿を検索しますか？");
        guild_->DisplayDetailed(input);
        break;
    }
  } while (true);
}

template <typename T>
T App::Ask(const std::string& message) const {
  std::cout << message << "\n>";
  std::string raw_input;
  std::cin >> raw_input;

  std::istringstream iss(raw_input);
  T result{};
  if (!(iss >> result)) {
    throw std::invalid_argument("Invalid input type");
  }

  return result;
}
