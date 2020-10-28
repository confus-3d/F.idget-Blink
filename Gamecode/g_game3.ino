
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
