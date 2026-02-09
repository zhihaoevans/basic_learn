#include <stdio.h>

struct child {
  char name[10];
  enum { boy, girl } gender;
};

struct child he = { "Tom", boy };

int main (void)
{
  static struct child she = { "Jerry", girl };
  printf ("Hello %s %s.\n", he.gender == boy ? "boy" : "girl", he.name);
  printf ("Hello %s %s.\n", she.gender == boy ? "boy" : "girl", she.name);
  return 0;
}
