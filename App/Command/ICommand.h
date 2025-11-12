#pragma once

#include <cstdint>

class ICommand {
 public:
  enum class Result: uint8_t {
    SUCCESS,
    CANCELED,
    FAILED
  };
  
  virtual ~ICommand() = default;
  virtual Result Execute() = 0;

  virtual Result Redo() = 0;
  virtual Result Undo() = 0;
};
