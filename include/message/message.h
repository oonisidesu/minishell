/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:45:14 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 00:53:01 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# define MINISHELL_ERROR "minishell: %s: %s\n"
# define MINISHELL_NAME "minishell: "

// --- builtin ---
# define BUILTIN_ERROR "minishell: %s: %s: %s\n"
# define HOME_NOT_SET "minishell: cd: HOME not set\n"
# define B_TOO_MANY_ARGS "too many arguments"
# define NUM_ARG_REQUIRED "numeric argument required"
# define DECLARE "declare -x %s=\"%s\"\n"
# define DECLARE_ONLY_KEY "declare -x %s\n"
# define IDENTIFIER_ERROR "minishell: %s: `%s': not a valid identifier\n"

// --- exec ---
# define COMMAND_NOT_FOUND "command not found"
# define PERMISSION_DENIED "permission denied"
# define NO_SUCH_FILE_OR_DIR "No such file or directory"

// --- parser ---
# define SYNTAX_ERROR "minishell: syntax error near unexpected token "
# define PROMPT "minishell $ "
# define ERROR_MAX_HEREDOC "minishell: maximum here-document count exceeded"
# define HEREDOC_PROMPT "> "
# define AMBIGUOUS_REDIRECT ": ambiguous redirect\n"

// --- minishell ---
# define TOO_MANY_ARGS "Error: too many arguments\n"
# define GETCWD_ERROR \
	"error retrieving current directory: \
getcwd: cannot access parent directories: Permission denied\n"
# define MALLOC_ERROR "cannot allocate"

#endif
