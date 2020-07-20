/*
          
          Fidget Blink
          Lead development by FJ Rios
          ONE Blink (No more, and of course, no less)
          
          Rules:
          Click to change game.
          Double click to select game.
          Hold to return game selection.
          6 available games.
          Pick a game & Play. 
          No more rules provided.
          
          
          
          
          
          
          
          
          
          
          
          










          
          
          
          
          
          
          
                    
          STOP READING
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          STOP READING OR WE WILL CALL THE POLICE
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          






          
          SPOILERS BELOW THIS LINE
*/



enum gameState {SELECTOR, TIME, MORSE, PAINT, AVOID, NUMBER, JUMP};  //Multigame mode
byte gameState = SELECTOR;
byte selectedGame = 1;//Starting game

//TIME & AVOID & PAINT
Timer timeTimer;
Timer wrongTimer;
int TIME_TIMER = 500;
byte timeFace = 0;
byte wrongFace = 0;
Timer timeRound;
byte reset = 0;
byte rotation = 0;

//PAINT
byte face0;
byte face1;
byte face2;
byte face3;
byte face4;
byte face5;

//MORSE & NUMBER
#define MAX_LEVEL 10
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
byte show;
byte imput;
byte light;
Timer pressed;

//JUMP
int brightness=255;
byte step = 10;
byte wrongFaceb;

void setup() {
  // put your setup code here, to run once:
  randomize();
}

void loop() {
  setColor(OFF); //Clear display buffer
  switch (gameState) { //Detects gamestate
    case SELECTOR:
      selectorLoop();
      break;
    case TIME:
      timeLoop();
      break;
    case MORSE:
      morseLoop();
      break;
    case PAINT:
      paintLoop();
      break;
    case AVOID:
      avoidLoop();
      break;
    case NUMBER:
      numberLoop();
      break;
    case JUMP:
      jumpLoop();
      break;
  }
  if (buttonLongPressed()) { //Go to selector
    gameState = SELECTOR;
    TIME_TIMER = 500;
    timeTimer.set(TIME_TIMER);
    timeFace = 0;
    wrongFace = 3;
    reset = 0;
    rotation = 0;
    level = 1;
    wrongFaceb = 2;
  }
}

void selectorLoop() {
  if (buttonSingleClicked() && timeTimer.isExpired()){ //Rotate games
    selectedGame++;
    if (selectedGame > 6){
      selectedGame = 1;
    }
  }
    switch (selectedGame){ //Show game preview
      case 1: //Time
      setColorOnFace( WHITE, 0);
      break;
      case 2: //Morse
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 3); setColorOnFace( WHITE, 4);
      break;
      case 3: //Paint
      setColor(WHITE);
      break;
      case 4: //Avoid
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 3);
      break;
      case 5: //Number
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4);
      break;
      case 6: //Jump
      setColorOnFace( WHITE, 1); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4); setColorOnFace( WHITE, 5);
      break;
    }
  if (buttonDoubleClicked()){ //Select games and initial variables
    switch (selectedGame){
      case 1:
      gameState = TIME;
      timeRound.set(5000);
      break;
      case 2:
      gameState = MORSE;
      break;
      case 3:
      gameState = PAINT;
      break;
      case 4:
      gameState = AVOID;
      break;
      case 5:
      gameState = NUMBER;
      break;
      case 6:
      gameState = JUMP;
      rotation = 2;
      brightness = 255;
      break;
    }
  }
}

void timeLoop() {
  if (!timeRound.isExpired()){
    if (timeTimer.isExpired()){
      timeTimer.set(TIME_TIMER);
      if (rotation == 0) timeFace = (timeFace+1)%6;
      if (rotation == 1 && timeFace == 0)timeFace = 5;
      if (rotation == 1 && timeFace > 0) timeFace--;
      
    }
    setColorOnFace( WHITE, timeFace);
    setColorOnFace( GREEN, 0);
    if (!wrongTimer.isExpired()){setColorOnFace( RED, wrongFace);}
  }
  if (buttonPressed() && timeFace == 0){
    TIME_TIMER = TIME_TIMER - ((random(2)+1)*5);
    timeRound.set(5000);
    rotation = random(1);
  }
  if (buttonPressed() && timeFace > 0){
    wrongFace = timeFace;
    wrongTimer.set(1000);
  }
  if (timeRound.isExpired()){
    setColor(RED);
    if (reset == 0){
      wrongTimer.set(1000);
      reset++;
    }
  }  
  if (timeRound.isExpired() && wrongTimer.isExpired()){
    timeRound.set(5000);
    TIME_TIMER = 500;
    reset=0;
    timeFace = 0;
  } 
}

