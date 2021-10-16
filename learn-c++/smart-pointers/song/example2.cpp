/*
 * the following example shows how to create unique_ptr instances and use
 * them in a vector.shows how to create unique_ptr instances and use them
 * in a vector.
 */

#include <iostream>
#include <memory>
#include <vector>

#include "song.h"

void SongVector()
{
    using std::vector;
    using std::unique_ptr;
    using std::make_unique;

    vector<unique_ptr<Song>> songs;

    // Create a few new unique_ptr<Song> instances
    // and add them to vector using implicit move semantics.
    songs.push_back(make_unique<Song>("B'z", "Juice"));
    songs.push_back(make_unique<Song>("Namie Amuro", "Funky Town"));
    songs.push_back(make_unique<Song>("Kome Kome Club", "Kimi ga Iru Dake de"));
    songs.push_back(make_unique<Song>("Ayumi Hamasaki", "Poker Face"));

    // Pass by const reference when possible to avoid copying.
    for (const auto& song : songs)
    {
        std::cout << "Artist: " << song->artist() << "   Title: " << song->title() << std::endl;
    }
}

int main()
{
    SongVector();
}
