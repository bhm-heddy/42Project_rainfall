
int main(int ac,char **av)
{
  char buff[40];
  int integer;

  integer = atoi(av[1]);
  if (integer < 10)
  {
    memcpy(buff,av[2],integer * 4);
    if (integer == 0x574f4c46)
	{
      execl("/bin/sh","sh",0);
    }
  }
}
