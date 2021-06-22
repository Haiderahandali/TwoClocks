#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
extern char AUDIO_PATH[];

void PlayAlarm(void);

void PlayAlarm()
{
	NSString *audioPath = [[NSString alloc]initWithCString:AUDIO_PATH encoding:NSASCIIStringEncoding];
	NSSound *sound = [[NSSound alloc] initWithContentsOfFile:audioPath  byReference:NO];

	[sound play];
	[sound release];
}
