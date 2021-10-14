int main(int ac,char **av)
{
  undefined4 *ptr_1;
  void *ptr_2;
  undefined4 *ptr_3;
  FILE *stream;

  ptr_1 = malloc(8);
  *ptr_1 = 1;
  ptr_2 = malloc(8);
  ptr_1[1] = ptr_2;
  ptr_3 = malloc(8);
  *ptr_3 = 2;
  ptr_2 = malloc(8);
  ptr_3[1] = ptr_2;

  ptrcpy((char *)ptr_1[1],av[1]);
  ptrcpy((char *)ptr_3[1],av[2]);

  stream = fopen("/home/user/level8/.pass","r");
  fgets(c,0x44,stream);
  puts("~~");
  return 0;
}
