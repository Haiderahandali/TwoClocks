#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>


void PlayAlarm(char* gAudioPath);

void PlayAlarm(char* gAudioPath)
{

    	NSString *audioPath = [[NSString alloc]initWithCString:gAudioPath encoding:NSASCIIStringEncoding];

		NSSound *sound = [[NSSound alloc] initWithContentsOfFile:audioPath  byReference:NO];
		[sound play];

		[audioPath release];
		[sound release];


}
