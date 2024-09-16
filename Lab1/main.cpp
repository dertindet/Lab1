#include <iostream>
#include "song.h"

int main() {
    std::vector<Song> playlist;
        
    if (loadSong(playlist, "file.txt")) {
        chooseSong(playlist);
    }

}