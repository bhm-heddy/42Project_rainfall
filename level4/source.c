void p(char *param_1)
{
  printf(param_1);
  return;
}

void n(void)
{
  char buff [520];
  
  fgets(buff,512,stdin);
  p(buff);
  if (m == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}

void main(void)

{
  n();
  return;
}
