#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "song.h"
#include <conio.h>

void addSong(std::vector<Song>& playlist, const std::string& title, const int& duration) {
    playlist.push_back({ title, duration });
}

bool loadSong(std::vector<Song>& playlist, const std::string& file_name) {
    std::cout << "Trying to open file: " << file_name << std::endl;
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "ERROR: " << file_name << std::endl;
        return false;
    }

    std::string title;
    std::string duration;
    while (std::getline(file, title) && std::getline(file, duration)) {
        addSong(playlist, title, std::stoi(duration));
    }

    file.close();
    return true;
}
void chooseSong(std::vector<Song>& playlist) {
    std::set<size_t> choosen;
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
            addSong(playlist, title, duration);
            std::cout << "Song added!\n";
            break;
        }
        case '2': {
            std::cout << "\n=== Song List ===\n";
            if (playlist.empty()) {
                std::cout << "No songs in the list.\n";
            }
            else {
                for (size_t i = 0; i < playlist.size(); ++i) {
                    std::cout << std::setw(2) << i + 1 << ". " << playlist[i].title
                        << " (" << playlist[i].duration << " sec)\n";
                }
            }
            break;
        }
        case '3': {
            choosen.clear();
            int choice = 0;
            do {
                std::cout << "\n=== Choose Favorite Songs ===\n";
                std::cout << "Enter the number of the song to toggle selection (0 to finish):\n";
                for (size_t i = 0; i < playlist.size(); ++i) {
                    if (choosen.count(i)) {
                        std::cout << "* "; 
                    }
                    else {
                        std::cout << "  ";
                    }
                    std::cout << std::setw(2) << i + 1 << ". " << playlist[i].title
                        << " (" << playlist[i].duration << " sec)\n";
                }
                std::cin >> choice;
                if (choice > 0 && static_cast<size_t>(choice) <= playlist.size()) {
                    if (choosen.count(choice - 1)) {
                        choosen.erase(choice - 1);
                    }
                    else {
                        choosen.insert(choice - 1);
                    }
                }
                else if (choice != 0) {
                    std::cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 0);

            int totalDuration = 0;
            for (auto index : choosen) {
                totalDuration += playlist[index].duration;
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
