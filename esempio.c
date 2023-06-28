#include <stdio.h>
#include "c_timer.h"

int main(int argc, char** argv) {
  double btime, etime;
  int i;
  double tmp = 0;
  
  btime = get_cur_time(); //inizio blocco da monitorare
  for (i = 0; i < 100000; i++) tmp += 0.09;

  etime = get_cur_time();  //fine blocco da monitorare
  
  printf("tempo trascorso: %f secondi\n", etime-btime);

  return 0;
}
