//
//  AppleHelper.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 24/2/15.
//
//

#include "AppleHelper.h"


void AppleHelper::ignorePathFromiCloud(std::string path , bool isDir, bool ignore)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    NSError *error = nil;
    NSString *iosPath = [NSString stringWithCString:path.c_str()
                                           encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL fileURLWithPath:iosPath isDirectory:isDir];
    if ([[NSFileManager defaultManager] fileExistsAtPath:[url path]]) {
        BOOL success = [url setResourceValue: [NSNumber numberWithBool: ignore]
                                      forKey: NSURLIsExcludedFromBackupKey error: &error];
        if(!success){
            NSLog(@"Error excluding %@ from backup %@", [url lastPathComponent], error);
        } else {
            NSLog(@"Success excluded from iCloud backup.");
        }
    }
#endif
}