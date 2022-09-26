#define echoPin  2
#define trigPin  3
#define resetPin 4
#define g0 8
#define y0 9
#define r0 10
#define g1 11
#define y1 12
#define r1 13
#define len 6
#define default_delay 10
#define weight 0.5
#define trig_dist 50
int stt = -1;
float delay_;
float delay_t0 = default_delay;
float delay_t1 = default_delay;
boolean GO;
int state[4][8] = {{1,0,0,0,0,1,default_delay,0},{0,1,0,0,0,1,1,0},{0,0,1,1,0,0,default_delay,1},{0,0,1,0,1,0,1,1}};
long int checkpoint;
long int t1;
float duration1; 
float dist1;
boolean input2 = false;
boolean input1 = false;
boolean inc1 = false;
boolean inc2 = false;
float count1=0;
float count2=0;
float mul0 = 1.0;
float mul1 = 1.0;
float par0;
float par1;
float vetor0[len];
float vetor1[len];
int pos = 0;

void setup() {
  for(int i = 0; i < len; i++){
    vetor0[i]=0;
    vetor1[i]=0;
  }
  Serial.begin(9600);
  pinMode(g0,OUTPUT);
  pinMode(y0,OUTPUT);
  pinMode(r0,OUTPUT);
  pinMode(g1,OUTPUT);
  pinMode(y1,OUTPUT);
  pinMode(r1,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //
  pinMode(resetPin,INPUT_PULLUP);
  //
  delay(500);
  checkpoint = 0;
  delay_ = 0;
}

void loop() {
  
  if(millis() - checkpoint > delay_){
    stt++;
    if (stt == 4){
      stt = 0;
    }
    setlight();
    inc1 = false;
    inc2 = false;
  }
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  // receive, convert time (us) to cm
  duration1 = pulseIn(echoPin,HIGH);
  dist1 = duration1 * 0.034/2.;
  input2 = digitalRead(resetPin);
 
  if (dist1 < trig_dist){
    input1 = true;
  } else{
    input1 = false;
  }
  if (input1 == true){
    inc1 = true;
  }
  if (input2 == true){
    inc2 = true;
  }

  if (inc1==true && input1==false && not GO){
    count1 += 1;
    Serial.print(" count1 -- ");
    Serial.println(count1);
    inc1 = false;
  }
  if (inc2==true && input2==false && GO){
    count2 += 1;
    Serial.print(" count2 -- ");
    Serial.println(count2);
    inc2 = false;
  }
  //print
//Serial.print(count1);
//Serial.print(" --- ");
//Serial.println(count2);
delay(50);
}

void setlight(){
  if(state[stt][0]){
    vetor1[pos] = count2/delay_t1;
    count2 = 0;
    vetor0[pos] = count1/delay_t0;
    count1 = 0;
    pos++;
    if (pos == len) pos = 0;
    calc();
  }
    
  digitalWrite(g0,state[stt][0]);
  digitalWrite(y0,state[stt][1]);
  digitalWrite(r0,state[stt][2]);
  digitalWrite(g1,state[stt][3]);
  digitalWrite(y1,state[stt][4]);
  digitalWrite(r1,state[stt][5]);
  delay_ = state[stt][6] * 1000;
  if (state[stt][0]){
    delay_ = delay_ * mul0;
    delay_t0 = delay_ / 1000;
  }
  if (state[stt][3]){
    delay_ = delay_ * mul1;
    delay_t1 = delay_ / 1000;
  }
  GO = state[stt][7];
  checkpoint = millis();
}

void calc(){
  Serial.print("vetor0: ");
  for(int i = 0; i < len; i++){
    Serial.print(vetor0[i]);
    Serial.print(" -- ");
  }
  Serial.println(" ");
  Serial.print("vetor1: ");
  for(int i = 0; i < len; i++){
    Serial.print(vetor1[i]);
    Serial.print(" -- ");
  }
  Serial.println(" ");
  Serial.print("delayt0: ");
  Serial.println(delay_t0);
  Serial.print("delayt1: ");
  Serial.println(delay_t1);


  par0 = mean(vetor0) + weight;
  par1 = mean(vetor1) + weight;
  mul0 = 2*par0/(par0+par1);
  mul1 = 2*par1/(par0+par1);
  if(mul0 < 0.5) mul0 = 0.5;
  if(mul0 > 1.5) mul0 = 1.5;
  if(mul1 < 0.5) mul0 = 0.5;
  if(mul1 > 1.5) mul0 = 1.5;
}

float mean(float vec[]){
  float sum = 0;
  for(int i =0; i<len;i++){
    sum += vec[i];
  }
  return sum/len;
}
