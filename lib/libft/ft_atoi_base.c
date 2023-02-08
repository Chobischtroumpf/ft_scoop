#include "libft.h"

int        ft_atoi_base(char *str, int str_base)
{
    int n;
    int i;
    int sign;
    int num;

    if (!str || (str_base < 2 || str_base > 16))
        return (0);
    i = 0;
    num = 0;
    sign = 1;
    while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
            str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
        ++i;
    if ((str[i] =='-' || str[i] == '+') && str[i++] == '-')
        sign *= -1;
    while (str[i])
    {
        n = str[i];
        if (n >= '0' && n <= '9')
            n -= '0';
        else if (n >= 'a' && n <= 'f')
            n -= 'a' - 10;
        else if (n >= 'A' && n <= 'F')
            n -= 'A' - 10;
        else 
            return (0);
        num = num * str_base + n;
        ++i;
    }
    return (sign * num);
}
