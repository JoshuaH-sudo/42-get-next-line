/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoban <jhoban@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:28:54 by jhoban            #+#    #+#             */
/*   Updated: 2025/12/01 12:31:52 by jhoban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_joinstr(char *dest, char *src)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	new_str = (char *)malloc((dest_len + src_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		new_str[i] = dest[i];
		i++;
	}
	j = 0;
	while (j < src_len)
	{
		new_str[i + j] = src[j];
		j++;
	}
	new_str[dest_len + src_len] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	int		index;
	char	*ptr_to_char;

	index = 0;
	if (!s)
		return (NULL);
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
		{
			ptr_to_char = (char *)&s[index];
			return (ptr_to_char);
		}
		index++;
	}
	if (s[index] == (char)c)
	{
		ptr_to_char = (char *)&s[index];
		return (ptr_to_char);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	*cleanup(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