void morseLoop() { 
    if (level == 1){ //generate sequence
    for (int i = 0; i < MAX_LEVEL; i++){ 
      sequence[i] = random(1);
    }
    if (sequence[0] == 0) timeTimer.set(TIME_TIMER);
    if (sequence[0] == 1) timeTimer.set(TIME_TIMER*2);
    show = 0;
    imput = 0;
    level++;
  }
  if (show < level){ //show sequence
    light = sequence[show];
    if (light == 0) {setColorOnFace( WHITE, 0);} else {setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 3); setColorOnFace( WHITE, 4);}
    if (timeTimer.isExpired() && sequence[show+1] == 0) {show++; timeTimer.set(TIME_TIMER);}
    if (timeTimer.isExpired() && sequence[show+1] == 1) {show++; timeTimer.set(TIME_TIMER*2);}
  }
  if (show == level){ //enter sequence
    if (imput < level){
      if (buttonPressed()) {pressed.set(500);}
      if (buttonReleased()) {
        if (!pressed.isExpired()){your_sequence[imput] = 0; reset++;}
        if (pressed.isExpired()){your_sequence[imput] = 1; reset++;}
      }
      if (reset == 1){
        if (your_sequence[imput] != sequence[imput]){level = 0; reset = 0; wrongTimer.set(1000);}
        if (your_sequence[imput] = sequence[imput]){imput++; reset = 0; wrongTimer.set(1000);}
      }
    }
  }
  if (imput == level){//win
    setColor(GREEN);
    if (wrongTimer.isExpired()){
      show = 0;
      level++; 
      if (level == MAX_LEVEL){TIME_TIMER = TIME_TIMER - ((random(2)+1)*50); level = 1;}
    }
  }
  if (level==0){//lose
    setColor(RED);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1; 
      TIME_TIMER = 500;
    }
  }
}

void paintLoop() {
  if (reset == 0){
    timeRound.set(5000);
    face0 = random(1);
    face1 = random(1);
    face2 = random(1);
    face3 = random(1);
    face4 = random(1);
    face5 = random(1);
    reset++;
  }
  if (timeTimer.isExpired()){
    timeTimer.set(TIME_TIMER);
    byte face6;
    face6 = face5; face5 = face4; face4 = face3; face3 = face2; face2 = face1; face1 = face0; face0 = face6;
  }
  if (face0==1) setColorOnFace( WHITE, 0);
  if (face1==1) setColorOnFace( WHITE, 1);
  if (face2==1) setColorOnFace( WHITE, 2);
  if (face3==1) setColorOnFace( WHITE, 3);
  if (face4==1) setColorOnFace( WHITE, 4);
  if (face5==1) setColorOnFace( WHITE, 5);
  if (buttonPressed()) face0 = (face0 + 1) % 2;
  if (face0 == face1 && face1 == face2 && face2 == face3 && face3 == face4 && face4 == face5 && face1 == 1){
    TIME_TIMER = TIME_TIMER - ((random(2)+1)*10);
    timeRound.set(5000);
    reset = 0;
  }
  if (timeRound.isExpired()){
    setColor(RED);
    if (reset == 1){
      wrongTimer.set(1000);
      reset++;
    }
  }  
  if (timeRound.isExpired() && wrongTimer.isExpired()){
    timeRound.set(5000);
    TIME_TIMER = 500;
    reset = 0;
  } 
}

