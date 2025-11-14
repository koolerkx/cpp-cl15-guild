/**
 * @file Guild.cpp
 * @brief ƒMƒ‹ƒh‚ÌŠÇ—
 */

#include "Guild.h"

#include <iostream>

Guild::Guild(GuildInitProps save_data) {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!save_data[i].is_valid_) continue;
    Character* c = new Character(save_data[i]);
    AddMember(c);
  }
}

Guild::~Guild() {
  for (Character* p : m_adventurers) {
    delete p;
  }
}

int Guild::AddMember(Character* adventurer) {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!m_adventurers[i]) {
      m_adventurers[i] = adventurer;
      return i;
    }
  }

  delete adventurer;
  return -1;
}

Character* Guild::GetMember(int index) {
  return m_adventurers[index];
}

void Guild::RemoveMember(int index) {
  delete m_adventurers[index];
  m_adventurers[index] = nullptr;
}

void Guild::DisplayList() const {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!m_adventurers[i]) continue;

    std::cout << i << ":" << m_adventurers[i]->GetName();
    std::cout << "(" << m_adventurers[i]->GetLv() << ")";
    std::cout << m_adventurers[i]->GetJob().GetName() << "\n";
  }
}

void Guild::DisplayDetailed(int index) const {
  if (!m_adventurers[index]) {
    std::cout << "No this adventurer\n";
    return;
  }

  Character* p = m_adventurers[index];

  std::cout << "NAME" << p->GetName() << "\n";
  std::cout << "JOB" << p->GetJob().GetName() << "\n";
  std::cout << "AGE" << p->GetAge() << "SAI\n";
  std::cout << "LV: " << p->GetLv() << "\n";
  std::cout << "HP: " << p->GetHp() << "\n";
  std::cout << "MP: " << p->GetMp() << "\n";
  std::cout << "----------------------" << "\n";
}

void Guild::GetSaveData(GuildInitProps* buffer) const {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (m_adventurers[i] == nullptr) continue;
    (*buffer)[i] = m_adventurers[i]->GetSaveData();
  }
}
