#include <TeensyThreads.h>
#include <Arduino.h>

volatile int count;
volatile int count2;

void threadTest (int data) {
  while(1) {
    count += data;
    delay(100);
  }
}

Threads testthread;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  std::thread th1(threadTest, 1);
  th1.detach();
}

void loop() {
  // put your main code here, to run repeatedly:
  count2++;
  delay(200);
  // Serial.println("yousifisgay");
  Serial.print(count);
  Serial.print('/');
  Serial.println(count2);
}
