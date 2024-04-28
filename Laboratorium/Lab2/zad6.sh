#!/usr/bin/env bash
#
# Systemy operacyjne 2 – laboratorium nr 2 – semestr letni 2020/2021
#
# Celem zajęć jest nabranie doświadczenia w podstawowej pracy z powłoką Bash,
# w szczególności w nawigowaniu po drzewie katalogów i sprawdzaniu uprawnień.
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
# Odnaleźć w katalogu `bbb` plik, którego zawartość pokrywa się z zawartością
# pliku `bardzo tajna treść` (jest on w katalogu `ddd`) i skopiować znaleziony
# plik do katalogu `ddd`, jeśli jeszcze go tam nie ma.
#

directory="bbb"
source_directory="ddd"
file_name="bardzo tajna treść"

# Dla każdego pliku w katalogu
for file in $(find "${directory}" -type f);
do
# Jeśli zawartość pliku jest taka sama jak zawartość pliku źródłowego
    if [ "$(cat "${file}")" == "$(cat "${source_directory}/${file_name}")" ];
    then
    # Jeśli plik nie istnieje w katalogu źródłowym
        if [ ! -e "${source_directory}/$(basename "${file}")" ];
        then
        # Skopiuj plik
            cp "${file}" "${source_directory}"
        fi
    fi
done

