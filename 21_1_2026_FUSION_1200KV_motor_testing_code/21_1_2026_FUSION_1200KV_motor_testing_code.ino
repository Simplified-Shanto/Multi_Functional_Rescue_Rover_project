#include <Servo.h>

Servo esc;

void setup() {
  esc.attach(3);        // D3 pin
  esc.writeMicroseconds(1500); // NEUTRAL
  delay(5000);          // ESC arming time
}

void loop() {
  // Slowly go forward
  for (int pwm = 1500; pwm <= 1650; pwm += 5) {
    esc.writeMicroseconds(pwm);
    delay(100);
  }

  delay(3000);

  // Back to neutral
  esc.writeMicroseconds(1500);
  delay(3000);
}