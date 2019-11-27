#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include "AudioFile.h"
#include <vector>
#include <chrono>

using namespace std;

vector<double> MyConvolve(vector<double> A, vector<double> B){

	vector<double> C;
		
	for (int i = 0; i < A.size() + B.size() - 1; i++) {
		C.push_back(0);

		int min, max;
		if (i >= B.size() - 1) min = i - B.size() + 1; else min = 0;
		if (i < A.size() - 1) max = i; else max = A.size() - 1;

		for (int j = min; j <= max; j++) 
			C[i] += A[j] * B[i - j];
		
	}

	return C;
}

void MyConvolveRun() {
	int n;
	vector<double> B = { 0.2, 0.2, 0.2, 0.2, 0.2 }, A; // This is the known vetor B given in the excercise.
	
	std::cout << "Choose a vector size greater than 10.\n"; // User input for vector A's size.
	std::cin >> n;
	while (n <= 10) {
		std::cout << "Please choose a vector size greater than 10.\n";
		std::cin >> n;
	}

	uniform_real_distribution<double> dis(0, 100);
	default_random_engine randeng;

	for (int i = 0; i < n; i++)
		A.push_back(dis(randeng));

	vector<double> C = MyConvolve(A, B); // Running the convoloution function.

	return;
}


void WavConvolve(string file1, string file2) {

	AudioFile<double> audio, filter, output;

	file1 += ".wav"; file2 += ".wav";
	audio.load(file1); filter.load(file2);

	output.samples[0] = MyConvolve(audio.samples[0], filter.samples[0]);
	output.save("pinkNoise_sampleAudio.wav");
}

void WhiteNoiseGen(string file) {

	AudioFile<double> audio, output;
	vector<double> noise;
	audio.load(file + ".wav");

	default_random_engine randeng;
	normal_distribution<double> dis(0., 1.);

	for (int i = 0; i < audio.samples[0].size(); i++)
		noise.push_back(dis(randeng));

	output.samples[0] = MyConvolve(audio.samples[0], noise);
	output.save("whiteNoise_sampleAudio.wav");
}

int main() {

	//MyConvolveRun();

	//WavConvolve("sample_audio", "pink_noise");

	WhiteNoiseGen("sample_audio");

	return 0;
}