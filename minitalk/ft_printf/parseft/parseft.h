/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:32:06 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/21 16:28:45 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEFT_H
# define PARSEFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

char	*ft_itoa(int n);
char	*ft_itou(int n);
char	*ft_itoh(unsigned int n, int flag);
char	*ft_itop(unsigned long n);

#endif