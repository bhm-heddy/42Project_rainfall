
void p(void)
{
  char input [64];
  uint param_1;
  
  fflush(stdout);
  gets(input);
  if ((param_1 & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n",param_1);
    _exit(1);
  }
  puts(input);
  strdup(input);
  return;
}

void main(void)

{
  p();
  return;
}
