/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:36 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/04 21:10:51 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// init term control to not show ^C
void	new_term(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

// keeps the old term setting
void	old_term(int get_set, struct termios *old_term)
{
	if (get_set == GET)
		tcgetattr(STDIN_FILENO, old_term);
	else if (get_set == SET)
		tcsetattr(STDIN_FILENO, TCSANOW, old_term);
}
