# Opis płytki PCB

Płytka zaprojektowana do gry z sekwencją przycisków wykorzystuje mikrokontroler AVR (np. ATmega8) i zestaw elementów wspomagających. Oto szczegóły konstrukcji:

## 1. Mikrokontroler
- Centralnym elementem płytki jest mikrokontroler (ATmega8 lub kompatybilny) umieszczony w podstawce DIP28.
- Mikrokontroler jest podłączony do:
  - **Pinów wejściowych**: przyciski podłączone do portu **PD**.
  - **Pinów wyjściowych**: diody LED podłączone do portu **PB**.
  - Kwarcu oscylacyjnego i kondensatorów do generowania zegara.

## 2. Zasilanie
- Płytka jest zasilana poprzez stabilizator napięcia 7805, który zapewnia stabilne 5V dla mikrokontrolera i reszty układu.
- Elementy w układzie zasilania:
  - Kondensatory filtrujące (elektrolityczne i ceramiczne).
  - Diody prostownicze zabezpieczające przed odwrotną polaryzacją.
  - Dławik, który dodatkowo wygładza napięcie zasilania.

## 3. Przyciski
- Na płytce znajduje się 6 przycisków:
  - Jeden do rozpoczęcia gry (PD0).
  - Cztery do odtwarzania sekwencji (PD1–PD4).
  - Jeden do konfiguracji sekwencji (PD5).
- Przyciski są podłączone do portu D mikrokontrolera, a ich stany są odczytywane w kodzie.

## 4. Diody LED
- Na płytce znajdują się dwie diody LED:
  - **LED Sukces**: Podłączona do PB1. Sygnalizuje poprawne odtworzenie sekwencji.
  - **LED Fail**: Podłączona do PB2. Sygnalizuje błędne odtworzenie sekwencji lub upływ czasu.
- Każda dioda ma rezystor ograniczający prąd.

## 5. Oscylator kwarcowy
- Mikrokontroler korzysta z zewnętrznego oscylatora kwarcowego (16 MHz) oraz dwóch kondensatorów ceramicznych (22 pF) do stabilizacji sygnału zegarowego.

## 6. Złącza
- Płytka zawiera następujące złącza:
  - Złącze ISP (In-System Programming) do programowania mikrokontrolera.
  - Złącza zasilania (VCC i GND) dla stabilizatora.
  - Złącza pinów mikrokontrolera wyprowadzone na zewnątrz w celach testowych lub dalszej rozbudowy.

## 7. Elementy zabezpieczające
- Diody i kondensatory filtrujące w układzie zasilania zapewniają ochronę przed zakłóceniami i odwrotnym podłączeniem zasilania.

## 8. Rozmieszczenie na PCB
- Wszystkie elementy zostały rozmieszczone kompaktowo, z minimalizacją długości ścieżek krytycznych (np. dla zasilania).
- Mikrokontroler znajduje się w centralnej części płytki, otoczony przez złącza ISP i elementy wspomagające.
- Przyciski i diody LED są umieszczone w logicznych sekcjach dla łatwego dostępu.

## 9. Sposób montażu
- Wszystkie elementy zostały zaprojektowane jako przewlekane (THT), co ułatwia lutowanie.
- Płytka zawiera opisy elementów (silkscreen), co znacznie ułatwia montaż i identyfikację komponentów.

