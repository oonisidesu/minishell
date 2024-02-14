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

#ifndef ENV_VAL_H
#define ENV_VAL_H


typedef struct s_env_val {
    char *cmd_str;
    struct s_cmd_history *next;

} t_env_val;

void get_env(char *env_name);
void set_env(char *env_name, char *env_val);
void unset_env(char *env_name);

#endif

