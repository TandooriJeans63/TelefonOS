#include <SD.h>

unsigned int count = 0;

void setup() {
  Serial.begin(9600);
  if (SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card present at begin");
  } else {
    Serial.println("no SD card found at begin");
  }
}

void loop() {
  count = count + 1;
  Serial.print("count = ");
  Serial.print(count);
  Serial.print(":  ");
  if (SD.mediaPresent()) {
    Serial.println("SD card is present");
    File f = SD.open("test.txt", FILE_WRITE); // appends unless FILE_WRITE_BEGIN
    if (f) {
      f.print("test ");
      f.println(count);
      f.flush();
      f.close();
    } else {
      Serial.println(" error appendint to test.txt");
    }
  } else {
    Serial.println("SD card absent");
  }
  delay(2500);
}
