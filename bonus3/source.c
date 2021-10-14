int	main(int ac,char **av)
{
  int i;
  char *buff[66];
  FILE *FILE;

  FILE = fopen("/home/user/end/.pass","r");
  if ((FILE == (FILE *)0x0) || (ac != 2))
	  return -1;
  else
  {
    fread(buff, 1, 66, FILE);
    i = atoi(av[1]);
    buff[i] = 0;
    fclose(FILE);
    i = strcmp(buff,av[1]);
    if (i == 0)
      execl("/bin/sh","sh",0);
	i = 1;
  }
  return i;
}
