/*
 * The following example shows how to create unique_ptr instances and pass
 * them between functions.
 */

#include <iostream>
#include <memory>
#include <vector>

#include "song.h"

std::unique_ptr<Song> SongFactory(std::string artist, std::string title)
{
    // Implicit move operation into the variable that stores the result.
    return std::make_unique<Song>(artist, title);
}

void MakeSongs()
{
    // Create a new unique_ptr with a new object.
    auto song = std::make_unique<Song>("Mr. Children", "Namonaki Uta");
    std::cout << song->to_string() << std::endl;

    // Use the unique_ptr.
    std::vector<std::string> titles = { song->title() };
    std::cout << "{\n";
    for (auto& title : titles) {
        std::cout << "    \"" << title << "\",\n";
    }
    std::cout << "}\n";

    // Move raw pointer from one unique_ptr to another.
    std::unique_ptr<Song> song2 = std::move(song);
    std::cout << song2->to_string() << std::endl;

    // Obtain unique_ptr from function that returns by value.
    auto song3 = SongFactory("Michael Jackson", "Beat It");
    std::cout << song3->to_string() << std::endl;
}

int main()
{
    MakeSongs();
}
