/**
 * @file Menu.h
 * @brief メニューの表示
 */

#pragma once

/**
 * @class Menu
 * @brief メニューを表示するユーティリティークラス
 * @attention ユーティリティークラスなので、状態を持たず静的メソッドだけ実装する
 */
class Menu {
 public:
  static void ShowWelcomeMessage();
  static void ShowMainMenu();

 private:
  Menu() = default;
  ~Menu() = default;
};
