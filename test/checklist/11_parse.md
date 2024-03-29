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



https://cs61.seas.harvard.edu/site/2021/Shell/
```
commandline ::= list
          |  list ";"
          |  list "&"

list     ::=  conditional
          |   list ";" conditional
          |   list "&" conditional

conditional ::=  pipeline
          |   conditional "&&" pipeline
          |   conditional "||" pipeline

pipeline ::=  command
          |   pipeline "|" command

command  ::=  word
          |   redirection
          |   command word
          |   command redirection

redirection  ::=  redirectionop filename
redirectionop  ::=  "<"  |  ">"  |  "2>"
```





bash EBNF
https://github.com/cbeust/kash/blob/master/src/main/resources/bash.ebnf

```
<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
             A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z

<digit> ::= 0|1|2|3|4|5|6|7|8|9

<number> ::= <digit>
           | <number> <digit>

<word> ::= <letter>
         | <word> <letter>
         | <word> '_'

<word_list> ::= <word>
             |  <word_list> <word>

<assignment_word> ::= <word> '=' <word>


<redirection> ::=  '>' <word>
                |  '<' <word>
                |  <number> '>' <word>
                |  <number> '<' <word>
                |  '>>' <word>
                |  <number> '>>' <word>
                |  '<<' <word>
                |  <number> '<<' <word>
                |  '<&' <number>
                |  <number> '<&' <number>
                |  '>&' <number>
                |  <number> '>&' <number>
                |  '<&' <word>
                |  <number> '<&' <word>
                |  '>&' <word>
                |  <number> '>&' <word>
                |  '<<-' <word>
                |  <number> '<<-' <word>
                |  '>&' '-'
                |  <number> '>&' '-'
                |  '<&' '-'
                |  <number> '<&' '-'
                |  '&>' <word>
                |  <number> '<>' <word>
                |  '<>' <word>
                |  '>|' <word>
                |  <number> '>|' <word>

<simple_command> ::=  (<simple_command_element>)*

<simple_command_element> ::= <word>
                          |  <assignment_word>
                          |  <redirection>

<redirection_list> ::= <redirection>
                    |  <redirection_list> <redirection>


<command> ::=  <simple_command>
            |  <shell_command>
            |  <shell_command> <redirection_list>

<shell_command> ::=  <for_command>
                  |  <case_command>
                  |  while <compound_list> do <compound_list> done
                  |  until <compound_list> do <compound_list> done
                  |  <select_command>
                  |  <if_command>
                  |  <subshell>
                  |  <group_command>
                  |  <function_def>

<for_command> ::=  for <word> <newline_list> do <compound_list> done
            |  for <word> <newline_list> '{' <compound_list> '}'
            |  for <word> ';' <newline_list> do <compound_list> done
            |  for <word> ';' <newline_list> '{' <compound_list> '}'
            |  for <word> <newline_list> in <word_list> <list_terminator>
                   <newline_list> do <compound_list> done
            |  for <word> <newline_list> in <word_list> <list_terminator>
                   <newline_list> '{' <compound_list> '}'

<select_command> ::=  select <word> <newline_list> do <list> done
                   |  select <word> <newline_list> '{' <list> '}'
                   |  select <word> ';' <newline_list> do <list> done
                   |  select <word> ';' <newline_list> '{' list '}'
                   |  select <word> <newline_list> in <word_list>
                           <list_terminator> <newline_list> do <list> done
                   |  select <word> <newline_list> in <word_list>
                           <list_terminator> <newline_list> '{' <list> '}'

<case_command> ::=  case <word> <newline_list> in <newline_list> esac
                 |  case <word> <newline_list> in <case_clause_sequence>
                         <newline_list> esac
                 |  case <word> <newline_list> in <case_clause> esac

<function_def> ::=  <word> '(' ')' <newline_list> <group_command>
                 |  function <word> '(' ')' <newline_list> <group_command>
                 |  function <word> <newline_list> <group_command>

<subshell> ::=  '(' <compound_list> ')'

<if_command> ::= if <compound_list> then <compound_list> fi
          | if <compound_list> then <compound_list> else <compound_list> fi
          | if <compound_list> then <compound_list> <elif_clause> fi

<group_command> ::=  '{' <list> '}'

<elif_clause> ::= elif <compound_list> then <compound_list>
           | elif <compound_list> then <compound_list> else <compound_list>
           | elif <compound_list> then <compound_list> <elif_clause>

<case_clause> ::=  <pattern_list>
                |  <case_clause_sequence> <pattern_list>

<pattern_list> ::=  <newline_list> <pattern> ')' <compound_list>
                 |  <newline_list> <pattern> ')' <newline_list>
                 |  <newline_list> '(' <pattern> ')' <compound_list>
                 |  <newline_list> '(' <pattern> ')' <newline_list>

<case_clause_sequence> ::=  <pattern_list> ';;'
                         |  <case_clause_sequence> <pattern_list> ';;'

<pattern> ::=  <word>
            |  <pattern> '|' <word>


<list> ::=   <newline_list> <list0>

<compound_list> ::=  <list>
                  |  <newline_list> <list1>

<list0> ::=   <list1> '\n' <newline_list>
           |  <list1> '&' <newline_list>
           |  <list1> ';' <newline_list>

<list1> ::=   <list1> '&&' <newline_list> <list1>
           |  <list1> '||' <newline_list> <list1>
           |  <list1> '&' <newline_list> <list1>
           |  <list1> ';' <newline_list> <list1>
           |  <list1> '\n' <newline_list> <list1>
           |  <pipeline_command>

<list_terminator> ::= '\n'
                   |  ';'

<newline_list> ::=
                  |  <newline_list> '\n'

<simple_list> ::=  <simple_list1>
                |  <simple_list1> '&'
                |  <simple_list1> ';'

<simple_list1> ::=  <simple_list1> '&&' <newline_list> <simple_list1>
                 |  <simple_list1> '||' <newline_list> <simple_list1>
                 |  <simple_list1> '&' <simple_list1>
                 |  <simple_list1> ';' <simple_list1>
                 |  <pipeline_command>

<pipeline_command> ::= <pipeline>
                    |  '!' <pipeline>
                    |  <timespec> <pipeline>
                    |  <timespec> '!' <pipeline>
                    |  '!' <timespec> <pipeline>

<pipeline> ::=
          <pipeline> '|' <newline_list> <pipeline>
       |  <command>

<time_opt> ::= '-p'

<timespec> ::=  time
             |  time <time_opt>

.XE "BNF (Backus-Naur Form)"
.XE "bash" "syntax, BNF form of"

```
