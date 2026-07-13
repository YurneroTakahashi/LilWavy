#include "Lil_Wavy.h"
#include <portaudio.h>


static void checkErr(PaError err) {
	if (err != paNoError) {
		std::cout << "PortAudio Error: " << Pa_GetErrorText(err);
		exit(EXIT_FAILURE);
	}
}


int main()
{
	PaError err;
	err = Pa_Initialize();
	checkErr(err);




	err = Pa_Terminate();
	checkErr(err);

	return EXIT_SUCCESS;
}
