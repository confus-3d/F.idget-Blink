
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
