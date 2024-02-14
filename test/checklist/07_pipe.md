# pipe

## 正常系
- [ ] ls | cat
- [ ] 途中でsegvでも最後まで実行、ステータスコードは最後の結果を表示
```
ls | ls | segv | ls
echo $?
0

ls | ls | segv
echo $?
127 <- うろ覚え 

ls | ls | aaaa
echo $?
126 <- うろ覚え
```

- [ ] 

## 異常系
- [ ] パイプ閉じ忘れ cat | ls
標準入力待ちとなる


