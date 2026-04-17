#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h> // Для random()

LiquidCrystal_I2C lcd(0x27, 20, 4); // Адрес I2C, 16 символов, 2 строки

// Рекурсивная функция для вычисления числа Фибоначчи
unsigned long fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Press button...");
  
  pinMode(2, INPUT_PULLUP); // Кнопка на пине 2
  randomSeed(analogRead(0)); // Инициализация генератора случайных чисел
}

void loop() {
  if (digitalRead(2) == LOW) { // Кнопка нажата
    delay(200); // Антидребезг

    // Генерация случайного числа от 5 до 30
    int n = random(5, 31);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rnd: " + String(n));

    // Замер времени
    unsigned long startTime = micros();
    unsigned long fib = fibonacci(n);
    unsigned long duration = micros() - startTime;

    // Вывод времени на вторую строку
    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(duration / 1000000.0, 5) + " sec");

    // Вывод числа Фибоначчи на третью строку (если дисплей 4-строчный)
    // Для 2-строчного — можно скроллить или выводить по очереди
    delay(2000); // Пауза для чтения
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fib: " + String(fib));
    
    delay(3000); // Пауза перед повтором
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press button...");
    
    while (digitalRead(2) == LOW); // Ожидание отпускания кнопки
  }
}