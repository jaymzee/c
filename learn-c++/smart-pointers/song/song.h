#include <string>

class Song {
public:
    Song(std::string artist, std::string title) :
        _artist(artist), _title(title)
    {}

    std::string to_string() {
        return _artist + ": " + _title;
    }

    std::string artist() {
        return _artist;
    }

    std::string title() {
        return _title;
    }

private:
    std::string _artist;
    std::string _title;
};
