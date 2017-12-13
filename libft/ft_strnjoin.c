
#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*s;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s = ft_strnew(ft_strlen(s1) + len + 1);
	join = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2 && len--)
		*s++ = *s2++;
	return (join);
}
