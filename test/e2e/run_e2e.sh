#!/bin/bash

# 色の定義
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

all_tests_passed=true

# 出力結果をbashと比較
for test_case in case/*.in; do
  # ファイル名を取得（拡張子除く）
  filename=$(basename -- "$test_case")
  filename="${filename%.*}"

  # minishellとbashを実行
  ../../minishell < "$test_case" > "out/${filename}_minishell.out" 2> "out/${filename}_minishell.err"
  bash < "$test_case" > "out/${filename}_bash.out" 2> "out/${filename}_bash.err"

  diff "out/${filename}_minishell.out" "out/${filename}_bash.out" > out/${filename}.diff
  if [ $? -eq 0 ]; then
    echo -e "${GREEN}passed${NC}:\t$filename"
  else
    echo "---------------------------------------- diff ----------"
    cat "out/${filename}.diff"
    echo "---------------------------------------- minishell -----"
    cat "out/${filename}_minishell.out"
    echo "---------------------------------------- bash ----------"
    cat "out/${filename}_bash.out"
    echo "--------------------------------------------------------"
    echo -e "${RED}failed${NC}:\t$filename"
    all_tests_passed=false
  fi
done

# エラー結果を予測と比較
for test_case in case/*.err; do
  # ファイル名を取得（拡張子除く）
  filename=$(basename -- "$test_case")
  filename="${filename%.*}"

  # minishellとbashを実行
  ../../minishell < "$test_case" > "out/${filename}_minishell.out" 2> "out/${filename}_minishell.err"
  bash < "$test_case" > "out/${filename}_bash.out" 2> "out/${filename}_bash.err"

  diff "out/${filename}_minishell.err" "case/${filename}.expected" > out/${filename}.err.diff
  if [ $? -eq 0 ]; then
    echo -e "${GREEN}passed${NC}:\t$filename(error)"
  else
    echo "---------------------------------------- diff(error) ----------"
    cat "out/${filename}.err.diff"
    echo "---------------------------------------- minishell(error) -----"
    cat "out/${filename}_minishell.err"
    echo "---------------------------------------- expected(error) ------"
    cat "case/${filename}.expected"
    echo "---------------------------------------------------------------"
    echo -e "${RED}failed${NC}:\t$filename(error)"
    all_tests_passed=false
  fi
done

# 終了ステータス
if $all_tests_passed; then
  echo -e "${GREEN}All test cases passed${NC}"
  exit 0
else
  echo -e "${RED}Some test cases failed${NC}"
  exit 1
fi

