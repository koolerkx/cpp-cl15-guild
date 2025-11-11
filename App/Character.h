#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "job.h"

class Character {
 private:
  std::string m_name{"Name"};
  Job m_job;
  int m_age{0};
  int m_lv{1};
  int m_hp{0};
  int m_mp{0};
  // int m_atk{ 0 };
  // int m_def{ 0 };

 public:
  Character() : Character{"Name", "Fighter", 16, 1, 1} {
  }
  Character(const std::string& name, int job_id, int age, int hp, int mp)
      : m_name{name}, m_job{job_id}, m_age{age}, m_lv{1}, m_hp{hp}, m_mp{mp} {
  }
  Character(const std::string& name, const std::string& job_name, int age,
            int hp, int mp)
      : m_name{name}, m_job{job_name}, m_age{age}, m_lv{1}, m_hp{hp}, m_mp{mp} {
  }
  // Character(const std::string& name, int job_id, int age, int hp, int mp, int
  // atk, int def); Character(const std::string& name, const std::string&
  // job_name, int age, int hp, int mp, int atk, int def);
  ~Character() = default;

  void SetName(const std::string& name) {
    m_name = name;
  }
  const std::string& GetName() {
    return m_name;
  }
  Job GetJob() {
    return m_job;
  }
  void LvUp() {
    ++m_lv;
  }
  int GetLv() {
    return m_lv;
  }
  void SetAge(int age) {
    m_age = age;
  }
  int GetAge() {
    return m_age;
  }
  void SetHp(int hp) {
    m_hp = hp;
  }
  int GetHp() {
    return m_hp;
  }
  void SetMp(int mp) {
    m_mp = mp;
  }
  int GetMp() {
    return m_mp;
  }
  // void SetAtk(int atk);
  // int  GetAtk();
  // void SetDef(int def);
  // int  GetDef();
};

#endif  // CHARACTER_H