void avoidLoop() {
  if (reset == 0){
    if (timeTimer.isExpired()){
      rotation = random(2);
      if (rotation == 2) {wrongFace++;}
      if (wrongFace>5){wrongFace = 0; TIME_TIMER = TIME_TIMER - ((random(2)+1)*50);}
      timeTimer.set(TIME_TIMER);
    }
    if (buttonPressed()){
      timeFace++;
      if(timeFace>5){timeFace = 0;}
    } 
  setColorOnFace( RED, wrongFace);
  setColorOnFace( GREEN, timeFace);
  }
  if (timeFace == wrongFace){
    setColor(RED);
    if (reset == 0){
      wrongTimer.set(1000);
      reset++;
    }
  }
    if (reset == 1 && wrongTimer.isExpired()){
    reset = 0;
    wrongFace = 3;
    timeFace = 0;
    TIME_TIMER = 500;
  } 
}

void numberLoop() {
  if (level == 1){ //generate sequence
    for (int i = 0; i < MAX_LEVEL; i++){ 
      sequence[i] = random(2);
    }
    timeTimer.set(TIME_TIMER);
    show = 0;
    imput = 0;
    level++;
  }
  if (show < level){ //show sequence
    light = sequence[show];
    if (light == 0) {setColorOnFace( WHITE, 0);}
    if (light == 1) {setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 3);}
    if (light == 2) {setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4);}
    if (timeTimer.isExpired()) {show++; timeTimer.set(TIME_TIMER);}
  }
  if (show == level){ //enter sequence
    if (imput < level){
      if (buttonSingleClicked()) {your_sequence[imput] = 0; reset++;}
      if (buttonDoubleClicked()) {your_sequence[imput] = 1; reset++;}
      if (buttonMultiClicked()) {if (buttonClickCount() == 3) {your_sequence[imput] = 2; reset++;}}
      if (reset == 1){
        if (your_sequence[imput] != sequence[imput]){level = 0; reset = 0; wrongTimer.set(1000);}
        if (your_sequence[imput] = sequence[imput]){imput++; reset = 0; wrongTimer.set(1000);}
      }
    }
  }
  if (imput == level){//win
    setColor(GREEN);
    if (wrongTimer.isExpired()){
      show = 0;
      level++; 
      if (level == 10){TIME_TIMER = TIME_TIMER - ((random(2)+1)*50); level = 1;}
    }
  }
  if (level == 0){//lose
    setColor(RED);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1; 
      TIME_TIMER = 500;
    }
  }
}

void jumpLoop() {
  if (timeTimer.isExpired()) { 
    if (brightness - step < 0 ) {
      brightness = 255;
      wrongFace = wrongFace+1;
      wrongFaceb = wrongFaceb+1;
      if (wrongFace > 5)wrongFace = wrongFace - 6;
      if (wrongFaceb > 5)wrongFaceb = wrongFaceb - 6;
    }
    brightness -= step;  
    timeTimer.set(100);
  }
  if (buttonSingleClicked()) {timeFace = timeFace + 1; if (rotation != timeFace) wrongFace = timeFace;}
  if (buttonDoubleClicked()) {timeFace = timeFace + 2; if (rotation != timeFace) wrongFace = timeFace;}
  if (buttonMultiClicked()) {if (buttonClickCount() == 3) {timeFace = timeFace + 3; if (rotation != timeFace) wrongFace = timeFace;}}
  if (timeFace > 5)timeFace = timeFace - 6;
  if (rotation == timeFace){
    rotation = (rotation + (random(2)+1)) % 6;
  }
  setColorOnFace( YELLOW, rotation);
  setColorOnFace( WHITE, timeFace);
  setColorOnFace( dim( RED,  255 - brightness  ), wrongFace);
  setColorOnFace( dim( RED,  brightness  ), wrongFaceb);
  if (wrongFace == timeFace){
    setColor(RED);
    if (reset == 0){
      wrongTimer.set(1000);
      reset++;
    }
  }
  if (reset == 1 && wrongTimer.isExpired()){
    reset = 0;
    wrongFace = 3;
    wrongFaceb = 2;
    timeFace = 0;
    rotation = 2;
    brightness = 255;
  } 
}
