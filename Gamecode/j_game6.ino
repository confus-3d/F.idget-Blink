
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
