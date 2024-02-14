

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_val.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/14 17:34:15 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "cmd.h"
#include "env_val.h"

void exec_pipeline(t_cmd *cmd, t_env_val *env);

int wait_process(t_cmd *cmd);

#endif