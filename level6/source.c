void n(void)
{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void	m()
{
  puts("Nope");
  return;
}

void 	main(int ac,char **av)
{
  char *dest;
  code **ppcVar1;

  dest = (char *)malloc(0x40);
  ppcVar1 = (code **)malloc(4);
  *ppcVar1 = m;
  strcpy(__dest,av[1]);
  (**ppcVar1)();
  return;
}
