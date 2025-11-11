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
  void AddMember(Character* adventurer);
  void RemoveMember(int index);
  void DisplayList() const;
  void DisplayDetailed(int index) const;
};

#endif
