/*
 Author: Kenny Z
 License: Creative Commons Attribution Share-Alike
 Description: A small keyboard that can play tones from 
 c7 to C8, with auto record, and a button for playback.
*/
#define SPK 13
#define PLAYBACK_BTN 12
#define BUFFERSIZE 160
int keys[] = {2,3,4,5,6,7,8,9};
int tones[] = {2093,1976,1760,1568,1397,1319,1175,1047}; // melhor tom
//int tones[] = {1047,1175,1319,1397,1568,1760,1976,2093};
char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
//int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

int length = sizeof keys/sizeof *keys;

// for recording
int count = 0;
int recorder[BUFFERSIZE];
unsigned long interval[BUFFERSIZE];
unsigned long pauseInterval[BUFFERSIZE];

void setup() {
  pinMode(SPK,OUTPUT);
  pinMode(PLAYBACK_BTN,INPUT);
  for(int i=0; i<length; i++){
    pinMode(keys[i],INPUT);
  }
}

void loop() {
  unsigned long startTime;
  static unsigned long pauseTime;
  static int playback_btn=0;
  int lastState = LOW;
  
  // prevent buffer overflow
  if(count>=BUFFERSIZE) count=0;

  // playback button
  if(digitalRead(PLAYBACK_BTN)==HIGH){
    playback();
    playback_btn=1;
  }
  
  // for each keyboard key
  for(int i=0; i<length; i++){
    //startTime = micros();
    startTime = millis();
    while(digitalRead(keys[i])==HIGH){
      if(playback_btn){
        // reset count after playback
        playback_btn = 0;
        count=0;
      }
      recorder[count]=i;
      tone(SPK,tones[i]);
      delay(200); // debounce
      lastState=HIGH;
    }
    if(lastState==HIGH){
      lastState=LOW;
      noTone(SPK);
      interval[count]=millis()-startTime;
      if(count)
        pauseInterval[count-1]=millis()-pauseTime;
      pauseTime=millis();
      count++;
    }
  }
}

void playback(){
  int index, key;
  for(int i=0; i<length; i++){
    pinMode(keys[i],OUTPUT);
  }
  for(int i=0; i<count; i++){
    index = recorder[i];
    key = keys[index];
    digitalWrite(key,HIGH);
    tone(SPK,tones[index]);
    delay(interval[i]);
    digitalWrite(key,LOW);
    noTone(SPK);
    delay(pauseInterval[i]);
  }
  for(int i=0; i<length; i++){
    pinMode(keys[i],INPUT);
  }
}
