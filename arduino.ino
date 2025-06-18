const int DIR = 26;
const int STEP = 28;
int anguloActual = 0;
int anguloObjetivo = 0;

void setup() {
  // Configurar pines como salida
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600);      // Comunicación con el módulo HC-05
  Serial.println("Sistema listo. Ingrese angulo objetivo (0-360):");
}

void loop() {
  // Leer ángulo objetivo desde el puerto serial
  if (Serial1.available()) {           // Si hay datos en el buffer de Serial2
    String mensaje = Serial1.readStringUntil('\n'); // Lee hasta salto de línea
    int anguloObjetivo = mensaje.toInt();
    Serial.print("Recibido: ");
    Serial.println(anguloObjetivo);          // Muestra en el monitor serial
  

    
    // Calcular diferencia angular
    float delta = fmod((anguloObjetivo - anguloActual + 360.0), 360.0);
    
    // Determinar dirección óptima
    if (delta > 180.0) {
      delta = 360.0 - delta;
      digitalWrite(DIR, HIGH); // Sentido horario
      Serial.println("Direccion: Horario");
    } else {
      digitalWrite(DIR, LOW); // Sentido antihorario
      Serial.println("Direccion: Antihorario");
    };
    
    // Convertir grados a pasos (asumiendo 1.8°/paso, 200 pasos/rev)
    int pasosNecesarios = delta / 1.8;
    
    // Generar los pulsos
    for(int i = 0; i < pasosNecesarios; i++) {
      digitalWrite(STEP, HIGH);
      delay(4); // Medio paso en microsegundos
      digitalWrite(STEP, LOW);
      delay(4);
    }
    
    // Actualizar posición actual
    anguloActual = anguloObjetivo;
  }
}