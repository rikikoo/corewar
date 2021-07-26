#include "libft/includes/libft.h"

int	main(void)
{
	unsigned char str[11] = "0x0000";

	ft_printf("%lu\n", ft_hextol(str));
}
