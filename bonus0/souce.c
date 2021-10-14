void p(char *BUFF_PP,char *DAT_TIRET)
{
  char *ptr;
  char BUFF_P_4104 [4104];

  puts(DAT_TIRET);
  read(0,BUFF_P_4104,4096);
  ptr = strchr(BUFF_P_4104,10);
  *ptr = '\0';
  strncpy(BUFF_PP,BUFF_P_4104,20);
  return;
}

void pp(char *BUFF_MAIN_54)
{
  char BUFF_PP1_20 [20];
  char BUFF_PP2_20 [20];

  p(BUFF_PP1_20," - ");
  p(BUFF_PP2_20, " - ");
  strcpy(BUFF_MAIN_54,BUFF_PP1_20);
  int len = strlen(BUFF_MAIN_54) - 1;
  BUFF_MAIN_54[LEN] = ' ';
  strcat(BUFF_MAIN_54,BUFF_PP2_20);
  return;
}


int main(void)
{
  char buff_main [54];

  pp(buff_main);
  puts(buff_main);
  return 0;
}

