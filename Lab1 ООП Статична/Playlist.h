#pragma once
#include "Song.h"
#include <string>
#include <vector>

class Playlist
{
public:
	void addSong(const Song&);
	bool loadSong(const std::string&);
	void chooseSong();
private:
	std::vector<Song> songs;
};