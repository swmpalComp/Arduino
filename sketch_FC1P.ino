const int FC_1P_CLK = 12;
const int FC_1P_PS = 8;
const int FC_1P_DAT = 7;

int state_dat = 0;
int loopi = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(FC_1P_CLK, OUTPUT);
  pinMode(FC_1P_PS, OUTPUT);
  pinMode(FC_1P_DAT, INPUT); 

  // debug serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // 周期開始
  if (loopi % 16 == 0){
    loopi = 0;
    digitalWrite(FC_1P_PS, HIGH);
  }

  // クロックを与えて押下判定
  digitalWrite(FC_1P_CLK, HIGH);
  delay(1);
  state_dat = digitalRead(FC_1P_DAT);

  if (state_dat == LOW){
    switch (loopi){
      case 0:
        Serial.println("A");
        break;
      case 1:
        Serial.println("B");
        break;
      case 2:
        Serial.println("Select");
        break;
      case 3:
        Serial.println("Start");
        break;
      case 4:
        Serial.println("Up");
        break;
      case 5:
        Serial.println("Down");
        break;
      case 6:
        Serial.println("Left");
        break;
      case 7:
        Serial.println("Right");
        break;
    }
    
  }

  // 次のクロックへ
  digitalWrite(FC_1P_CLK, LOW);
  digitalWrite(FC_1P_PS, LOW);
  loopi = loopi + 1;;

  delay(1);

}
