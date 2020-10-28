
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
