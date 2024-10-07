volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;  //0b 1000 0000
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;  //0b 1000 0001
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;  //0b 1000 0010
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;  //0b 0110 1111
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;  //0b 1000 0100
volatile unsigned char *myTIFR1  = (unsigned char *) 0x36;  //0b 0011 0110
volatile unsigned char *portDDRB = (unsigned char *) 0x24;  //0b 0010 0100
volatile unsigned char *portB    = (unsigned char *) 0x25;  //0b 0010 0101
volatile unsigned char in_char;
int frequency = 0;
//make sure to always use volatile keyword


void setup() {
  Serial.begin(9600);
  //TODO: Set PB6 to OUTPUT
  *portDDRB |= 0x01 << 6; 
  *portB &= ~(0x01 << 6);
  *myTCCR1A = 0x00;
  *myTCCR1B = 0x00;
  *myTCCR1C = 0x00;
  *myTIFR1 = 0x01;
}
void loop() 
{
  if(Serial.available() > 0){
    in_char = Serial.read();
  }
  switch(in_char){
    case 'q':
      frequency = 0;
      break;
    case 'a':
      frequency = 440;
      break;
    case 'b':
      frequency = 494;
      break;
    case 'c':
      frequency = 523;
      break;
    case 'd':
      frequency = 587;
      break;
    case 'e':
      frequency = 659;
      break;
    case 'f':
      frequency = 698;
      break;
    case 'g':
      frequency = 784;
      break;
  }
  if(frequency == 0){
    return;
  }
  *portB |= 0x01 << 6;
  my_delay(frequency);
  *portB &= ~(0x01 << 6);
  my_delay(frequency);
}
//replace '??' With your value
void my_delay(unsigned int freq)
{
  // calc period
  double period = 1.0/double(freq);
  // 50% duty cycle
  double half_period = period/ 2.0;
  // clock period def
  double clk_period = 0.0000000625;
  // calc ticks
  unsigned int ticks = half_period/clk_period;
  // stop the timer
  // TODO: Change prescaler to 0 (2, 1, and 0 bit).
  *myTCCR1B &= 0xF8; //0b 1111 1000
  // set the counts
  // TCNT timers can hold a 2 bytes worth of data
  *myTCNT1 = (unsigned int) (65536 - ticks);
  //Set TCCR1A to normal mode
  *myTCCR1A = 0x0;
  // start the timer
  * myTCCR1B |= 0x01; //0b 0000 0001
  // wait for overflow
  while((*myTIFR1 & 0x01)==0);
  // stop the timer
  *myTCCR1B = 0x0; //0b 1111 1000  
  // reset TOV           
  *myTIFR1 |= 0x01;
}
