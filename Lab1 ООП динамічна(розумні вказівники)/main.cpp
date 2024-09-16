#include <iostream>
#include "Playlist.h"

int main()
{
	Playlist playlist;
	if (playlist.loadSong("file.txt")) {
		playlist.chooseSong();
	}
}
