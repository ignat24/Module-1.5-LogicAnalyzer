#include <Arduino.h>

constexpr uint8_t BUTTON_1=21;
constexpr uint8_t BUTTON_2=20;
constexpr uint8_t BUTTON_BUILTIN=0;

volatile uint32_t button_counter_1 = 0;  // volatile обов'язковий для змінних, які змінюються всередині ISR
volatile uint32_t button_counter_2 = 0;
volatile uint32_t button_counter_3 = 0;
uint32_t last_count_1 = 0; // Змінна для відслідковування змін у головному циклі
uint32_t last_count_2 = 0;
uint32_t last_count_3 = 0;

// Швидка функція обробки переривань (ISR), яка розміщується в оперативній пам'яті (IRAM)
void IRAM_ATTR button_isr_1() {
  button_counter_1++;
}

void IRAM_ATTR button_isr_2() {
  button_counter_2++;
}

void IRAM_ATTR button_isr_3() {
  button_counter_3++;
}

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_BUILTIN, INPUT_PULLUP);
  Serial.begin(115200);

  // Прив'язка переривання. FALLING означає спрацьовування при натисканні (перехід з 1 в 0)
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), button_isr_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), button_isr_2, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_BUILTIN), button_isr_3, FALLING);
}

void loop() {
  if (button_counter_1 != last_count_1) {
    last_count_1 = button_counter_1;
    Serial.print("Button 1 Pressed! Count: ");
    Serial.println(last_count_1);
  }

  if (button_counter_2 != last_count_2) {
    last_count_2 = button_counter_2;
    Serial.print("Button 2 Pressed! Count: ");
    Serial.println(last_count_2);
  }

  if (button_counter_3 != last_count_3) {
    last_count_3 = button_counter_3;
    Serial.print("Button BOOT Pressed! Count: ");
    Serial.println(last_count_3);
  }

  delay(10);
}