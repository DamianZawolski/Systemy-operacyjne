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
# Zadanie 8.
# Utworzyć kopię zapasową wszystkich ważnych plików z katalogów `aaa` i `bbb`
# wewnątrz katalogu `zapasy` w `ddd`. Ważne pliki to takie, które zostały
# zabezpieczone przed modyfikacją (czyli nie mamy prawa zapisu do nich).
# Zachować strukturę plików – czyli w katalogu `zapasy` mają powstać katalogi
# `aaa`, `bbb` i wszelkie potrzebne ich podkatalogi.
#

source_directory1="aaa"
source_directory2="bbb"
directory="ddd/zapasy"

#Jeżeli katalog docelowy nie istnieje, to go utwórz
if [ ! -d "${directory}" ]; then
    mkdir -p "${directory}"
fi

# Dla każdego pliku w katalogu źródłowym (który jest niezapisywalny) wykonaj kopię do katalogu docelowego (z zachowaniem struktury katalogów)
for file in $(find "${source_directory1}" "${source_directory2}" -type f); do
# Jeżeli plik jest niezapisywalny (-w jest prawdą jeśli plik istnieje i jest zapisywalny)
    if [ ! -w "${file}" ]; then
    cp --parents "${file}" "${directory}"
    fi
done