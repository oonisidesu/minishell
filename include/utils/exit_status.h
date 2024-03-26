/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:04:22 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/26 15:03:17 by ootsuboyosh      ###   ########.fr       */
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

#endif