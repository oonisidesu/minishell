
# echo
- echo "$USER'入力を待たない
----------------------------
- echo -nx 42 の出力の差異
----------------------------
- echo $"aaaa"/echo $'aaaa'/export TEST=aaaa ; echo $"$TEST" で$aaaaと出力されていました。
----------------------------
```
minishell $ echo -n -n
-nminishell $ echo -nnnnn -n
-nnnnn -n
```
----------------------------
- echo - は「-」 が出力されるはずです。
## 正常系


## 異常系


# cd
- cd - 
- cd --
----------------------------
- HOME有無でのcd
```
minishell$ unset HOME
minishell$ cd
minishell$ cd: HOME not set
minishell$ export HOME=aaa
minishell$ cd
minishell$ cd: aaa: No such file or directory
```
----------------------------
- env -i でminishell が起動された時の問題
```
minishell$ env -i ./minishell
minishell$ minishell $ cd ..
minishell$ zsh: segmentation fault  env -i ./minishell
```
----------------------------
- cd は最初の引数しか見ていないのでcd Downloads/ hello はDownloadsに移動できます！
----------------------------
- cd:権限がないフォルダにいる時に移動ができなくなる
## 正常系


## 異常系


# pwd
## 正常系
- pwd
- 引数は無視？
```
pwd a b c
pwd < file.txt
```

# export
- export A のように値なしで export しても, export コマンドの結果に変数Aが存在しない. export A+=xxx で既存の変数の値に文字列を連結できます
----------------------------
- export 1 でエラーが出ません
----------------------------
- エラーの場合は何かメッセージが欲しいかも！
```
bash-3.2$ export AAA = B
bash: export: `=': not a valid identifier
minishell $ export  AAAA = B
minishell $ export  | grep AAA
```
----------------------------
- export  AAAA=　BBB の場合BBBが作成されていませんでした。
- exportに空白が含まれていた場合の処理が違いました。
```
minishell $ export  AAAA="ls -la"
minishell $ $AAAA
minishell: ls -la: command not found
```
----------------------------
- exportで"+="が実装されていない
----------------------------
- minishell $ unset A B 1 C D
minishell: export: `1': not a valid identifier```時に時に終了ステータスが1ですが0になっていて誤りがありました。挙動がbash-5.2, bash-3.2のどちらかに統一した方が良いかもです。
----------------------------
- export PATH=/binができない。
----------------------------
- env を全て削除した際にexport したらSEGVしました。
## 正常系

- export ABC=hello

- "="が続かない場合
```
なにもしない？
export ABC
export ABC EFG HIJ
```



- "="の後ろに空白がある場合
```
bash-3.2$ export AAA= B
bash-3.2$ echo $AAA

bash-3.2$
```

## 異常系
- "="前後に空白がある場合
```
bash-3.2$ export AAA = B
bash: export: `=': not a valid identifier
```

- 数字から始まる環境変数名
```
export 1=123
bash: export: `1=123': not a valid identifier
bash-3.2$ export 1ab=123
bash: export: `1ab=123': not a valid identifier
```

# unset
- unset PATHした時に環境変数コマンドだけでなく、絶対PATH, 相対PATH使えなくなる
----------------------------
- UNSETコマンドが前方一致で削除されてしまうなどの不具合がありました。
----------------------------
- unset ZZZ PWD CCC OLDPWDで存在する環境変数が消えない。
## 正常系
- [ ] unset

- [ ] unset ABC

# env
- [ ] ソートして表示


# exit
- exit 1 1 でexitしてしまいます (エラーだけ出して, 実行を続けるのが正しい)
----------------------------
- exit -42等で、引数が負の際にはステータスコードは214(256-42)といった挙動になります。
----------------------------
- cat << eの時にsigintが来るとexit status1 ではなく0になっていました。
----------------------------
- パイプでcommand not foundが起こった時にexit statusが141になっていました。
----------------------------
- 単純に改行した時のexit statusが258になっていました
## 正常系
- [ ] exit
echo $?
0

- [ ] exit 12
echo $?
12

- [ ] exit 123456
echo $?
64

## 異常系
- [ ] exit a 1
bash: exit: a: numeric argument required

- [ ] exit 1 1
bash: exit: too many arguments





