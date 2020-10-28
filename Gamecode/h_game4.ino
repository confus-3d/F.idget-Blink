
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
