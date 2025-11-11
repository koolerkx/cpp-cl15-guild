/**
 * @file main.cpp
 * @brief プログラムのメイン処理
 */

#include <iostream>

#include "Character.h"
#include "Guild.h"
#include "Job.h"

int main() {
  std::cout << "==================\n";
  std::cout << "welcome\n";
  std::cout << "==================\n";

  Guild guild;

  int n, age, hp, mp;
  char yes_no;
  std::string name, job_name;

  for (;;) {
    std::cout << "\n";
    std::cout << "menu\n";
    std::cout << "1:入会手続き\n";
    std::cout << "2:退会手続き\n";
    std::cout << "3:会員一覧\n";
    std::cout << "4:会員詳細\n";
    std::cout << "0:終了\n";
    std::cout << ">";

    std::cin >> n;
    switch (n) {
      case 0:
        return 0;
      case 1: {
        std::cout << "入会の名前を入力してください。\n>";
        std::cin >> name;
        std::cout << "入会の職業を入力してください。\n>";
        std::cin >> job_name;
        Job job{job_name};
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
        std::cout << "この冒険者を登録致します。よろしいですが？ y/n\n>";
        std::cin >> yes_no;
        if (yes_no == 'y') {
          guild.AddMember(new Character{name, job_name, age, hp, mp});
        } else {
          std::cout << "登録をキャンセルしました。\n";
        }
        break;
      }
      case 2:
        std::cout << "リストの何番目の冒険者を退会致しますか？\n>";
        std::cin >> n;
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        guild.DisplayDetailed(n);
        std::cout << "この冒険者も退会させますか？ y/n\n>";
        std::cin >> yes_no;
        if (yes_no == 'y') {
          guild.RemoveMember(n);
        }
        break;
      case 3:
        guild.DisplayList();
        break;
      case 4:
        std::cout << "名簿を検索しますか？\n>";
        std::cin >> n;
        guild.DisplayDetailed(n);
        break;
    }

    std::cin.get();
  }
}
