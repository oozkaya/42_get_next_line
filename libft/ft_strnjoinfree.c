#include "libft.h"

char	*ft_strnjoinfree(char const *s1, char const *s2, size_t len, int pick)
{
	char	*join;

	if (pick < 0 || pick > 2)
		return (NULL);
	join = ft_strnjoin(s1, s2, len);
	if (pick == 0 || pick == 2)
		free((char*)s1);
	if (pick == 1 || pick == 2)
		free((char*)s2);
	return (join);
}
