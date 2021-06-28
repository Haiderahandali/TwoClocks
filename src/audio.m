#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include "audio.h"

NSSound* sound = nil;
NSString* audioPath = nil;


void InitAudio(char* gAudioPath)
{
	audioPath = [[NSString alloc]initWithCString:gAudioPath encoding:NSASCIIStringEncoding];
    sound     = [[NSSound alloc] initWithContentsOfFile:audioPath byReference:NO];
}

void PlayAlarm()
{
	if([sound isPlaying] == NO)
    {
		[sound play];
	} 
	else 
    {
		[sound stop];
		[sound play];
    }

}


