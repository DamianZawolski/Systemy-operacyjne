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
# Zadanie 6.
# Odnaleźć wszystkie dowiązania miękkie, zdefiniowane w katalogu `ccc`, które
# poprawnie wskazują na jakieś miejsce w systemie plików (ich cel istnieje).
# Wyświetlić ścieżki do wskazywanych miejsc, konstruując je jako ścieżki
# względem katalogu domowego bieżącego użytkownika (zmienna ${HOME}).
#

# Ustawienie zmiennych
directory="ccc"

# Dla każdego dowiązania symbolicznego w katalogu wykonaj sprawdzenie, czy wskazuje na istniejący plik
for link in $(find "${directory}" -type l); do
    # Sprawdź, czy wskazywany plik istnieje
    if [ -e "${link}" ]; then
        # Wyświetl ścieżkę wskazywanego pliku jako ścieżkę względną do katalogu domowego bieżącego użytkownika
        readlink -f "${link}" --relative-to="${HOME}"
    fi
done