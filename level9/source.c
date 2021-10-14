#include <string.h>

void	*setannotation(char *dst, char *src)
{
	return (memcpy(dst, src, 10));
}


int main(int ac, char **av)
{
	char **s2;
	char s1[15];
	int ret;

	s2 = &s1;
	setannotation(s1, av[1]);

	ret = **s2;

	return ret;

}
