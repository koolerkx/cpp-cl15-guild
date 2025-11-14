/**
 * @file main.cpp
 * @brief ƒvƒƒOƒ‰ƒ€‚ÌƒƒCƒ“ˆ—
 */

#include <iostream>

#include "App.h"

int main() {
  App* app = new App();

  app->Run();

  delete app;
}
