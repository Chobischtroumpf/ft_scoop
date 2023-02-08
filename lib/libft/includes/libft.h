/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:10:59 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 10:39:05 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int					ft_atoi(const char *str);
int					ft_atoi_base(char *str, int str_base);
char				*ft_itoa(int n);
char				*ft_itoa_base(long nbr, char *base, int b_len);
char				*ft_utoa_base(unsigned int n, char *base, int b_len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, unsigned int n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);

char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
size_t				ft_strlen(const char *src);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, char const *src, size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
ssize_t				ft_strnbr(char *s);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_numlen(int n, int minus);
char				**ft_split(char const *s, char c);

/*!
** @brief this function removes all the chars in set from the front and back of
** s1
** @param[in] s1 the first string
** @param[in] set the set of characters to remove from s1
** @return returns the string minus all the characters in set at the front or
** back of the string, or `NULL` in case of an error
*/
char				*ft_strtrim(char const *s1, char const *set);

/*!
** @brief this function joins two strings together
** @param[in] s1 the first string
** @param[in] s2 the second string
** @return returns the string made of s1 and s2, or `NULL` in case of an error
*/
char				*ft_strjoin(char const *s1, char const *s2);

/*!
** @brief this function joins two strings together up to r_size of the second string
** @param[in] s1 the first string
** @param[in] s2 the second string
** @param[in] r_size size of the second string to copy
** @return returns the string made of s1 and s2, or `NULL` in case of an error
*/
char				*ft_strnjoin(char const *s1, char const *s2, 
															ssize_t r_size);

/*!
** @brief this function finds a character in a string
** @param[in] str the string we're going through
** @param[in] c the character we're trying to find
** @return returns 1 if it finds c or 0 if it reaches the end of the string
*/
int					ft_haschr(const char *str, int c);

/*!
** @brief this function creates a string initialized with bzero
** @param[in] size the size of the new string
** @return returns a pointer to the created string or `NULL` in case of an error
*/
char				*ft_strnew(size_t size);

/*!
** @brief this function checks if last is at the end of str
** @param[in] str the string you want to check
** @param[in] last the element you want to find
** @return returns 1 if last is at the end of str, 0 otherwise
*/
int					ft_strlast(char const *str, char const *last);

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_strfree(char **cache, int ret);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
int					get_next_line(int fd, char **line);
int					ft_printf(const char *form, ...);


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));

#endif
