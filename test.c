void changeFirst(int x[]) {
  x[0] = 14;
}

int main (void) {
  int x[] = {1, 2, 3, 4};
  changeFirst(x);
  
  printf("%d\n", x[0]);
}
