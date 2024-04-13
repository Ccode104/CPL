
;; Function fib (fib, funcdef_no=0, decl_uid=1943, cgraph_uid=1, symbol_order=0)

int fib (int n)
{
  int D.1952;

  if (n <= 1) goto <D.1950>; else goto <D.1951>;
  <D.1950>:
  D.1952 = n;
  // predicted unlikely by early return (on trees) predictor.
  goto <D.1953>;
  <D.1951>:
  _1 = n + -1;
  _2 = fib (_1);
  _3 = n + -2;
  _4 = fib (_3);
  D.1952 = _2 + _4;
  // predicted unlikely by early return (on trees) predictor.
  goto <D.1953>;
  <D.1953>:
  return D.1952;
}



;; Function main (main, funcdef_no=1, decl_uid=1945, cgraph_uid=2, symbol_order=1)

void main ()
{
  int res;
  int a;

  a = 5;
  res = fib (a);
  return;
}


