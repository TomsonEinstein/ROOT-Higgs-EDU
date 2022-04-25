#include "TStopwatch.h"
#include "TRandom2.h"

#include <iostream>


void tut18()
{
  TStopwatch t;

  TRandom2 *r = new TRandom2();

  double x = 0;

  for(int i = 0;i<1e9;i++)
  {
    x +=r->Rndm();
  }

  std::cout << x << std::endl;

  t.Print();
}

