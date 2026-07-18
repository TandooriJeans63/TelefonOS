#include <SD.h>

const int cs_pin = BUILTIN_SDCARD; // socket on Teensy 4.1
const int cs1_pin = 0;
const int cs2_pin = 10;
const int cs3_pin = 32;

// first card uses default "SD", others need to create their own SDClass instances
SDClass SD1;  // use SPI1  MOSI1=26, MISO1=1, SCK1=27
SDClass SD2;  // use SPI   MOSI=11, MISO=12, SCK=13
SDClass SD3;  // use SPI   MOSI=11, MISO=12, SCK=13

void setup() {
  // Start with all SPI CS pins HIGH
  pinMode(cs1_pin, OUTPUT); digitalWrite(cs1_pin, HIGH);
  pinMode(cs2_pin, OUTPUT); digitalWrite(cs2_pin, HIGH);
  pinMode(cs3_pin, OUTPUT); digitalWrite(cs3_pin, HIGH);
  delay(1);
  Serial.begin(9600);
  Serial.println("Four SD card demo start");
  const float oneGB = 1000000000.0;

  if (SD.begin(BUILTIN_SDCARD)) {
    Serial.println();
    Serial.print("SD is OK, size ");
    Serial.print(SD.totalSize() / oneGB);
    Serial.println(" GB");
    SD.sdfs.ls();
  } else {
    Serial.println();
    Serial.println("SD no card detected");
  }

  if (SD1.sdfs.begin(SdSpiConfig(cs1_pin, DEDICATED_SPI, SD_SCK_MHZ(16), &SPI1))) {
    Serial.println();
    SD1.mediaPresent(); // call mediaPresent() at least once after sdfs.begin()
    Serial.print("SD1 is OK, size ");
    Serial.print(SD1.totalSize() / oneGB);
    Serial.println(" GB");
    SD1.sdfs.ls();
  } else {
    Serial.println();
    Serial.println("SD1 no card detected");
  }

  if (SD2.sdfs.begin(SdSpiConfig(cs2_pin, SHARED_SPI, SD_SCK_MHZ(12), &SPI))) {
    Serial.println();
    SD2.mediaPresent(); // call mediaPresent() at least once after sdfs.begin()
    Serial.print("SD2 is OK, size ");
    Serial.print(SD2.totalSize() / oneGB);
    Serial.println(" GB");
    SD2.sdfs.ls();
  } else {
    Serial.println();
    Serial.println("SD2 not detected");
  }

  if (SD3.sdfs.begin(SdSpiConfig(cs3_pin, SHARED_SPI, SD_SCK_MHZ(12), &SPI))) {
    Serial.println();
    SD3.mediaPresent(); // call mediaPresent() at least once after sdfs.begin()
    Serial.print("SD3 is OK, size ");
    Serial.print(SD3.totalSize() / oneGB);
    Serial.println(" GB");
    SD3.sdfs.ls();
  } else {
    Serial.println();
    Serial.println("SD3 not detected");
  }
}

void loop() {
}
