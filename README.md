# bridges app
## Wąski most

Z miasta A do miasta B prowadzi droga, na której znajduje się wąski most umożliwiający tylko ruch jednokierunkowy. Most jest również dość słaby, także może po nim przejeżdżać tylko jeden samochód na raz. Napisać program w którym N samochodów (wątków) będzie nieustannie przejeżdżało z miasta do miasta, pokonując po drodze most (N przekazywane jako argument linii poleceń).  "Miasto" jest to funkcja, którą wątki mogą wykonywać niezależnie od siebie przez krótki, losowy czas (maks. kilka sekund). Zsynchronizuj dostęp wątków do mostu:
- nie wykorzystując zmiennych warunkowych (tylko mutexy/semafory)
- wykorzystując zmienne warunkowe (condition variables)

Aby móc obserwować działanie programu, każdemu samochodowi został przydzielony numer. Program  wypisuje komunikaty według poniższego przykładu:
```
A-5 10>>> [>> 4 >>] <<<4 6-B
```
Oznacza to, że po stronie miasta A jest 15 samochodów z czego 10 czeka w kolejce przed mostem, przez most przejeżdża samochód z numerem 4 z miasta A do B, po stronie miasta B jest 10 samochodów, z czego 4 oczekują w kolejce przed mostem. Po uruchomieniu programu z parametrem -debug, cała zawartość kolejek po obu stronach mostu jest wypisywana (nie tylko ilość samochodów).  
Komunikat jest wypisywany w momencie, kiedy w programie zmieni się którakolwiek z tych wartości.

