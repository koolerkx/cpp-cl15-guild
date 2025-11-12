#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>

#include "Command/ICommand.h"
#include "CommandHistory.h"
#include "catch_amalgamated.hpp"

// Test command that tracks execution for verification
class ValueCommand : public ICommand {
 public:
  ValueCommand(int& value, int new_value,
               std::vector<std::string>* log = nullptr)
      : value_(value), new_value_(new_value), old_value_(value), log_(log) {
  }

  void Execute() override {
    if (log_)
      log_->push_back("Execute: " + std::to_string(old_value_) + "->" +
                      std::to_string(new_value_));
    value_ = new_value_;
  }

  void Undo() override {
    if (log_)
      log_->push_back("Undo: " + std::to_string(new_value_) + "->" +
                      std::to_string(old_value_));
    value_ = old_value_;
  }

 private:
  int& value_;
  int new_value_;
  int old_value_;
  std::vector<std::string>* log_;
};

TEST_CASE("CommandHistory - Initial State", "[init]") {
  int value = 0;
  CommandHistory history;

  SECTION("Empty history allows no undo") {
    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Empty history allows no redo") {
    history.Redo();
    REQUIRE(value == 0);
  }

  SECTION("Execute nullptr does nothing") {
    history.Execute(nullptr);
    REQUIRE(value == 0);
  }
}

TEST_CASE("CommandHistory - Single Command", "[single]") {
  int value = 0;
  CommandHistory history;

  SECTION("Execute single command") {
    history.Execute(new ValueCommand(value, 10));
    REQUIRE(value == 10);
  }

  SECTION("Execute and undo single command") {
    history.Execute(new ValueCommand(value, 10));
    REQUIRE(value == 10);

    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Execute, undo, redo single command") {
    history.Execute(new ValueCommand(value, 10));
    history.Undo();
    REQUIRE(value == 0);

    history.Redo();
    REQUIRE(value == 10);
  }

  SECTION("Undo beyond start (current_ becomes -1)") {
    history.Execute(new ValueCommand(value, 10));
    history.Undo();
    REQUIRE(value == 0);

    // Another undo should do nothing (current_ is -1)
    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Redo from -1 state") {
    history.Execute(new ValueCommand(value, 10));
    history.Undo();
    REQUIRE(value == 0);

    // current_ is now -1, redo should restore
    history.Redo();
    REQUIRE(value == 10);
  }

  SECTION("Redo at end does nothing") {
    history.Execute(new ValueCommand(value, 10));
    REQUIRE(value == 10);

    history.Redo();
    REQUIRE(value == 10);
  }
}

TEST_CASE("CommandHistory - Multiple Commands", "[multiple]") {
  int value = 0;
  CommandHistory history;

  SECTION("Execute multiple commands") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));
    REQUIRE(value == 30);
  }

  SECTION("Undo multiple commands") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));

    history.Undo();
    REQUIRE(value == 20);
    history.Undo();
    REQUIRE(value == 10);
    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Redo multiple commands") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));

    history.Undo();
    history.Undo();
    history.Undo();
    REQUIRE(value == 0);

    history.Redo();
    REQUIRE(value == 10);
    history.Redo();
    REQUIRE(value == 20);
    history.Redo();
    REQUIRE(value == 30);
  }

  SECTION("Partial undo then redo") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));

    history.Undo();
    history.Undo();
    REQUIRE(value == 10);

    history.Redo();
    REQUIRE(value == 20);
  }
}

