#include <M5Cardputer.h>
#include <WiFi.h>

int menu = 0;
String items[4] = {"1. WiFi SCAN", "2. RADAR", "3. SYSTEM INFO", "4. ABOUT"};

void drawMenu() {
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.setTextColor(GREEN, BLACK);
  M5Cardputer.Display.setTextSize(2);
  M5Cardputer.Display.setCursor(10, 10);
  M5Cardputer.Display.println("CYBER_OS v1.0");
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setCursor(10, 35);
  M5Cardputer.Display.println("M5Stack Cardputer - READY");
  M5Cardputer.Display.drawLine(0, 50, 240, 50, GREEN);
  for (int i = 0; i < 4; i++) {
    M5Cardputer.Display.setCursor(15, 65 + i * 18);
    if (i == menu) M5Cardputer.Display.setTextColor(BLACK, GREEN);
    else M5Cardputer.Display.setTextColor(GREEN, BLACK);
    M5Cardputer.Display.println(items[i]);
  }
  M5Cardputer.Display.setTextColor(GREEN, BLACK);
  M5Cardputer.Display.setCursor(10, 150);
  M5Cardputer.Display.println("UP/DOWN + ENTER");
}

void wifiScan() {
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.setTextColor(GREEN, BLACK);
  M5Cardputer.Display.setCursor(10, 10);
  M5Cardputer.Display.println("SCANNING WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.setCursor(10, 10);
  M5Cardputer.Display.print("Found: ");
  M5Cardputer.Display.println(n);
  for (int i = 0; i < n && i < 8; i++) {
    M5Cardputer.Display.setCursor(10, 30 + i * 13);
    M5Cardputer.Display.print(WiFi.SSID(i));
    M5Cardputer.Display.print(" ");
    M5Cardputer.Display.print(WiFi.RSSI(i));
    M5Cardputer.Display.println("dB");
  }
  M5Cardputer.Display.setCursor(10, 150);
  M5Cardputer.Display.println("Press ENTER for MENU");
}

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  drawMenu();
}

void loop() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      auto keys = M5Cardputer.Keyboard.keysState();
      for (auto k : keys.word) {
        if (k == ';') { menu--; if (menu < 0) menu = 3; drawMenu(); }
        if (k == '.') { menu++; if (menu > 3) menu = 0; drawMenu(); }
        if (k == '\n' || k == '\r') {
          if (menu == 0) wifiScan();
          else if (menu == 1) { drawMenu(); }
          else drawMenu();
        }
      }
    }
  }
  delay(10);
}
