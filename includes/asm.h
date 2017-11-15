/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:13:15 by ahouel            #+#    #+#             */
/*   Updated: 2017/11/15 12:14:22 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define color(param) ft_printf("\033[%sm",param)

#define C_RED "31"
#define C_GREEN "32"
#define C_YELLOW "33"
#define C_BLUE "34"
#define C_MAGENTA "35"
#define C_CYAN "36"
#define C_RESET "0"

#define CHECK_MODE 0
#define PRINT_MODE 1
// asm_error(int ERROR, char *str, int line, int column)
#define ERROR_MIN 0
#define ERROR_MAX 27
#define NO_FILE_ERR 0
#define SOURCE_ERR 1
#define MALLOC_ERR 2
#define SIZE_ERROR 3
#define OPEN_ERROR 4
#define FILE_ERROR 5
#define INST_ERROR 6
#define LEX_ERROR 7
#define LABEL_ERROR 8
#define TOO_MUCH_ARG_ERR 9
#define BAD_ARG_REG 10
#define BAD_ARG_DIR 11
#define BAD_ARG_IND 12
#define BAD_ARG_REG_IND 13
#define BAD_ARG_REG_DIR 14
#define BAD_ARG_IND_DIR 15
#define BAD_ARG_REG_DIR_IND 16
#define NAME_SIZE_ERR 17
#define COM_SIZE_ERR 18
#define NAME_EXISTS 19
#define COM_EXISTS 20
#define COMMAND_ERR 21
#define NO_NAME 22
#define NO_COMMENT 23
#define NO_INSTRUCTIONS 24
#define NO_ARGUMENTS 25
#define WRONG_FORM_COM 26
#define SIZE_MAX_ERR 27

typedef struct s_asm_env
{
	struct s_tab_labs *labs;
	int              bytes;
	int							 size;
	int              fd;
	int								line;
	char							*current_line;
	char							*verbose_line;
	int								name;
	int								comment;
	int 							debug;
	int 							verbose;
	int								ko;
	int								print;
}                  t_asm_env;

typedef struct s_tab_labs
{
	char              *label;
	int               nb_oct;
	struct s_tab_labs  *next;
}                   t_tab_labs;

void free_labels(t_asm_env *env);
void print_labs_lst(t_tab_labs *lst);
/*
 ** -------- Create file ---------
*/
void create_file(t_asm_env *env, char *str);
int check_name(char *str);

/*
 ** -------- Analyse -------------
*/
int analyse(int oct, char *line, int i);
int analyse_args(int oct, char *line, int i);
void op_no_ocp(t_asm_env *env, int i, char *line);
void op_ocp(t_asm_env *env, int i, char *line);
char *moove_on_line(char *line);
int detect_arg(t_asm_env *env, char *line);
char *concat_opcode(char *ocp, int arg);

/*
 ** ---------- Read -------------
*/
void parse(t_asm_env *env, char *line, int printmode);
int goto_nextarg(char *line);
char *red_label_name(char *word, int len);

/*
 ** ---------- Parsing tools ---------
*/
int until_is_not_space(char *str);
int until_next_arg(char *str, t_asm_env *env, int col);
int len_is_label(char *line);

/*
 ** --------- Find op -----------
*/
int find_op(t_asm_env *env, char *word, char *line, int printmode);

/*
 ** --------- Check line --------------
*/
void check_instr(char *line, t_asm_env *env);
int check_op(char *instr, t_asm_env *env, int col);
void check_header();
void check_parse_arg(char *str, int instr, t_asm_env *env, int col);
void check_line(t_asm_env *env, char *line);

/*
 **---------- Lex instructions ---------
*/
void check_instr_endline(char *str, t_asm_env *env, int col);
void check_instr_1_9_12_15(char *str, t_asm_env *env, int col);
void check_instr_2_13(char *str, t_asm_env *env, int col);
void check_instr_3(char *str, t_asm_env *env, int col);
void check_instr_4_5(char *str, t_asm_env *env, int col);
void check_instr_6_7_8(char *str, t_asm_env *env, int col);
void check_instr_10(char *str, t_asm_env *env, int col);
void check_instr_11(char *str ,t_asm_env *env, int col);
void check_instr_14(char *str, t_asm_env *env, int col);
void check_instr_16(char *str, t_asm_env *env, int col);

/*
 ** ---------- Display ------------
*/
void write_reg(t_asm_env *env, char *line);
void write_dir(t_asm_env *env, char *line, int i);
void write_dir_short(t_asm_env *env, char *line, int nb, int a);
void write_dir_int(t_asm_env *env, char *line, int nb, int a);
void write_ind(t_asm_env *env, char *line);
void write_args(t_asm_env *env, char *line, int i);
void write_ocp(t_asm_env *env, char *ocp);

/*
 ** ------------ Check args -----------
*/
int is_ind(char *str);
int is_dir(char *str);
int is_reg(char *str);
int is_reg_or_ind(char *str, t_asm_env *env, int col);
int is_reg_or_dir(char *str, t_asm_env *env, int col);
int is_ind_or_dir(char *str, t_asm_env *env, int col);
int is_reg_or_ind_or_dir(char *str, t_asm_env *env, int col);


/*
 ** -------- Header -------------
*/

void write_comment(t_asm_env *env, char *line);
void write_name(t_asm_env *env, char *line);
void write_header(t_asm_env *env, char *line, int printmode);

/*
 ** --------- Labels ------------
*/
t_tab_labs *new_label(char *line, int bytes);
void create_label(t_tab_labs **labels, int bytes, char *line);
int dist_label(t_asm_env *env, char *label);
int is_label_str(char *str);
int is_label_char(char c);

/*
 ** ---------- Toolkit ----------
*/
int reverse_int(int nb);
short reverse_short(short nb);
int is_dir_int(int i);
int is_space(char c);
char *take_word(char *str);
//void	init_vm(t_vm *vm);

/*
 ** ------- Error -------
*/
void asm_error(int err, char *str, t_asm_env *env, int column);
void asm_error2(int err, char *str, t_asm_env *env, int column);

void verbose_inst(t_asm_env *env, char *ins, int hex);
void verbose_arg(t_asm_env *env, char *line, int add, int hex);
void verbose_lab(char *lab, int pos);
void verbose_dist_lab(int dist);
void verbose_ocp(t_asm_env *env, char ocp);
