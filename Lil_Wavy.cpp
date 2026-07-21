#include "Lil_Wavy.h"
#include <portaudio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512



static void checkErr(PaError err) {
	if (err != paNoError) {
		std::cout << "PortAudio Error: " << Pa_GetErrorText(err);
		exit(EXIT_FAILURE);	
	}
}

static int patestCallback(
	const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
	void* userData
) {

}



int main()
{
	//portAudio
	PaError err;
	err = Pa_Initialize();
	checkErr(err);


	int deviceNum = 0;


	PaStreamParameters inputParameters;

	inputParameters.channelCount = 2;
	inputParameters.device = deviceNum;
	inputParameters.hostApiSpecificStreamInfo = NULL;
	inputParameters.sampleFormat = paFloat32;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(deviceNum)->defaultLowInputLatency;

	PaStreamParameters outputParameters;

	outputParameters.channelCount = 2;
	outputParameters.device = deviceNum;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(deviceNum)->defaultLowInputLatency;

	PaStream* stream;
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paNoFlag,
		patestCallback,
		NULL
	);
	checkErr(err);

	err = Pa_StartStream(&stream);
	checkErr(err);



	//SFML
	sf::Window window(sf::VideoMode({800, 600}), "LilWavy", sf::Style::Default, sf::State::Windowed);


	// ================================================================
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
	}






	// ================================================================

	err = Pa_StopStream(&stream);
	checkErr(err);

	err = Pa_CloseStream(&stream);
	checkErr(err);

	err = Pa_Terminate();
	checkErr(err);

	return EXIT_SUCCESS;
}
