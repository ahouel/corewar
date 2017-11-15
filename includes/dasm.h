/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:14:54 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/15 12:15:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_dasm_env
{
	int								fd;
	int								sizeFile;
	unsigned char 		*file;
}										t_dasm_env;


/*
 ** ------ Display instructions ---------
*/
int print_dir4(int fd, unsigned char *str);
int print_dir2(int fd, unsigned char *str);
int print_reg(int fd, int reg);
int print_ind(int fd, unsigned char *str);
int print_args(int fd, int inst, unsigned char *str);

/*
 ** ------ Error -------
*/
void dasm_error(int err, char *str);
int len_is_label(char *str);

/*
 ** ----- Create file -----
*/
int ft_bin_len(unsigned char *str);
unsigned char *open_bin(t_dasm_env *env, int fd);
void create_file_cor(t_dasm_env *env, char *str);

/*
 ** ----- Get types ---
*/
int get_uint32(unsigned char *buff);
short get_uint16(unsigned char *buff);

#endif
