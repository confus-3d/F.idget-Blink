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
























          GAME SPOILERS BELOW THIS LINE.
          
*/

enum gameState {SELECTOR, TIME, MORSE, PAINT, AVOID, NUMBER, JUMP};  //Multigame mode
byte gameState = SELECTOR;
byte selectedGame = 1;//Starting game

//TIME & AVOID & PAINT
Timer timeTimer;
Timer wrongTimer;
int TIME_TIMER = 500;
byte timeFace;
byte wrongFace;
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
byte face6;

//MORSE & NUMBER
#define MAX_LEVEL 10
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
byte show;
byte imput;
byte light;
Timer pressed;

void setup() {
  // put your setup code here, to run once:
  randomize();
}

void loop() {
  setColor(OFF); //Clear display buffer

  if (buttonLongPressed()) { //Go to selector
    gameState = SELECTOR;
    resetLoop();
  }
  
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
}

void resetLoop(){
    TIME_TIMER = 500;
    timeTimer.set(TIME_TIMER);
    timeFace = 0;
    wrongFace = 3;
    reset = 0;
    rotation = 0;
    level = 1;
}

void selectorLoop() {
  if (buttonSingleClicked()){ //Rotate games
    if (timeTimer.isExpired()){
      selectedGame++;
      if (selectedGame > 6){selectedGame = 1;}
    }
  }
    switch (selectedGame){ //Show game preview
      case 1: //Time
      setColorOnFace( WHITE, 0); break;
      case 2: //Morse
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 3); setColorOnFace( WHITE, 4); break;
      case 3: //Paint
      setColor(WHITE); break;
      case 4: //Avoid
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 3); break;
      case 5: //Number
      setColorOnFace( WHITE, 0); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4);  break;
      case 6: //Jump
      setColorOnFace( WHITE, 1); setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4); setColorOnFace( WHITE, 5); break;
    }
  if (buttonDoubleClicked()){ //Select games and initial variables
    if (timeTimer.isExpired()){
      switch (selectedGame){
        case 1:
        gameState = TIME; break;
        case 2:
        gameState = MORSE; break;
        case 3:
        gameState = PAINT; break;
        case 4:
        gameState = AVOID;  break;
        case 5:
        gameState = NUMBER; break;
        case 6:
        gameState = JUMP; break;
      } 
    }
  }
}

void timeLoop() {
  if (buttonPressed()){
    if (timeFace == 0){
      TIME_TIMER = TIME_TIMER - ((random(2)+1)*10);
      timeRound.set(5000);
      rotation = random(1);
    }
    if (timeFace != 0){
      wrongFace = timeFace;
      wrongTimer.set(1000);
    }
  }
  
  if (timeTimer.isExpired()){
      timeTimer.set(TIME_TIMER);
      if (rotation == 0) {timeFace = (timeFace+1)%6;}
      else {timeFace = (timeFace+5)%6;}
      
  }
  if (!wrongTimer.isExpired()){setColorOnFace( RED, wrongFace);}
  setColorOnFace( GREEN, 0);
  setColorOnFace( WHITE, timeFace);

  if (timeRound.isExpired()){
    setColor(RED);
    if (reset == 0){
      wrongTimer.set(1000);
      reset = 1;
    }
    if (wrongTimer.isExpired()){
      timeRound.set(5000);
      resetLoop();
    } 
  }  
}

void morseLoop() { 
  if (level == 1){ //generate sequence
    for (int i = 0; i < MAX_LEVEL; i++){ 
      sequence[i] = random(1);
    }
    nextlevelLoop();
  }
  if (show < level){ //show sequence
    light = sequence[show];
    if (timeTimer.getRemaining() > 100) {
      if (light == 0) {setColorOnFace( WHITE, 0);}else {setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 3); setColorOnFace( WHITE, 4);}
    }
    if (timeTimer.isExpired() && sequence[show+1] == 0) {show++; timeTimer.set(TIME_TIMER);}
    if (timeTimer.isExpired() && sequence[show+1] == 1) {show++; timeTimer.set(TIME_TIMER*2);}
  }
  if (show == level){ //enter sequence
    if (imput < level){
      if (buttonSingleClicked()) {your_sequence[imput] = 0; reset = 1;}
      if (buttonPressed()) {pressed.set(200);}
      if (buttonReleased()) { if (pressed.isExpired()){your_sequence[imput] = 1; reset = 1;} }
      if (reset == 1){
        if (your_sequence[imput] != sequence[imput]){imput++; level = 0; reset = 0; wrongTimer.set(1000);}
        if (your_sequence[imput] == sequence[imput]){imput++; reset = 0; wrongTimer.set(1000);}
      } 
    }
    if (imput == level) {nextlevelLoop();}
  }
  if (level > 10){//win
    setColor(GREEN);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1;
      imput = 0;
      TIME_TIMER = TIME_TIMER - ((random(2)+1)*50);
      if (TIME_TIMER < 250) {TIME_TIMER = 250;} 
    }
  }
  if (level == 0){//lose
    setColor(RED);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1;
      imput = 0; 
      TIME_TIMER = 500;
    }
  }
}
void nextlevelLoop(){
      if (sequence[0] == 0) {timeTimer.set(TIME_TIMER);}
      else {timeTimer.set(TIME_TIMER*2);}
      show = 0;
      imput = 0;
      level++;
}

