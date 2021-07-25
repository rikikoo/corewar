#include "libft/includes/libft.h"

int	main(void)
{
	unsigned char str[9] = "0xef4b1a";

	ft_printf("%lu\n", ft_hextol(str));
}
