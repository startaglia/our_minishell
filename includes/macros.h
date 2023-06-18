/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:45:18 by startagl          #+#    #+#             */
/*   Updated: 2023/06/17 15:35:21 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define DUB_QUOT "\x1b[31mSyntax Error: unclosed double quotes \e[m\n"
# define SIN_QUOT "\x1b[31mSyntax Error: unclosed single quotes \e[m\n"
# define IN "\x1b[31mSyntax Error: unexpected < token \e[m\n"
# define OUT "\x1b[31mSyntax Error: unexpected > token \e[m\n"
# define PIP "\x1b[31mSyntax Error: unexpected | token \e[m\n"
# define AND "\x1b[31mSyntax Error: missing second & token \e[m\n"
# define CMD_ERR " :command not found \e[m"
# define CD_ERR "\x1b[31mminishell: cd:"
# define CD_ERR_DUE ": No such file or directory\e[m\n"
#endif