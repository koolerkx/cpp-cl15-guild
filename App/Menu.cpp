#include "Menu.h"

#include <iostream>

void Menu::ShowWelcomeMessage() {
  std::cout << "==================\n";
  std::cout << "welcome\n";
  std::cout << "==================\n";
}

void Menu::ShowMainMenu() {
  std::cout << "\n";
  std::cout << "menu\n";
  std::cout << " 1 : 入会手続き\n";
  std::cout << " 2 : 退会手続き\n";
  std::cout << " 3 : 会員一覧\n";
  std::cout << " 4 : 会員詳細\n";
  std::cout << " - : Undo 元に戻す\n";
  std::cout << " + : Redo やり直し\n";
  std::cout << " = : 操作履歴\n";
  std::cout << " 0 : 終了\n";
}
