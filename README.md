# Praktikum – Labor C Messtechnik

## 🛠 Praktikumsthema
Dieses Repository enthält den Praktikumsbericht für das **Labor C Embedded Systems** im Fachgebiet Messtechnik an der Universität Kassel.

Das Ziel des Praktikums war es, grundlegende Kenntnisse in der hardwarenahen Programmierung mit **C** zu erlangen und messtechnische Anwendungen zu realisieren. Dabei wurde mit dem **STM32 NUCLEO F446RE** gearbeitet.

## 📋 Inhalt des Berichts
Im Rahmen des Praktikums wurden mehrere Aufgabenblöcke bearbeitet. Dieses Repository enthält den Bericht zu **Block 1 – Ein- und Ausgaben**, welcher folgende Teilaufgaben umfasst:

1. **Blinkende LED** – Eine LED blinkt mit einer definierten Frequenz, gesteuert über einen Timer-Interrupt.
2. **UART-Kommunikation** – Die Blinkfrequenz der LED kann über eine UART-Schnittstelle eingestellt und ausgelesen werden.
3. **Display-Anzeige** – Die aktuelle Frequenz wird auf einem **SSD1306 OLED-Display** dargestellt.

## 📂 Dateien im Repository
- `main.c` – Hauptprogramm mit der Implementierung der Aufgaben
- `stm32f4xx_it.c` – Interrupt-Routinen für Timer und UART
- `ssd1306.c` & `ssd1306.h` – Display-Treiberbibliothek
- `LaborC_Bericht.pdf` – Praktikumsbericht im PDF-Format

## 🖥 Voraussetzungen
Um das Projekt auszuführen, werden folgende Komponenten benötigt:
- **STM32 NUCLEO F446RE** - Mikrocontroller
- **STM32CubeIDE** zur Programmierung des Mikrocontrollers
- **HTerm** oder ein anderes Terminalprogramm zur UART-Kommunikation
- **SSD1306 OLED-Display** mit I2C-Anschluss

---

📌 **Hinweis**: Dieses Projekt wurde zu **Lernzwecken** erstellt.
