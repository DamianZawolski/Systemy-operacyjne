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
# Zadanie 2.
# Zweryfikować istnienie i zawartość pliku `drugi` z katalogu `ddd`.
# Plik powinien zawierać napis `Ala ma kota.`. Jeśli czegoś brakuje
# to odpowiedni plik stworzyć lub nadpisać istniejący.
#

directory="ddd"
file_name="drugi"
file_text="Ala ma kota."

# Jeśli plik nie istnieje (-e jest prawdą jeśli plik istnieje)
if [ ! -e "${directory}/${file_name}" ];
then
# Utworzenie pliku
    echo "${file_text}" > "${directory}/${file_name}"
else
# Jeśli plik istnieje, sprawdź czy zawiera odpowiedni tekst
    if [ "$(cat "${directory}/${file_name}")" != "${file_text}" ];
    then
    # Jeśli nie, nadpisz plik
        echo "${file_text}" > "${directory}/${file_name}"
    fi
fi