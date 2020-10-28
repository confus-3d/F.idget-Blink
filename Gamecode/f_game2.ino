
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
