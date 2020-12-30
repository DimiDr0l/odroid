#include <wiringPi.h>
#include <softPwm.h>

#define FTEMP     "/sys/class/thermal/thermal_zone0/temp"
#define THRESHOLD 60
#define GPIO_PIN  1

int os_read_d(char  *fname) {
  FILE* fd = fopen(fname, "r");

  if (fd == NULL) {
    return -1;
  }
  char inp[64];
  inp[0] = 0;
  fgets(inp, 64, fd);
  return strtoul(inp, NULL, 10);
}

void main(void) {
  int temperature;

  wiringPiSetup();
  softPwmCreate (GPIO_PIN, 0, 100);
  
  while(1) {
     temperature = os_read_d(FTEMP)/1000;

     if (temperature >= THRESHOLD && temperature <= THRESHOLD + 3 ) {
		softPwmWrite (GPIO_PIN, 50) ;
	 } else if (temperature > THRESHOLD + 3 && temperature <= THRESHOLD + 5 ) {
		softPwmWrite (GPIO_PIN, 75) ;
	 } else if (temperature > THRESHOLD + 5) {
		softPwmWrite (GPIO_PIN, 100) ;
     } else {
		softPwmWrite (GPIO_PIN, 0) ;
	 }
	 delay(5000);
  }
}
