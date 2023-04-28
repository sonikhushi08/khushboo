#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include "sddl.h/SDL.h"

using namespace std;

// Define constants for audio playback
const int FREQUENCY = 44100;
const Uint16 FORMAT = AUDIO_S16;
const int CHANNELS = 2;
const int CHUNKSIZE = 4096;

// Struct to represent a song
struct Song {
    string title;
    string artist;
    string album;
    string path;
};

// Function to get a list of music files in a directory
vector<string> getMusicFiles(const string& directory) {
    DIR* dir = opendir(directory.c_str());
    dirent* entry;
    vector<string> files;

    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        // Check if the file is a music file
        if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".mp3") {
            files.push_back(directory + "/" + filename);
        }
    }
    closedir(dir);
    return files;
}

// Function to load a song from a file path
Song loadSong(const string& path) {
    Song song;
    // Load metadata using TagLib library
    // ...
    song.path = path;
    return song;
}

// Function to play a song using SDL audio library
void playSong(const Song& song) {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec desiredSpec, obtainedSpec;
    SDL_AudioDeviceID audioDevice;

    // Set up audio device specifications
    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = FORMAT;
    desiredSpec.channels = CHANNELS;
    desiredSpec.samples = CHUNKSIZE;
    desiredSpec.callback = NULL;

    // Open audio device
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, &obtainedSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (audioDevice == 0) {
        cerr << "Error: Failed to open audio device - " << SDL_GetError() << endl;
        return;
    }

    // Load music file using SDL_mixer library
    // ...
    // Play music
    SDL_PauseAudioDevice(audioDevice, 0);

    // Wait until song finishes playing
    while (SDL_GetAudioDeviceStatus(audioDevice) == SDL_AUDIO_PLAYING) {
        SDL_Delay(100);
    }

    // Close audio device
    SDL_CloseAudioDevice(audioDevice);
}

int main() {
    // Get list of music files in directory
    vector<string> musicFiles = getMusicFiles("Music");

    // Load songs from music files
    vector<Song> songs;
    for (const auto& file : musicFiles) {
        Song song = loadSong(file);
        songs.push_back(song);
    }

    // Play first song in list
    playSong(songs[0]);

    return 0;
}