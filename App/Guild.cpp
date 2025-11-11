/**
 * @file Guild.cpp
 * @brief ƒMƒ‹ƒh‚ÌŠÇ—
 */

#include "Guild.h"

#include <iostream>

Guild::~Guild() {
  for (Character* p : m_adventurers) {
    delete p;
  }
}

void Guild::AddMember(Character* adventurer) {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!m_adventurers[i]) {
      m_adventurers[i] = adventurer;
      break;
    }
  }
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
