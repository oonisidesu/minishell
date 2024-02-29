/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/27 18:52:25 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/prompt.h"
#include "signal/signal.h"
#include "variable/env.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)envp;
	(void)argv;
	// TODO
	// t_minishellの初期化したい
	init_minishell(&minish);
	signal(SIGINT, ctrl_c_handler);
	rl_initialize();
	rl_event_hook = signal_monitor;
	if (argc > 1)
	{
		ft_printf_fd(STDERR_FILENO, TOO_MANY_ARGS);
		return (1);
	}
	set_envp(&minish, (const char **)envp);
	// t_var *current_var = minish.var;
	// while (current_var)
	// {
	// 	printf("-------------------------\n");
	// 	ft_printf("%s\n", current_var->key);
	// 	ft_printf("%s\n", current_var->val);
	// 	ft_printf("%d\n", current_var->type);  // Assuming 'type' is an integer
	// 	current_var = current_var->next;
	// }
	// t_var *current_var2 = minish.var;
	add_or_update_var(&minish, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin", VAR_SHELL);
	// add_or_update_var(&minish, "sss", "abc", VAR_SHELL);
	// while (current_var2)
	// {
	// 	printf("-------------------------\n");
	// 	ft_printf("%s\n", current_var2->key);
	// 	ft_printf("%s\n", current_var2->val);
	// 	ft_printf("%d\n", current_var2->type);  // Assuming 'type' is an integer
	// 	current_var2 = current_var2->next;
	// }
	char **ejjj = get_envp(&minish);
	for (size_t i = 0; i < 40; i++) {
        printf("%zu: %s\n", i, ejjj[i]);
        free(ejjj[i]); // Free each string in envp
    }
	t_var *current_var = minish.var;
	while (current_var)
	{
		printf("-------------------------\n");
		ft_printf("%s\n", current_var->key);
		ft_printf("%s\n", current_var->val);
		ft_printf("%d\n", current_var->type);  // Assuming 'type' is an integer
		current_var = current_var->next;
	}
	while (1)
	{
		prompt(&minish);
	}
	return (0);
}
