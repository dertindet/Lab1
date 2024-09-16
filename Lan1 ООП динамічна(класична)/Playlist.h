#pragma once
#include "Song.h"
#include <string>
#include <vector>

class Playlist
{
public:
	void addSong(Song*);
	bool loadSong(const std::string&);
	void chooseSong();
	~Playlist();
private:
	std::vector<Song*> songs;
};