# parse

- [ ] 空白、タブなどの解釈
/bin/ls  (tab) -la

- コマンドがない場合でもリダイレクト先のファイルの存在チェックをする
bash-3.2$ <a
bash: a: No such file or directory
bash-3.2$ echo $?
1
minishell $ <a
minishell $ echo $?
0


- $0を解釈
```
susumuyagi% bash
bash-3.2$ echo $0
bash
bash-3.2$

susumuyagi% /bin/bash
bash-3.2$ echo $0
/bin/bash
bash-3.2$
```
