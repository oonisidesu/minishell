#!/bin/bash

# 色の定義
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

all_tests_passed=true

for test_case in case/*.in; do
  # ファイル名を取得（拡張子除く）
  filename=$(basename -- "$test_case")
  filename="${filename%.*}"

  # minishellとbashを実行
  ../../minishell < "$test_case" > "out/${filename}_minishell.out"
  bash < "$test_case" > "out/${filename}_bash.out"

  # 出力を比較
  diff -u "out/${filename}_minishell.out" "out/${filename}_bash.out" > out/${filename}.diff
  if [ $? -eq 0 ]; then
    echo -e "Test case $filename ${GREEN}passed${NC}"
  else
    echo -e "Test case $filename ${RED}failed${NC}"
	all_tests_passed=false
  fi
done

if $all_tests_passed; then
  echo -e "${GREEN}All test cases passed${NC}"
  exit 0
else
  echo -e "${RED}Some test cases failed${NC}"
  exit 1
fi

