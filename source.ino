//grupo augusto, lucas gomes, william de souza
#define KEYS 8
#define LEDS 8
#define NOTES 8

int i, j, k, pos = 0, mode = 0;
int leds[] = {A2,A1,2,3,4,5,6,7};
int keys[] = {A5,A4,A3,9,10,11,12,13};
float notes[] = {130.81,146.83,164.81,174.61,196.00,220.00,246.94,261.63};

int slot1[] = {42,0,0,4,4,5,5,4,3,3,2,2,1,1,0,4,4,3,3,2,2,1,4,4,3,3,2,2,1,0,0,4,4,5,5,4,3,3,2,2,1,1,0};
int slot2[] = {40,0,1,2,3,3,3,0,1,0,1,1,1,0,4,3,2,2,2,0,1,2,3,3,3,0,1,0,1,1,1,0,4,3,2,2,2,0,1,2,3};
int slot3[] = {39,4,1,2,3,4,3,2,1,0,0,2,4,3,2,1,1,2,3,4,2,0,0,3,5,7,6,5,4,2,4,3,2,1,2,3,4,2,0,0};

void setup() {

  Serial.begin(9600);
  
  for (i = 0; i < LEDS; i++){
  	pinMode(leds[i], OUTPUT);
  }
  for (i = 0; i < KEYS; i++){
  	pinMode(keys[i], INPUT);
  }
  
}

void loop() {

    if (mode == 0){

        for (i = 0; i < KEYS; i++){
            if (digitalRead(keys[i]) == HIGH){
                digitalWrite(leds[i], HIGH);  
                tone(A0, notes[i], 175);
                delay(200);
                digitalWrite(leds[i], LOW);
            }
        }

        if (digitalRead(8) == HIGH){
            menu();
        }

    } else if (mode == 1) {

        if (digitalRead(8) == HIGH){
            reset();
        }
        if (digitalRead(keys[3]) == HIGH){
            playSong(1);
        }
        if (digitalRead(keys[4]) == HIGH){
            playSong(2);
        }
        if (digitalRead(keys[5]) == HIGH){
            playSong(3);
        }
        if (digitalRead(keys[0]) == HIGH){
            learnSong(1);
        }
        if (digitalRead(keys[1]) == HIGH){
            learnSong(2);
        }
        if (digitalRead(keys[2]) == HIGH){
            learnSong(3);
        }

    }
  
    delay(20);
}

void learnSong(int song) {

turnLighsOff();
    pos = 0;
  
    if (song == 1)
        k = slot1[pos];
    if (song == 2)
        k = slot2[pos];
    if (song == 3)
        k = slot3[pos];

    pos++;

    while (pos <= k && stop() == false){

        if (song == 1)
          j = slot1[pos];
        if (song == 2)
          j = slot2[pos];
        if (song == 3)
          j = slot3[pos];

        digitalWrite(leds[j], HIGH);

        if (digitalRead(keys[j]) == HIGH){
            while (digitalRead(keys[j]) == HIGH){
                tone(A0, notes[j], 175);
                delay(200);
            }
            digitalWrite(leds[j], LOW);
            pos++;
        }

    }
  
}

void playSong(int song) {
  
turnLighsOff();
  pos = 0;
  
  if (song == 1)
    k = slot1[pos];
  if (song == 2)
    k = slot2[pos];
  if (song == 3)
    k = slot3[pos];
  
    for(i=1;i<=k;i++){
        pos++;
      Serial.println(notes[i]);
      
        if (song == 1)
          j = slot1[pos];
        if (song == 2)
          j = slot2[pos];
        if (song == 3)
          j = slot3[pos];
      if (stop()){
            reset();
            break;
        }
        tone(A0, notes[j], 200);
        digitalWrite(leds[j], HIGH);
        delay(300);
        digitalWrite(leds[j], LOW);
    }
    reset();
  
}

bool stop(){
	if (digitalRead(8) == HIGH)
      return true;
    return false;
}

void menu(){
    mode = 1;
    for (i = 0; i < LEDS; i++){
        digitalWrite(leds[i], HIGH);
    }
    delay(200);
}

void reset(){
    mode = 0;
    turnLighsOff();
    delay(200);
}

void turnLighsOff(){
    for (i = 0; i < LEDS; i++){
        digitalWrite(leds[i], LOW);
    }
}