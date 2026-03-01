#!/usr/bin/env bash
set -euo pipefail

echo "==> Running Python tests"
python -m unittest discover -s languages/python/tests -v

if command -v node >/dev/null 2>&1; then
  echo "==> Running JavaScript tests"
  node --test languages/javascript/tests
else
  echo "==> Skipping JavaScript tests (node not found)"
fi

if command -v go >/dev/null 2>&1; then
  echo "==> Running Go tests"
  bash -lc 'cd languages/go && go test ./... -v'
else
  echo "==> Skipping Go tests (go not found)"
fi

if command -v cargo >/dev/null 2>&1; then
  echo "==> Running Rust tests"
  bash -lc 'cd languages/rust && cargo test -q'
else
  echo "==> Skipping Rust tests (cargo not found)"
fi

echo "All selected tests finished."
