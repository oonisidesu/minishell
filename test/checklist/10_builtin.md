
# echo
## 正常系


## 異常系


# cd
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
## 正常系
- [ ] unset

- [ ] unset ABC

# env
- [ ] ソートして表示


# exit
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





