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
# Zadanie 9.
# W katalogu `zasoby` w `ddd` utworzyć plik `tajne hasła`, który zawierać
# będzie połączoną treść wszystkich plików z katalogu `ccc` (oraz jego
# podkatalogów) – ale tylko takich, które potrafimy przeczytać. Niech każda
# nowa zawartość będzie poprzedzona jakimś wyróżniającym się nagłówkiem
# z nazwą pliku z którego ona pochodzi. Upewnić się także, że w trakcie
# procesu nie zgłoszą nam się problemy z dostępem do plików (to znaczy,
# że na pewno możemy je przeczytać).
#

directory="ddd/zasoby"
file_name="tajne hasła"
source_directory="ccc"
header="---"

if [ -e "${directory}/${file_name}" ];
then
    rm "${directory}/${file_name}"
fi

touch "${directory}/${file_name}"

for file in $(find "${source_directory}" -type f);
do
    if [ -r "${file}" ];
    then
        echo "${header} $(basename "${file}")" >> "${directory}/${file_name}"
        cat "${file}" >> "${directory}/${file_name}"
    fi
done

