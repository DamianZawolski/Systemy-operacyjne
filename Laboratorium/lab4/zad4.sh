#!/usr/bin/env bash
#
# Systemy operacyjne 2 – laboratorium nr 4 – semestr letni 2020/2021
#
# Celem zajęć jest nabranie doświadczenia w pracy z programem `find`,
# wykorzystując przy tym wiedzę na temat struktury systemu plików itd.
# Większość rozwiązań powinno sprowadzić się do jednego, zmyślnego
# wywołania programu `find` z odpowiednimi argumentami.
#
# Nie przywiązujemy wagi do środowiska roboczego – zakładamy, że jego pliki,
# inne niż te podane wprost w treści zadań, mogą ulec zmianie, a przygotowane
# rozwiązania nadal powinny działać poprawnie.
#
# Punkt startowy powinien stanowić katalog ze źródłami: linux-5.11.13/
#

#
# Zadanie 4.
# Odszukać wykonywalne pliki zwykłe i policzyć ile ich jest. Następnie policzyć
# ile jest wykonywalnych skryptów powłoki pośród nich (plików z rozszerzeniem
# .sh na końcu nazwy). Jako wynik zwrócić ułamek w postaci X/Y i nic więcej.
#

dir="linux-5.11.13"


all=$(find "$dir" -type f -executable | wc -l)

sh=$(find "$dir" -type f -executable -name "*.sh" | wc -l)

echo "$sh/$all"