TEST_CASE("CommandHistory - Branch Cutting", "[branch]") {
  int value = 0;
  CommandHistory history;

  SECTION("Execute after single undo cuts branch") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));

    history.Undo();
    REQUIRE(value == 20);

    // This should overwrite the 30 command
    history.Execute(new ValueCommand(value, 25));
    REQUIRE(value == 25);

    // Redo should do nothing (branch was cut)
    history.Redo();
    REQUIRE(value == 25);

    // Verify we can still undo to previous commands
    history.Undo();
    REQUIRE(value == 20);
  }

  SECTION("Execute after multiple undos cuts entire branch") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));
    history.Execute(new ValueCommand(value, 30));
    history.Execute(new ValueCommand(value, 40));

    history.Undo();
    history.Undo();
    history.Undo();
    REQUIRE(value == 10);

    // This cuts commands 20, 30, 40
    history.Execute(new ValueCommand(value, 15));
    REQUIRE(value == 15);

    history.Redo();
    REQUIRE(value == 15);  // No redo available
  }

  SECTION("Execute after undo to -1 state") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));

    history.Undo();
    history.Undo();
    REQUIRE(value == 0);

    // Execute from -1 state
    history.Execute(new ValueCommand(value, 15));
    REQUIRE(value == 15);

    // Old branch should be cut
    history.Redo();
    REQUIRE(value == 15);

    // But we can still undo
    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Multiple branch cuts") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(new ValueCommand(value, 20));

    // First branch cut
    history.Undo();
    history.Execute(new ValueCommand(value, 15));
    REQUIRE(value == 15);

    // Second branch cut
    history.Undo();
    history.Execute(new ValueCommand(value, 12));
    REQUIRE(value == 12);

    // Verify history
    history.Undo();
    REQUIRE(value == 10);
  }
}

TEST_CASE("CommandHistory - Circular Buffer Fill", "[circular]") {
  int value = 0;
  CommandHistory history;

  SECTION("Fill buffer exactly (5 commands)") {
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }
    REQUIRE(value == 50);
    REQUIRE(value == HISTORY_SIZE * 10);

    // Undo all
    for (int i = HISTORY_SIZE; i > 0; i--) {
      history.Undo();
    }
    REQUIRE(value == 0);

    // Redo all
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Redo();
    }
    REQUIRE(value == 50);
  }

  SECTION("Overflow by 1 - oldest command lost") {
    // Fill buffer: [10, 20, 30, 40, 50]
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }

    // Overflow: [60, 20, 30, 40, 50] - command 10 is overwritten
    history.Execute(new ValueCommand(value, 60));
    REQUIRE(value == 60);

    // Can only undo 5 times (back to 10, not 0)
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history.Undo();
    }
    REQUIRE(value == 10);  // Can't go back to 0

    // Extra undo does nothing
    history.Undo();
    REQUIRE(value == 10);
  }

  SECTION("Overflow by multiple - wraparound") {
    // Fill buffer
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }

    // Add 3 more (wraparound)
    history.Execute(new ValueCommand(value, 60));
    history.Execute(new ValueCommand(value, 70));
    history.Execute(new ValueCommand(value, 80));
    REQUIRE(value == 80);

    // Can undo 5 times: 80->70->60->50->40->30
    history.Undo();  // 70
    history.Undo();  // 60
    history.Undo();  // 50
    history.Undo();  // 40
    history.Undo();  // 30
    REQUIRE(value == 30);

    // Extra undo does nothing
    history.Undo();
    REQUIRE(value == 30);
  }

  SECTION("Overflow then redo") {
    for (int i = 1; i <= HISTORY_SIZE + 2; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }
    REQUIRE(value == 70);

    history.Undo();
    history.Undo();
    REQUIRE(value == 50);

    history.Redo();
    REQUIRE(value == 60);
    history.Redo();
    REQUIRE(value == 70);

    // No more redo
    history.Redo();
    REQUIRE(value == 70);
  }
}

