/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:50:04 by susumuyagi        #+#    #+#             */
/*   Updated: 2023/09/29 11:50:06 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*ft_strsig01_09(int sig)
{
	if (sig == 1)
		return ("Hangup");
	else if (sig == 2)
		return ("Interrupt");
	else if (sig == 3)
		return ("Quit");
	else if (sig == 4)
		return ("Illegal instruction");
	else if (sig == 5)
		return ("Trace/BPT trap");
	else if (sig == 6)
		return ("Abort trap");
	else if (sig == 7)
		return ("EMT trap");
	else if (sig == 8)
		return ("Floating point exception");
	else if (sig == 9)
		return ("Killed");
	return ("bad input");
}

static char	*ft_strsig10_19(int sig)
{
	if (sig == 10)
		return ("Bus error");
	else if (sig == 11)
		return ("Segmentation fault");
	else if (sig == 12)
		return ("Bad system call");
	else if (sig == 13)
		return ("Broken pipe");
	else if (sig == 14)
		return ("Alarm clock");
	else if (sig == 15)
		return ("Terminated");
	else if (sig == 16)
		return ("Urgent I/O condition");
	else if (sig == 17)
		return ("Suspended (signal)");
	else if (sig == 18)
		return ("Suspended");
	else if (sig == 19)
		return ("Continued");
	return ("bad input");
}

static char	*ft_strsig20_29(int sig)
{
	if (sig == 20)
		return ("Child exited");
	else if (sig == 21)
		return ("Stopped (tty input)");
	else if (sig == 22)
		return ("Stopped (tty output)");
	else if (sig == 23)
		return ("I/O possible");
	else if (sig == 24)
		return ("Cputime limit exceeded");
	else if (sig == 25)
		return ("Filesize limit exceeded");
	else if (sig == 26)
		return ("Virtual timer expired");
	else if (sig == 27)
		return ("Profiling timer expired");
	else if (sig == 28)
		return ("Window size changes");
	else if (sig == 29)
		return ("Information request");
	return ("bad input");
}

char	*ft_strsignal(int sig)
{
	if (1 <= sig && sig <= 9)
		return (ft_strsig01_09(sig));
	else if (10 <= sig && sig <= 19)
		return (ft_strsig10_19(sig));
	else if (20 <= sig && sig <= 29)
		return (ft_strsig20_29(sig));
	else if (sig == 30)
		return ("User defined signal 1");
	else if (sig == 31)
		return ("User defined signal 2");
	else
		return ("Unknown signal");
}
