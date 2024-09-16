#include "Playlist.h"
#include <iostream>
#include <fstream>
#include <set>
#include <conio.h>
#include <iomanip>
#include <memory>  

void Playlist::addSong(std::unique_ptr<Song> song) {
    songs.push_back(std::move(song));
}

bool Playlist::loadSong(const std::string& file_name) {
    std::cout << "Trying to open file: " << file_name << std::endl;
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Error: " << file_name << std::endl;
        return false;
    }

    std::string title;
    std::string duration;
    while (std::getline(file, title) && std::getline(file, duration)) {
        addSong(std::make_unique<Song>(title, std::stoi(duration)));
    }

    file.close();
    return true;
}

void Playlist::chooseSong() {
    std::set<size_t> chosen;
    char key;
    do {
        std::cout << "\n=== Menu ===\n";
        std::cout << "1. Add a new song\n";
        std::cout << "2. View all songs\n";
        std::cout << "3. Choose favorite songs\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        key = _getch();
        switch (key) {
        case '1': {
            std::string title;
            int duration;
            std::cout << "\nEnter song title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter song duration (seconds): ";
            std::cin >> duration;
            addSong(std::make_unique<Song>(title, duration));
            std::cout << "Song added!\n";
            break;
        }
        case '2': {
            std::cout << "\n=== Song List ===\n";
            if (songs.empty()) {
                std::cout << "No songs in the list.\n";
            }
            else {
                for (size_t i = 0; i < songs.size(); ++i) {
                    std::cout << std::setw(2) << i + 1 << ". " << songs[i]->title
                        << " (" << songs[i]->duration << " sec)\n";
                }
            }
            break;
        }
        case '3': {
            chosen.clear();
            int choice = 0;
            do {
                std::cout << "\n=== Choose Favorite Songs ===\n";
                std::cout << "Enter the number of the song to toggle selection (0 to finish):\n";
                for (size_t i = 0; i < songs.size(); ++i) {
                    if (chosen.count(i)) {
                        std::cout << "* ";
                    }
                    else {
                        std::cout << "  ";
                    }
                    std::cout << std::setw(2) << i + 1 << ". " << songs[i]->title
                        << " (" << songs[i]->duration << " sec)\n";
                }
                std::cin >> choice;
                if (choice > 0 && static_cast<size_t>(choice) <= songs.size()) {
                    if (chosen.count(choice - 1)) {
                        chosen.erase(choice - 1);
                    }
                    else {
                        chosen.insert(choice - 1);
                    }
                }
                else if (choice != 0) {
                    std::cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 0);

            int totalDuration = 0;
            for (auto index : chosen) {
                totalDuration += songs[index]->duration;
            }
            std::cout << "\nTotal listening time for favorite songs: " << totalDuration << " seconds.\n";
            break;
        }
        case '4':
            std::cout << "\nExiting...\n";
            break;
        default:
            std::cout << "\nInvalid option! Please try again.\n";
            break;
        }
    } while (key != '4');
}