TEST_CASE("CommandHistory - Circular Buffer Edge Cases", "[circular][edge]") {
  int value = 0;
  CommandHistory history;

  SECTION("Fill, undo all, execute (from -1 state in full buffer)") {
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }

    // Undo all to -1 state
    for (int i = 0; i <= HISTORY_SIZE; i++) {
      history.Undo();
    }
    REQUIRE(value == 0);

    // Execute from -1 state
    history.Execute(new ValueCommand(value, 5));
    REQUIRE(value == 5);
  }

  SECTION("Overflow, undo to start, execute (branch cut in wrapped buffer)") {
    for (int i = 1; i <= HISTORY_SIZE + 2; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }
    REQUIRE(value == 70);

    history.Undo();
    REQUIRE(value == 60);
    history.Undo();
    REQUIRE(value == 50);
    history.Undo();
    REQUIRE(value == 40);

    history.Undo();
    INFO("After 4th undo, value should be 30");
    REQUIRE(value == 30);

    history.Undo();
    INFO("After 5th undo (should hit start), value should be 20");
    REQUIRE(value == 20);

    // Execute (should cut branch)
    history.Execute(new ValueCommand(value, 25));
    REQUIRE(value == 25);

    // Redo should do nothing
    history.Redo();
    REQUIRE(value == 25);
  }

  SECTION(
    "Overflow, partial undo, execute (branch cut in middle of wrapped "
    "buffer)") {
    for (int i = 1; i <= HISTORY_SIZE + 3; i++) {
      history.Execute(new ValueCommand(value, i * 10));
    }
    // Buffer: [60, 70, 80, 40, 50] with start=3

    history.Undo();
    history.Undo();
    REQUIRE(value == 60);

    // Execute (cuts 70, 80)
    history.Execute(new ValueCommand(value, 65));
    REQUIRE(value == 65);

    // Can still undo through circular buffer
    history.Undo();  // 60
    history.Undo();  // 50
    history.Undo();  // 40
    REQUIRE(value == 40);
  }

  SECTION("Continuous wraparound stress test") {
    // Execute many commands to thoroughly wrap around
    for (int i = 1; i <= HISTORY_SIZE * 3; i++) {
      history.Execute(new ValueCommand(value, i));
    }
    REQUIRE(value == 15);

    // Should be able to undo 5 times
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history.Undo();
    }
    REQUIRE(value == 10);

    // Redo back
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history.Redo();
    }
    REQUIRE(value == 15);
  }
}

TEST_CASE("CommandHistory - State Tracking", "[state]") {
  int value = 0;
  std::vector<std::string> log;
  CommandHistory history;

  SECTION("Verify execution order with logging") {
    history.Execute(new ValueCommand(value, 10, &log));
    history.Execute(new ValueCommand(value, 20, &log));

    REQUIRE(log.size() == 2);
    REQUIRE(log[0] == "Execute: 0->10");
    REQUIRE(log[1] == "Execute: 10->20");
  }

  SECTION("Verify undo/redo order") {
    history.Execute(new ValueCommand(value, 10, &log));
    history.Execute(new ValueCommand(value, 20, &log));
    log.clear();

    history.Undo();
    history.Undo();
    REQUIRE(log.size() == 2);
    REQUIRE(log[0] == "Undo: 20->10");
    REQUIRE(log[1] == "Undo: 10->0");

    log.clear();
    history.Redo();
    history.Redo();
    REQUIRE(log.size() == 2);
    REQUIRE(log[0] == "Execute: 0->10");
    REQUIRE(log[1] == "Execute: 10->20");
  }
}

TEST_CASE("CommandHistory - Complex Scenarios", "[complex]") {
  int value = 0;
  CommandHistory history;

  SECTION("Alternating execute and undo") {
    history.Execute(new ValueCommand(value, 10));
    history.Undo();
    history.Execute(new ValueCommand(value, 20));
    history.Undo();
    history.Execute(new ValueCommand(value, 30));
    REQUIRE(value == 30);

    history.Undo();
    REQUIRE(value == 0);
  }

  SECTION("Fill buffer with undo/redo cycles") {
    for (int i = 1; i <= HISTORY_SIZE; i++) {
      history.Execute(new ValueCommand(value, i * 10));
      if (i % 2 == 0) {
        history.Undo();
        history.Redo();
      }
    }
    REQUIRE(value == 50);

    // All commands should be accessible
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history.Undo();
    }
    REQUIRE(value == 0);
  }

  SECTION("Overflow with undo/redo during fill") {
    for (int i = 1; i <= HISTORY_SIZE + 2; i++) {
      history.Execute(new ValueCommand(value, i * 10));
      if (i == 3) {
        history.Undo();
        history.Redo();
      }
    }
    REQUIRE(value == 70);

    // Undo to available start
    for (int i = 0; i < HISTORY_SIZE; i++) {
      history.Undo();
    }
    REQUIRE(value == 20);
  }

  SECTION("Execute nullptr doesn't break state") {
    history.Execute(new ValueCommand(value, 10));
    history.Execute(nullptr);
    history.Execute(new ValueCommand(value, 20));
    REQUIRE(value == 20);

    history.Undo();
    REQUIRE(value == 10);
    history.Redo();
    REQUIRE(value == 20);
  }
}
