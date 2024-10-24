/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:32:06 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/07 00:18:41 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *strs, ...);
void	parse_value(va_list ap, char *strs, int *total);
void	parse_text(char *strs, int *total);
void	parse_dex(va_list ap, char *strs, int *total);
void	parse_pointer(va_list ap, int *total);
void	parse_hex(va_list ap, char *strs, int *total);
void	parse_char(va_list ap, int *total);
void	parse_str(va_list ap, int *total);

#endif