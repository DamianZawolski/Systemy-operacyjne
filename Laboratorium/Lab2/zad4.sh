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
# Zadanie 4.
# Utworzyć w katalogu `ddd` plik o nazwie `całość`, który będzie zawierał
# połączoną zawartość wszystkich plików zwykłych z katalogu `aaa`.
# Jeżeli plik `całość` istnieje, to należy nadpisać jego zawartość.
# Kolejność łączenia plików nie ma znaczenia.
#

directory="ddd"
file_name="całość"
source_directory="aaa"

# Jeśli plik istnieje (-e jest prawdą jeśli plik istnieje)
if [ -e "${directory}/${file_name}" ];
then
# Usunięcie pliku
    rm "${directory}/${file_name}"
fi

# Utworzenie pliku
touch "${directory}/${file_name}"

# Dla każdego pliku w katalogu źródłowym
for file in "${source_directory}"/*;
do
# Jeśli plik jest zwykły (-f jest prawdą jeśli plik istnieje i jest zwykły)
    if [ -f "${file}" ];
    then
    # Dołącz zawartość pliku do pliku docelowego
        cat "${file}" >> "${directory}/${file_name}"
    fi
done
