#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

namespace exception {
// 基底クラス
class Exception : public std::exception {
 public:
  Exception() = default;
  Exception(const std::string& msg) : msg_(msg) {
  }

  const char* what() const noexcept override {
    return "Exception";
  }

 protected:
  std::string msg_;
};

// カスタイマイズ例外クラス
const std::string INVALID_INPUT_EXCEPTION = "入力は無効です";
const std::string INVALID_COMMAND_STATE_EXCEPTION = "無効なコマンド状態";

class InvalidInputException : public Exception {
 public:
  const char* what() const noexcept override {
    return INVALID_INPUT_EXCEPTION.c_str();
  }
};

class InvalidCommandStateException : public Exception {
 public:
  InvalidCommandStateException(const std::string& msg)
      : Exception(INVALID_COMMAND_STATE_EXCEPTION + ": " + msg) {
  }
  const char* what() const noexcept override {
    return msg_.c_str();
  }
};
}  // namespace exception

#endif  // EXCEPTION_H
