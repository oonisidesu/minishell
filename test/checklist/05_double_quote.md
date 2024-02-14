# double quote

- [ ] 表示する特殊文字、解釈する特殊文字
```
bash-3.2$ echo "!%^&*()$?"
echo "^&*()$?"
^&*()0
# !%はなぜか消えた？
# $?はステータスコードを表示
```

- [ ] 変数展開する
```
bash-3.2$ export ABC=hello
bash-3.2$ echo "$ABC"
hello

bash-3.2$ echo "xx $ABC xx"
xx hello xx

bash-3.2$ echo "xx$ABC xx"
xxhello xx

bash-3.2$ echo "xx$ABCxx"
xx
```




