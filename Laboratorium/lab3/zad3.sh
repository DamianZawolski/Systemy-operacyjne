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
# Zadanie 3.
# Utworzyć w katalogu `ddd` dowiązania do wszystkich plików wykonywalnych
# z katalogu `aaa`. Nazwy tworzonych dowiązań mają pokrywać się z nazwami
# oryginalnych plików. Rodzaj dowiązania nie ma znaczenia, ale należy
# upewnić się, że nie zmienimy żadnych istniejących plików w `ddd`.
#

# Ustawienie zmiennych
source_directory="aaa"
directory="ddd"

# Jeżeli katalog docelowy nie istnieje, to go utwórz
if [ ! -d "${directory}" ]; then
    mkdir -p "${directory}"
fi

# Dla każdego pliku w katalogu źródłowym (który jest wykonywalny) wykonaj dowiązanie do katalogu docelowego
for file in $(find "${source_directory}" -type f -executable); do
    # Utwórz dowiązanie do pliku w katalogu docelowym
    ln -s "${file}" "${directory}/$(basename "${file}")"
done