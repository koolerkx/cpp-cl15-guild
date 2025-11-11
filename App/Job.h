#ifndef JOB_H
#define JOB_H

#include <string>

class Job {
 private:
  const std::string m_names[4]{"ƒiƒCƒg", "”’–‚–@m", "—³‹Rm", "‹á—Vl"};

  int m_id{0};

 public:
  Job() = default;
  Job(int id) : m_id(id) {
  }
  Job(const std::string& name);

  const std::string& GetName() const {
    return m_names[m_id];
  }
};

#endif  // JOB_H
