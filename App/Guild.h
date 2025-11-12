/**
 * @file Guild.h
 * @brief ƒMƒ‹ƒh‚ÌŠÇ—
 */

#ifndef GUILD_H
#define GUILD_H

#include "Character.h"

class Guild {
 private:
  static constexpr int MAX_ADVENTURERS = 256;
  Character* m_adventurers[MAX_ADVENTURERS]{};

 public:
  Guild() = default;
  // Guild(const std::string& filename)
  ~Guild();
  int AddMember(Character* adventurer);
  Character* GetMember(int index);
  void RemoveMember(int index);
  void DisplayList() const;
  void DisplayDetailed(int index) const;
};

#endif
