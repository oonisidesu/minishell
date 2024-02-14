/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:10:53 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/14 17:31:51 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

typedef struct s_builtin
{
	char	*name;
	int		(*f)(int argc, char *argv[], char *envp);
}			t_builtin;

int			builtin_echo(int argc, char *argv[], char *envp);
int			builtin_cd(int argc, char *argv[], char *envp);
int			builtin_pwd(int argc, char *argv[], char *envp);
int			builtin_export(int argc, char *argv[], char *envp);
int			builtin_unset(int argc, char *argv[], char *envp);
int			builtin_env(int argc, char *argv[], char *envp);
int			builtin_exit(int argc, char *argv[], char *envp);

#endif