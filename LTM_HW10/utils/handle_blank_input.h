void custom_fflush_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}