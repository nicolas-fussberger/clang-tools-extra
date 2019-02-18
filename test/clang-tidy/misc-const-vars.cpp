// RUN: %check_clang_tidy %s misc-const-vars %t

// FIXME: Add something that triggers the check here.
int f() {
  int number = 10;
  return number * 10;

}

// CHECK-MESSAGES: :[[@LINE-3]]:3: warning: Var 'number' should be const [misc-const-vars]
// FIXME: Verify the applied fix.
//   * Make the CHECK patterns specific enough and try to make verified lines
//     unique to avoid incorrect matches.
//   * Use {{}} for regular expressions.
// CHECK-FIXES: {{^}}void awesome_f();{{$}}

// FIXME: Add something that doesn't trigger the check here.
void awesome_f2();
