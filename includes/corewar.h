/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/21 09:45:12 by khansman          #+#    #+#             */
/*   Updated: 2016/08/23 11:39:35 by arnovan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This is a prototype header file for the corewar vm.
*/

#ifndef COREWAR_H
# define COREWAR_H

/*
** ---------
** Includes:
** ---------
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# include "libft.h"
# include "op.h"

/*
** --------
** Defines:
** --------
*/

/*
**		Shorthand:
*/
# define L_STATE t_live_state
# define PROCESS t_process
# define PROCES2 struct s_process

# define C_TYPE 0b11110000000000000000000000000000 >> 28
# define C_MO_A 0b00001100000000000000000000000000 >> 26
# define C_MO_B 0b00000011000000000000000000000000 >> 24
# define C_FI_A 0b00000000111111111111000000000000 >> 12
# define C_FI_B 0b00000000000000000000111111111111 >> 00

# define C_ARG1 0b11000000 >> 6
# define C_ARG2 0b00110000 >> 4
# define C_ARG3 0b00001100 >> 2
# define C_ARG4 0b00000011

/*
**		Instructions:
*/
# define LIVE  0x01
# define LD    0x02
# define ST    0x03
# define ADD   0x04
# define SUB   0x05
# define AND   0x06
# define OR    0x07
# define XOR   0x08
# define ZJMP  0x09
# define LDI   0x0a
# define STI   0x0b
# define FORK  0x0c
# define LLD   0x0d
# define LLDI  0x0e
# define LFORK 0x0f
# define AFF   0x10

/*
**		Colour codes:
*/
# define C_RED \e[31m

/*
**		Error Messages:
*/
# define ERR_MSG_00 "C_RED Error: Not enough memory avaliable.\n"
# define ERR_MSG_01 "C_RED Error: No arguments specified.\n"
# define ERR_MSG_02 "C_RED Error: Multiple definitions for dump cycles.\n"
# define ERR_MSG_03 "C_RED Error: Invalid dump cycle.\n"
# define ERR_MSG_04 "C_RED Error: Invalid player set.\n"
# define ERR_MSG_05 "C_RED Error: Player Number has already been set.\n"
# define ERR_MSG_06 "C_RED Error: Max players already reached.\n"

/*
**		Strings:
*/

/*
** -----------
** Structures:
** -----------
*/

typedef unsigned long int ul_int;
typedef unsigned char char_u;
typedef unsigned char reg_t[REG_SIZE];

typedef struct	s_player
{
	char		*file_name; //passed in argv
	int			number; // if -n else the previous +1
	header_t	player_ref; // filled by Arno
}				t_player;

typedef struct	s_process
{
	t_player	*player;
	ul_int		pc;
	char		carry;
	int			cycle_to_next;
	reg_t		*registers; //malloc to REG_NUMBER
}				t_process;

typedef struct	s_env
{
	char_u		*memory; //malloc to MEM_SIZE
	int			num_players;
	t_player	players[MAX_PLAYERS];
	t_list		*processes;
	ul_int		cycle;
	int			dump_cycle;
}				t_env;

/*
** --------------------
*/

/*
**		Preprogramming prototypes:
*/
void			manage_args(t_env *env, int argc, char **argv);
void			run_simulation(t_env *env);

/*
**		read_program.c
*/
void			read_programs(t_env *env);

/*
**		error_quit.c
*/
void			error_quit(int error);
/*
**		free_env.c
*/
void			free_env(t_env *env);
/*
**		init_env.c
*/
int				ft_set_player_number(t_env *env, char *s1, char *s2);
int				ft_set_dump_cycle(t_env *env, char *str);
void			init_env(t_env *env);
/*
**		manage_args.c
*/
void			manage_args(t_env *env, int argc, char **argv);

#endif

/*
** register = 1 byite code 01
** direct = 4 code 10 define in op.h '%' else if index  byte = 2
** indirect = 2 code 11
*/

/*
**	Kesh:  1,   4,  7   0 assembler
**	Rob :  2,   3,  5,  8 run_simulation
**	Arno:  9,  10, 11, 12 read_program
**	Lee : 13,  14, 15, 16 manage_args, init & free
*/

/*
**end
*/
