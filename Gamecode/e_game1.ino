
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
