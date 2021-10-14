
void greetuser(char *buf)
{
  void string;

  if (language == 1)
    string += "Hello" ;
  else if (language == 2)
      string += "Goedemiddag!";
  else if (language == 0)
        string += "Hyvää päivää";

  strcat((char *)&string, buf);
  puts((char *)&string);
  return;
}


int main(int ac,char **av)
{
	int i;
	undefined4 buff_1 [10];
	char buff_2 [36];
	char *S_ENV;

	strncpy((char *)buff_1,av[1],40);
	strncpy(buff_2,av[2],32);
	S_ENV = getenv("LANG");
	if (S_ENV != (char *)0x0)
	{
		i = memcmp(S_ENV,&DAT_FI,2);
		if (i == 0)
			language = 1;
	}
	else
	{
		i = memcmp(S_ENV,&DAT_NL,2);
		if (i == 0)
			language = 2;
		greetuser();
	}
