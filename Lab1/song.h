#pragma once
#include <string>
#include <vector>

struct Song {
public:
	std::string title;
	int duration;
};

void addSong(std::vector<Song>&, const std::string&, const int&);

bool loadSong(std::vector<Song>&, const std::string&);

void chooseSong(std::vector<Song>&);