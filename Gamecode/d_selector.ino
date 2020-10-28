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
