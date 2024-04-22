/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:04:22 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/29 14:54:58 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define EXIT_MISUSE_BUILTIN_COMMAND 2
# define EXIT_CANNOT_EXECUTE_COMMAND 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_SIGNAL_BASE 128
# define EXIT_OUT_OF_RANGE_STATUS 255

# define EXIT_MAX_HEREDOC 2

#endif
