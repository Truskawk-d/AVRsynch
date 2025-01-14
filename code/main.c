// Definicja pinów
const int przyciskStart = PD0; // SW0 - przycisk start
const int przycisk1 = PD1;     // SW1
const int przycisk2 = PD2;     // SW2
const int przycisk3 = PD3;     // SW3
const int przycisk4 = PD4;     // SW4
const int przyciskConfig = PD5; // SW5 - przycisk konfiguracji sekwencji

const int ledSukces = PB1;     // L1 - LED Sukces
const int ledFail = PB2;       // L2 - LED Fail

// Ustawienia sekwencji 
int sekwencja[4] = {przycisk1, przycisk2, przycisk3, przycisk4};
const int dlugoscSekwencji = 4;
const unsigned long czasNaSekwencje = 10000;  // Limit czasu - 10 sekund

void setup() {
  // Ustawienie pinów przycisków z pull-up
  DDRD &= ~((1 << przyciskStart) | (1 << przycisk1) | (1 << przycisk2) | (1 << przycisk3) | (1 << przycisk4) | (1 << przyciskConfig));
  PORTD |= (1 << przyciskStart) | (1 << przycisk1) | (1 << przycisk2) | (1 << przycisk3) | (1 << przycisk4) | (1 << przyciskConfig);

  // Ustawienie pinów LED 
  DDRB |= (1 << ledSukces) | (1 << ledFail);

  // Wyłączenie LED na start
  PORTB &= ~((1 << ledSukces) | (1 << ledFail));
}

void loop() {
  // Sprawdzenie, czy przycisk konfiguracji został wciśnięty
  if (!(PIND & (1 << przyciskConfig))) {
    _delay_ms(200); // Debounce
    
    // Wejście w tryb konfiguracji sekwencji
    konfigurujSekwencje();
  }

  // Sprawdzanie, czy przycisk start został wciśnięty
  if (!(PIND & (1 << przyciskStart))) { // Przycisk start wciśnięty
    _delay_ms(200);  
    unsigned long startCzas = millis();
    int userSequence[dlugoscSekwencji];
    bool sukces = true;

    // Pętla po sekwencji przycisków
    for (int i = 0; i < dlugoscSekwencji; i++) {
      userSequence[i] = -1;
      bool wcisniety = false;

      // Czekanie na wciśnięcie przycisku lub upływ czasu
      while (!wcisniety) {
        // Sprawdzenie, czy minął czas
        if (millis() - startCzas > czasNaSekwencje) {
          sukces = false;
          break;
        }

        // Sprawdzenie, który przycisk został wciśnięty i zapisanie go
        if (!(PIND & (1 << przycisk1))) {
          userSequence[i] = przycisk1;
          wcisniety = true;
          _delay_ms(200);  
        } else if (!(PIND & (1 << przycisk2))) {
          userSequence[i] = przycisk2;
          wcisniety = true;
          _delay_ms(200);  
        } else if (!(PIND & (1 << przycisk3))) {
          userSequence[i] = przycisk3;
          wcisniety = true;
          _delay_ms(200);  
        } else if (!(PIND & (1 << przycisk4))) {
          userSequence[i] = przycisk4;
          wcisniety = true;
          _delay_ms(200);  
        }
      }

      if (!sukces) break;  // Przerwij, jeśli czas minął
    }

    // Porównanie wprowadzonej sekwencji z poprawną sekwencją
    for (int i = 0; i < dlugoscSekwencji; i++) {
      if (userSequence[i] != sekwencja[i]) {
        sukces = false;
        break;
      }
    }

    // Wynik: jeśli sekwencja jest poprawna zapal Sukces, jeśli błędna, zapal Fail
    if (sukces) {
      PORTB |= (1 << ledSukces);  // Zapal LED sukcesu
      _delay_ms(1000);
      PORTB &= ~(1 << ledSukces); // Wyłącz LED sukcesu
    } else {
      PORTB |= (1 << ledFail);  // Zapal LED Fail
      _delay_ms(1000);
      PORTB &= ~(1 << ledFail); // Wyłącz LED Fail
    }
  }
}

void konfigurujSekwencje() {
  // Sygnalizacja wejścia w tryb konfiguracji - mignij LED sukces
  PORTB |= (1 << ledSukces);
  _delay_ms(500);
  PORTB &= ~(1 << ledSukces);
  _delay_ms(500);

  // Oczekiwanie na wprowadzenie nowej sekwencji
  // Użytkownik musi nacisnąć 4 przyciski w żądanej kolejności
  for (int i = 0; i < dlugoscSekwencji; i++) {
    bool wcisniety = false;
    while (!wcisniety) {
      if (!(PIND & (1 << przycisk1))) {
        sekwencja[i] = przycisk1;
        wcisniety = true;
        _delay_ms(200);
      } else if (!(PIND & (1 << przycisk2))) {
        sekwencja[i] = przycisk2;
        wcisniety = true;
        _delay_ms(200);
      } else if (!(PIND & (1 << przycisk3))) {
        sekwencja[i] = przycisk3;
        wcisniety = true;
        _delay_ms(200);
      } else if (!(PIND & (1 << przycisk4))) {
        sekwencja[i] = przycisk4;
        wcisniety = true;
        _delay_ms(200);
      }
    }
  }

  // Potwierdzenie zapisania nowej sekwencji - mignij LED sukces 2 razy
  for (int i = 0; i < 2; i++) {
    PORTB |= (1 << ledSukces);
    _delay_ms(200);
    PORTB &= ~(1 << ledSukces);
    _delay_ms(200);
  }
}