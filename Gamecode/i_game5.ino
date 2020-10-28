
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
