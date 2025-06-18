const int xPin = 14;  // Eje X del joystick (conectar a GPIO34)
const int yPin = 12;  // Eje Y del joystick (conectar a GPIO35)
const int swPin = 13; // Botón del joystick (conectar a GPIO22)
float angulo;
float anguloenviar;
int intangulo;
String stringangulo; 
#define RX1_PIN 16  // GPIO16 como RX1 (conectar a TX del HC-05)
#define TX1_PIN 17  // GPIO17 como TX1 (conectar a RX del HC-05)

void setup() {
  Serial.begin(115200); // Inicia comunicación serial a mayor velocidad
  Serial1.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN); // 9600 baudios es común en HC-05
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Configura resistencia pull-up interna para el botón
  
  Serial.println("Iniciando lectura de joystick...");
  Serial.println("Formato: X:valor | Y:valor | Botón:estado");
  Serial.println("----------------------------------------");
}

float joystickToAngle(int x_raw, int y_raw, int centro = 2048) {
  int x = x_raw - centro;
  int y = y_raw - centro;
  float ang = atan2(y, x) * 180.0 / PI;
  return (ang < 0) ? ang + 360 : ang;
}


void loop() {
  // Leer valores crudos del joystick
  int xVal = analogRead(xPin);
  xVal = 4095 - xVal; 
  int yVal = analogRead(yPin);
  yVal = 4095 - yVal;
  int btnVal = digitalRead(swPin); // 0=presionado, 1=no presionado (por pull-up)

    

  // Mostrar valores por serial
  Serial.print("X:"); Serial.print(xVal);
  Serial.print(" | Y:"); Serial.print(yVal);
  Serial.print(" | Botón:"); Serial.println(btnVal ? "NO" : "SI");

  if (!((xVal > 2000 && xVal < 3000) && (yVal > 2000 && yVal < 3000))) {
    // Aquí entra si x o y están fuera del rango de zona muerta
    Serial.print("Ángulo: ");
    anguloenviar = joystickToAngle(xVal, yVal);
    intangulo = (int)anguloenviar;
    stringangulo = String(intangulo);

    Serial.println(stringangulo);
    Serial1.println(stringangulo);
  }

  delay(50); // Pequeña pausa para evitar saturación
}
