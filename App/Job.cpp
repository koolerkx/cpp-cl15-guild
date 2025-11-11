#include "job.h"

Job::Job(const std::string& name) : m_id(0) {
  for (int i = 0; i < 4; i++) {
    if (m_names[i] == name) {
      m_id = i;
      break;
    }
  }
}
