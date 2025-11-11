#include "Guild.h"

#include <iostream>

Guild::~Guild() {
  for (Character* p : m_adventurers) {
    delete p;
  }
}

void Guild::Joining(Character* adventurer) {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!m_adventurers[i]) {
      m_adventurers[i] = adventurer;
      break;
    }
  }
}

void Guild::Withdrawal(int index) {
  delete m_adventurers[index];
  m_adventurers[index] = nullptr;
}

void Guild::DisplayList() {
  for (int i = 0; i < MAX_ADVENTURERS; i++) {
    if (!m_adventurers[i]) continue;

    std::cout << i << ":" << m_adventurers[i]->GetName();
    std::cout << "(" << m_adventurers[i]->GetLv() << ")";
    std::cout << m_adventurers[i]->GetJob().GetName() << std::endl;
  }
}

void Guild::DisplayDetailed(int index) {
  if (!m_adventurers[index]) {
    std::cout << "112211";
    return;
  }

  Character* p = m_adventurers[index];

  std::cout << "NAME" << p->GetName() << std::endl;
  std::cout << "JOB" << p->GetJob().GetName() << std::endl;
  std::cout << "AGE" << p->GetAge() << "SAI\n";
  std::cout << "LV: " << p->GetLv() << std::endl;
  std::cout << "HP: " << p->GetHp() << std::endl;
  std::cout << "MP: " << p->GetMp() << std::endl;
  std::cout << "----------------------\n";
}
