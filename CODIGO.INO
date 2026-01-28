Creado por: Álvaro Herrero Lobo, 2024.
Los valores de los potenciometros deben ser modificados en funcion de los valores leidos en cada brazo, para ello es necesario realizar una medicion inicial y actualizar esos valores.

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT); //inversion giro bas
  pinMode(35, OUTPUT); //activacion base

  pinMode(8, OUTPUT); //inversion clapper
  pinMode(9, OUTPUT); //activacion clapper
  pinMode(10, OUTPUT); //inversion pinza
  pinMode(11, OUTPUT); //activacion pinza
  pinMode(23, OUTPUT); //activacion pinza
  pinMode(25, OUTPUT); //inversion pinza
  pinMode(31, OUTPUT); //activacion b2
  pinMode(33, OUTPUT); //inversion giro b2
  pinMode(27, OUTPUT); //activacion b1
  pinMode(29, OUTPUT); //inversion giro b1
}

void loop() {
  int MC = analogRead(A15);
  Serial.println("-------------- DATOS BRAZO ROBOT ---------------");
  Serial.print("MOTOR CURRENT: ");
  Serial.println(MC);

  //PROCESAMIENTO DATOS ROBOT
  int posBase = analogRead(A0);
  int GBase = 210 - map(posBase, 0, 677, 0, 210);
  Serial.print("POSICION ROBOT BASE: ");
  Serial.println(GBase);

  int posPinza1 = analogRead(A4);
  int GposPinza1 = map(posPinza1, 477, 866, 0, 140);
  Serial.print("POSICION ROBOT PINZA 1: ");
  Serial.println(GposPinza1);

  int posPinza2 = analogRead(A5);
  int GposPinza2 = map(posPinza2, 376, 777, 0, 140);
  Serial.print("POSICION ROBOT PINZA 2: ");
  Serial.println(GposPinza2);

  int posPinzaClap = analogRead(A2);
  int GposPinzaClap = map(posPinzaClap, 758, 577, 0, 100);
  Serial.print("POSICION ROBOT PINZA CLAP: ");
  Serial.println(GposPinzaClap);

  int posB2 = analogRead(A3);
  int GB2 = map(posB2, 100, 795, 0, 230);
  Serial.print("POSICION ROBOT B2: ");
  Serial.println(GB2);

  int posB1 = analogRead(A8);
  int GB1 = map(posB1, 65, 650, 0, 180);
  Serial.print("POSICION ROBOT B1: ");
  Serial.println(GB1);

  //PROCESAMIENTO DATOS MANDO
  int posMBase = analogRead(A6);
  int GMBase = map(posMBase, 0, 1023, 0, 210);
  Serial.print("POSICION MANDO BASE: ");
  Serial.println(GMBase);

  int posPinzaIncl = analogRead(A13);
  int GposPinzaIncl = map(posPinzaIncl, 0, 1023, 0, 140);
  Serial.print("POSICION MANDO INCL PINZA: ");
  Serial.println(GposPinzaIncl);
  
  int posPinzaClapper = analogRead(A10);
  int GposPinzaClapper = map(posPinzaClapper, 0, 1023, 0, 100);
  Serial.print("POSICION MANDO PINZA CLAPPER: ");
  Serial.println(GposPinzaClapper);

  int posMB2 = analogRead(A11);
  int GMB2 = map(posMB2, 230, 1000, 0, 230) - 5; // corrección de 5 grados
  Serial.print("POSICION MANDO B2: ");
  Serial.println(GMB2);

  int posMB1 = analogRead(A12);
  int GMB1 = map(posMB1, 367, 1023, 0, 180);
  Serial.print("POSICION MANDO B1: ");
  Serial.println(posMB1);

  //MOVIMIENTO

  if (MC < 1023) {
    //MOVIMIENTO BASE
    if (GMBase > GBase && GBase < 200) {
        if((GBase + 10) > GMBase){
        digitalWrite(12, LOW);
        digitalWrite(35, HIGH);  
        delay(40);
        digitalWrite(12, LOW);
        digitalWrite(35, LOW);
        delay(40);
      }
      else{
        digitalWrite(12, LOW);
        digitalWrite(35, HIGH);
      }
    }
    else if (GMBase < GBase && GBase > 10) {
      if((GBase - 10) < GMBase){      
        digitalWrite(12, HIGH);
        digitalWrite(35, HIGH);
        delay(40);
        digitalWrite(12, LOW);
        digitalWrite(35, LOW);
        delay(40);
    }
    else{
      digitalWrite(12, HIGH);
      digitalWrite(35, HIGH);      
    }
  }
    else {
      digitalWrite(12, LOW);
      digitalWrite(35, LOW);
    }

    //MOVIMIENTO PINZA    
    if (GposPinzaIncl >= GposPinza1 && GposPinzaIncl >= GposPinza2 && GposPinza1 < 110) {
      if ((GposPinza1 + 25) > GposPinzaIncl){
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);
      delay(40);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      delay(40);
      }
      else{
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(25, HIGH);        
      }
    }
    else if (GposPinzaIncl <= GposPinza1 && GposPinzaIncl <= GposPinza2 && GposPinza2 > 25) {
      if ((GposPinza1 - 25) < GposPinzaIncl){
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);
      delay(40);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
      delay(40);
      }
      else{
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(25, LOW);     
      }
    }
    else {
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(23, LOW);
      digitalWrite(25, LOW);
    }
    if (GposPinzaClapper >= GposPinzaClap && GposPinzaClap < 70) {
      if ((GposPinzaClapper + 10) > GposPinzaClap) {
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        delay(100);
      }
      else {
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
      }
    }

    else if (GposPinzaClapper <= GposPinzaClap && GposPinzaClap > 50) {
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
    }
    else {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
    //MOVIMIENTO BRAZOS
    if (GMB2 > GB2 && GB2 < 200) {
      if ((GB2 + 20) > GMB2) {
        digitalWrite(33, LOW);
        digitalWrite(31, HIGH);
        delay(30);
        digitalWrite(33, LOW);
        digitalWrite(31, LOW);
        delay(30);
      }
      else {
        digitalWrite(33, LOW);
        digitalWrite(31, HIGH);
      }
    }
    else if (GMB2 < GB2 && GB2 > 20) {
      if ((GB2 - 20) < GMB2) {
        digitalWrite(33, HIGH);
        digitalWrite(31, HIGH);
        delay(30);
        digitalWrite(33, LOW);
        digitalWrite(31, LOW);
        delay(30);
      }
      else {
        digitalWrite(33, HIGH);
        digitalWrite(31, HIGH);
      }
    }
    else {
      digitalWrite(33, LOW);
      digitalWrite(31, LOW);
    }

    if (GMB1 > GB1 && GB1 < 170) {
      if ((GB1 + 10) > GMB1) {
        digitalWrite(29, HIGH);
        digitalWrite(27, HIGH);
        delay(30);
        digitalWrite(29, LOW);
        digitalWrite(27, LOW);
        delay(30);
      }
      else {
        digitalWrite(29, HIGH);
        digitalWrite(27, HIGH);
      }
    }
    else if (GMB1 < GB1 && GB1 > 10) {
      if ((GB1 - 10) < GMB1) {
        digitalWrite(29, LOW);
        digitalWrite(27, HIGH);
        delay(30);
        digitalWrite(29, LOW);
        digitalWrite(27, LOW);
        delay(30);
      }
      else {
        digitalWrite(29, LOW);
        digitalWrite(27, HIGH);
      }
    }
    else {
      digitalWrite(29, LOW);
      digitalWrite(27, LOW);
    }
  }
  else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(23, LOW);
    digitalWrite(25, LOW);
    digitalWrite(31, LOW);
    digitalWrite(33, LOW);
    digitalWrite(27, LOW);
    digitalWrite(29, LOW);
  }
}
