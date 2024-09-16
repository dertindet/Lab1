#pragma once
#include "Song.h"
#include <string>
#include <vector>
#include <memory>  

class Playlist {
public:
    void addSong(std::unique_ptr<Song> song);  
    bool loadSong(const std::string& file_name);
    void chooseSong();

private:
    std::vector<std::unique_ptr<Song>> songs; 
};