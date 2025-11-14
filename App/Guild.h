/**
 * @file Guild.h
 * @brief ƒMƒ‹ƒh‚ÌŠÇ—
 */

#ifndef GUILD_H
#define GUILD_H

#include "Character.h"

static constexpr int MAX_ADVENTURERS = 256;

using GuildInitProps = CharacterSaveData[MAX_ADVENTURERS];

class Guild {
 private:
  Character* m_adventurers[MAX_ADVENTURERS]{};

 public:
  Guild() = default;
  Guild(GuildInitProps save_data);

  ~Guild();
  int AddMember(Character* adventurer);
  Character* GetMember(int index);
  void RemoveMember(int index);
  void DisplayList() const;
  void DisplayDetailed(int index) const;

  void GetSaveData(GuildInitProps* buffer) const;
};

#endif
