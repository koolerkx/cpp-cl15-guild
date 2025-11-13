/**
 * @file Character.h
 * @brief キャラクターを制御
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "job.h"

struct CharacterSaveData {
  bool is_valid_{false};
  int age_{0};
  int lv_{1};
  int hp_{0};
  int mp_{0};
  int job_id_{0};
  char name_[256]{"名前なし"};
};

class Character {
 private:
  std::string name_{"名前なし"};
  Job job_;
  int age_{0};
  int lv_{1};
  int hp_{0};
  int mp_{0};

 public:
  Character() : Character{"名前なし", "ナイト", 16, 1, 1} {
  }
  Character(const std::string& name, int job_id, int age, int hp, int mp)
      : name_{name}, job_{job_id}, age_{age}, lv_{1}, hp_{hp}, mp_{mp} {
  }
  Character(const std::string& name, const std::string& job_name, int age,
            int hp, int mp)
      : name_{name}, job_{job_name}, age_{age}, lv_{1}, hp_{hp}, mp_{mp} {
  }
  Character(const Character& c)
      : name_{c.name_},
        job_{c.job_},
        age_{c.age_},
        lv_{c.lv_},
        hp_{c.hp_},
        mp_{c.mp_} {
  }
  Character(const CharacterSaveData& save_data)
      : name_{save_data.name_},
        job_{save_data.job_id_},
        age_{save_data.age_},
        lv_{save_data.lv_},
        hp_{save_data.hp_},
        mp_{save_data.mp_} {
  }

  CharacterSaveData GetSaveData() const {
    CharacterSaveData c;
    c.is_valid_ = true;
    c.age_ = age_;
    c.lv_ = lv_;
    c.hp_ = hp_;
    c.mp_ = mp_;
    c.job_id_ = job_.GetId();
    strncpy_s(c.name_, name_.c_str(), sizeof(c.name_));

    return c;
  }

  ~Character() = default;

  void SetName(const std::string& name) {
    name_ = name;
  }
  const std::string& GetName() {
    return name_;
  }

  Job GetJob() {
    return job_;
  }

  void LvUp() {
    ++lv_;
  }
  int GetLv() const {
    return lv_;
  }

  void SetAge(int age) {
    age_ = age;
  }
  int GetAge() const {
    return age_;
  }

  void SetHp(int hp) {
    hp_ = hp;
  }
  int GetHp() const {
    return hp_;
  }

  void SetMp(int mp) {
    mp_ = mp;
  }
  int GetMp() const {
    return mp_;
  }
};

#endif  // CHARACTER_H
