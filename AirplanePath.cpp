#include "AirplanePath.h"

// Implementace hledání cesty
// "Letadlo" - nejkratší cesta mezi dvěma body nehledě na nadmořskou výšku
// Výsledek nemusí být "přímka" vzhledem k limitaci směrů pohybu v mapě - podobné vzdálenosti v Manhattanské metrice - více možností pro nejkratší vzdálenost
// našel jsem, že by se mohlo jednat o Chebyshev distance
bool AirplanePath::find() {
    
    path.push_back(start);
    Point current = start;

    while (current != finish) {
        if (current.x < finish.x) current.x++;
        else if (current.x > finish.x) current.x--;

        if (current.y < finish.y) current.y++;
        else if (current.y > finish.y) current.y--;

        path.push_back(current);
    }

    return true; // Úspěšně nalezeno
}