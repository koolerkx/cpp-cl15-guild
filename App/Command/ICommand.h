#pragma once

#include <cstdint>
#include <string>

class ICommand {
 public:
  enum class Result : uint8_t { SUCCESS, CANCELED, FAILED };

  ICommand() = default;
  ICommand(const std::string& name) {
    this->name_ = name;
  }
  virtual ~ICommand() = default;
  virtual Result Execute() = 0;

  virtual Result Redo() = 0;
  virtual Result Undo() = 0;

  const std::string& GetName() {
    return name_;
  }

 protected:
  std::string name_;
  void SetName(const std::string& name) {
    name_ = name;
  }
};