void paintLoop() {
  if (reset == 0){
    timeRound.set(10000);
    face0 = random(1);  face1 = random(1); face2 = random(1); face3 = random(1); face4 = random(1); face5 = random(1);
    reset = 1;
  }
  if (timeTimer.isExpired()){
    timeTimer.set(TIME_TIMER);
    face6 = face5; face5 = face4; face4 = face3; face3 = face2; face2 = face1; face1 = face0; face0 = face6;
  }

  if (buttonPressed()) face0 = (face0 + 1) % 2;
  
  if (face0==1) setColorOnFace( WHITE, 0);  if (face1==1) setColorOnFace( WHITE, 1);  if (face2==1) setColorOnFace( WHITE, 2);
  if (face3==1) setColorOnFace( WHITE, 3);  if (face4==1) setColorOnFace( WHITE, 4);  if (face5==1) setColorOnFace( WHITE, 5);
  setColorOnFace( GREEN, 0);
  if (!wrongTimer.isExpired()){setColor(GREEN);}
  if (face0 == 1 && face1 == 1 && face2 == 1 && face3 == 1 && face4 == 1 && face5 == 1){
    TIME_TIMER = TIME_TIMER - ((random(2)+1)*10);
    timeRound.set(10000);
    wrongTimer.set(500);
    reset = 0;
  }
  if (timeRound.isExpired()){
    setColor(RED);
    if (reset == 1){
      wrongTimer.set(1000);
      reset = 2;
    }
  }  
  if (timeRound.isExpired() && wrongTimer.isExpired()){
    timeRound.set(10000);
    resetLoop();
  } 
}

void avoidLoop() {
  if (reset == 0){
    if (timeTimer.isExpired()){
      rotation = random(2);
      if (rotation == 2) {wrongFace++;}
      if (wrongFace>5){wrongFace = 0; TIME_TIMER = TIME_TIMER - ((random(2)+1)*30);}
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
    resetLoop();
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
    if (timeTimer.getRemaining() > 100) {
      setColorOnFace( WHITE, 0);
      if (light == 1) {setColorOnFace( WHITE, 3);}
      if (light == 2) {setColorOnFace( WHITE, 2); setColorOnFace( WHITE, 4);}
    }
    if (timeTimer.isExpired()) {show++; timeTimer.set(TIME_TIMER);}
  }
  if (show == level){ //enter sequence
    if (imput < level){
      
      if (buttonDoubleClicked()) {your_sequence[imput] = 1; reset = 1;}
      if (buttonSingleClicked()) {your_sequence[imput] = 0; reset = 1;}
      if (buttonMultiClicked()) {your_sequence[imput] = 2; reset = 1;}
      if (reset == 1){
        if (your_sequence[imput] != sequence[imput]){imput++; level = 0; reset = 0; wrongTimer.set(1000);}
        if (your_sequence[imput] == sequence[imput]){imput++; reset = 0; wrongTimer.set(1000);}
      }
    }
    if (imput == level) {nextlevelLoop(); timeTimer.set(TIME_TIMER);}
  }
  if (level > 10){//win
    setColor(GREEN);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1;
      imput = 0;
      TIME_TIMER = TIME_TIMER - ((random(2)+1)*50);
      if (TIME_TIMER < 250) {TIME_TIMER = 250;}
    }
  }
  if (level == 0){//lose
    setColor(RED);
    if (wrongTimer.isExpired()){
      show = 0;
      level = 1; 
      imput = 0;
      TIME_TIMER = 500;
    }
  }
}

void jumpLoop() {
  if (timeTimer.isExpired()&& wrongTimer.isExpired()) { 
    wrongFace = (wrongFace+1)%6;
    timeTimer.set(TIME_TIMER*3);
  }
  if (buttonSingleClicked()) {
    timeFace++;
    if (timeFace>5){timeFace = 0;}
    if (rotation != timeFace) {wrongFace = timeFace;}
  }
  if (buttonDoubleClicked()) {
    timeFace = (timeFace + 2)%6; 
    if (rotation != timeFace) {wrongFace = timeFace;}
  }

  if (rotation == timeFace)  {rotation = (rotation +(random(1)+1)) % 6; TIME_TIMER = TIME_TIMER - ((random(2)+1)*5);}
  
  setColorOnFace( YELLOW, rotation);
  setColorOnFace( GREEN, timeFace);
  setColorOnFace( RED, wrongFace);
  
  if (wrongFace == timeFace){
    setColor(RED);
    if (reset == 0){
      wrongTimer.set(1000);
      reset++;
    }
  }
  if (reset == 1 && wrongTimer.isExpired()){
    resetLoop();
  } 
}
