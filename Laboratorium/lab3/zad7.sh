#!/usr/bin/env bash
#
# Systemy operacyjne 2 – laboratorium nr 3 – semestr letni 2020/2021
#
# Celem zajęć jest pogłębienie wiedzy na temat struktury systemu plików,
# poruszania się po katalogach i kontroli uprawnień w skryptach powłoki.
#
# Przygotowane rozwiązania nie muszą być całkowicie uniwersalne. Zakładamy,
# że ogólna struktura katalogów się nie zmienia (nie będzie już więcej/mniej
# poziomów podkatalogów), jednakże same nazwy i zawartości plików (o ile
# nie są podane wprost w treści zadań) mogą być dowolne i ulegać zmianie,
# a przygotowane rozwiązania nadal powinny działać.
#
# Wszystkie chwyty dozwolone, ale ostatecznie w wyniku ma powstać tylko to,
# o czym mowa w treści zadania – tworzone samodzielnie ewentualne tymczasowe
# pliki pomocnicze należy usunąć.
#

#
# Zadanie 7.
# Odnaleźć w katalogu `bbb` wszystkie dowiązania miękkie, które wskazują
# na jakiś cel przy pomocy ścieżki bezwzględnej. Zapisać do pliku `linki`
# w katalogu `ddd` wszystkie te ścieżki, ale poprawione w taki sposób,
# aby były one ścieżkami kanonicznymi. Istnienie elementu wskazywanego
# przez dowiązanie nie ma dla nas znaczenia.
#

# Ustawienie zmiennych
directory="bbb"
output_file="ddd/linki"

# Dla każdego dowiązania symbolicznego w katalogu wykonaj sprawdzenie, czy wskazuje na istniejący plik
for link in $(find "${directory}" -type l); do
    # Sprawdź, czy wskazywany plik istnieje
    if [ -e "${link}" ]; then
        # Wyświetl ścieżkę wskazywanego pliku jako ścieżkę kanoniczną
        readlink -f "${link}" >> "${output_file}"
    fi
done