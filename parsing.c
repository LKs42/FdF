#include "fdf.h"

int	check_extension(char *str, char *extension)
{
	return (ft_strcmp(str + ft_strlen(str) - ft_strlen(extension), extension) == 0) ? 0 : 1;
}