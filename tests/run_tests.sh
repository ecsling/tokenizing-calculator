#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."

BIN=./my_bc

# Build binary if missing
if [ ! -x "$BIN" ]; then
  echo "Building my_bc..."
  make -j2 || exit 1
fi

cases=(
  " 1+2  *3|7|0"
  " -(5+2)|-7|0"
  "10/     (3-3      )|parse     error|1"
  "3    %2|1  |0" 
  " +   5|5|0               "
  "             2+3      *         4-5/2|12|0"
)

fail=0
for c in "${cases[@]}"; do
  IFS='|' read -r expr expect expect_code <<< "$c"
  if out=$($BIN "$expr" 2>&1); then
    rc=0
  else
    rc=$?
  fi
  # normalize whitespace for robust comparisons and pretty printing
  normalize() {
    # collapse all whitespace runs to single spaces and trim
    echo "$1" | tr -s '[:space:]' ' ' | sed -e 's/^ //' -e 's/ $//'
  }

  got=$(printf "%s" "$out")
  got_n=$(normalize "$got")
  expect_n=$(normalize "$expect")
  expr_n=$(normalize "$expr")

  if [ "$rc" -eq 0 ]; then
    if [ "$got_n" = "$expect_n" ] && [ "$rc" -eq "$expect_code" ]; then
      printf "PASS: %s -> %s\n" "$expr_n" "$got_n"
    else
      printf "FAIL: %s -> got='%s' rc=%d expected='%s' expected_rc=%s\n" "$expr_n" "$got_n" "$rc" "$expect_n" "$expect_code"
      fail=1
    fi
  else
    if [ "$expect_n" = "parse error" ] && [ "$rc" -ne 0 ]; then
      printf "PASS: %s -> parse error (rc=%d)\n" "$expr_n" "$rc"
    else
      printf "FAIL: %s -> got='%s' rc=%d expected='%s' expected_rc=%s\n" "$expr_n" "$got_n" "$rc" "$expect_n" "$expect_code"
      fail=1
    fi
  fi
done

if [ "$fail" -ne 0 ]; then
  echo "Some tests failed"
  exit 1
fi

echo "All tests passed"
