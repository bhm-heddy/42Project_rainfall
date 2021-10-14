int main(int ac, char **av)
{
	int i = atoi(av[1]);

	if (i == 423)
		execv("/bin/sh", "/bin/sh");
	return 0;
}
