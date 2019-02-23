// RUN: %check_clang_tidy %s misc-const-vars %t

int f() {
  int number = 10;
  // CHECK-MESSAGES: [[@LINE-1]]:3: warning: Var should be const [misc-const-vars]
  // CHECK-FIXES: const int number = 10;
  return number * 10;
}

