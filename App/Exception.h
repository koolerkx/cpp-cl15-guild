/**
 * @file Exception.h
 * @brief 例外処理
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

/**
 * @namespace exception
 * @brief 例外処理
 */
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
const std::string FILE_OUTPUT_FAILED_EXCEPTION =
  "ファイルの書き出しできませんでした";
const std::string FILE_INPUT_FAILED_EXCEPTION =
  "ファイルの読み込みできませんでした";
const std::string INVALID_COMMAND_STATE_EXCEPTION = "無効なコマンド状態";

class InvalidInputException : public Exception {
 public:
  const char* what() const noexcept override {
    return INVALID_INPUT_EXCEPTION.c_str();
  }
};

class FileOutputFailedException : public Exception {
 public:
  const char* what() const noexcept override {
    return FILE_OUTPUT_FAILED_EXCEPTION.c_str();
  }
};

class FileInputFailedException : public Exception {
 public:
  const char* what() const noexcept override {
    return FILE_INPUT_FAILED_EXCEPTION.c_str();
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
