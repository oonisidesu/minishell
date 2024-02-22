/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:51 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/22 16:33:02 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "signal/signal.h"
#include <stdlib.h>

void	ctrl_c_handler(int sig)
{
    (void)sig;
    g_signal = 1;
}

void	ctrl_c_clean_handler(t_minishell *minish)
{
    // TODO
    // プログラム実行していない時
    // 　node == NULL　の時、終了コード:1
    // プログラム実行中
    //   node != NULL の時、終了コード:130
    // どう分けよう
    // freeするとabortするのでどうしようかな
    t_node *node;
    node = minish->node;
    g_signal = 0;
    if (node == NULL)
    {
        minish->status_code = 1;
    }
    else
    {
        printf("node->pid: %d\n", node->pid);
        while (node && node->pid > 0)
        {
            kill(node->pid, SIGKILL);
            node = node->next;
        }
        minish->status_code = 130;
        // free_minishell(minish);
    }
}

void    ctrl_d_clean_handler(t_minishell *minish)
{
    printf("===> ctrl_d_clean_handler\n");
    // TODO
    // segfaultするのでどうしようかな
    // freeがよくわかってない
    // lsなどが書かれている状態でctrl_dした場合、デフォルトでbashと同じ挙動のため対応なし  
    t_node *node;
    node = minish->node;
    while (node && node->pid > 0)
    {
        kill(node->pid, SIGKILL);
        node = node->next;
    }
    //free_minishell(minish);
    //exit関数呼び出す？？
    exit(0);
}

int	signal_monitor()
{
	if (g_signal == CTRL_C_ONE)
	{
        // 入力中のテキストを破棄、これしないと変にlsとかしてしまう
        rl_delete_text(0, rl_end);
        // readline()をreturnさせる
        rl_done = 1;
        // signal_monitorがめちゃくちゃループするので、g_signalを変更する前に処理を書く
        g_signal = CTRL_C_TWO;
	}
	return (0);
}
