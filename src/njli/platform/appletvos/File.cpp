#include "File.h"
#import <UIKit/UIKit.h>
#include <string>
#include "Log.h"
#include <vector>

FILE* njli_fopen(const char* fname, const char* mode)
{
//    if(mode[0] == 'w') return NULL;
    return fopen(fname, mode);
}

const char *RESOURCE_PATH()
{
    NSString * resourcePath = [[NSBundle mainBundle] resourcePath];
    return [resourcePath cStringUsingEncoding:NSASCIIStringEncoding];
}

const char *ASSET_PATH(const char *file)
{
    NSMutableString* adjusted_relative_path = [[NSMutableString alloc] initWithString:@"assets/"];
    [adjusted_relative_path appendString: [[NSString alloc] initWithCString:file
                                                                   encoding:NSASCIIStringEncoding]];
    
    return [[[NSBundle mainBundle] pathForResource:adjusted_relative_path
                                                        ofType:nil]
                        cStringUsingEncoding:NSASCIIStringEncoding];
}

const char *BUNDLE_PATH()
{
    NSMutableString *path = [[NSMutableString alloc] initWithString:[[NSBundle mainBundle] resourcePath]];
    [path appendString: [[NSString alloc] initWithCString:"/assets/"
                                                                   encoding:NSASCIIStringEncoding]];
    
    return [path UTF8String];
}

const char *DOCUMENT_PATH(const char *file)
{
    NSString *documentDirectory = [NSString stringWithCString:DOCUMENT_BASEPATH() encoding:NSASCIIStringEncoding];
    NSString *filename = [[NSString alloc] initWithCString:file encoding:NSASCIIStringEncoding];
    NSString *fullFilename = [documentDirectory stringByAppendingPathComponent:filename];

    return [fullFilename UTF8String];
}

const char *DOCUMENT_BASEPATH()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    return [documentsDirectory UTF8String];
}

void sleepThread(float milliseconds)
{
    [NSThread sleepForTimeInterval:milliseconds];
}

//static int createFolder(NSString *folderName)
//{
//    NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH([folderName UTF8String]) encoding:NSASCIIStringEncoding];
//    
//    if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
//    {
//         NSError *error;
//        [[NSFileManager defaultManager] createDirectoryAtPath:filePath withIntermediateDirectories:NO attributes:nil error:&error]; //Create folder
//        if (error) {
//            DEBUG_LOG_E("File.mm", "%s", [[error localizedDescription] UTF8String]);
//            return 0;
//        }
//        return 1;
//    }
//    DEBUG_LOG_W("File.mm", "Unable to create directory: %s ", [filePath UTF8String]);
//    return 0;
//}

static void createDirectoryStructure(const char *filename)
{
    static char temp[2048];
    
//    DEBUG_LOG_ASSERT_WRITE(strlen(filename) < 2048, "TAG", "error");
    
    NSMutableArray *array = [[NSMutableArray alloc] init];
    
    strcpy(temp, filename);
    char *token = strtok(temp, "/");
    std::string path("");
    while (token != NULL)
    {
        path += token;
        path += "/";
        
        NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(path.c_str()) encoding:NSASCIIStringEncoding];
        
        [array addObject:filePath];
        
        token = strtok(NULL, "/");
    }
    [array removeLastObject];
    
    for (NSString *filePath in array)
    {
        if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
        {
            NSError *error;
            [[NSFileManager defaultManager] createDirectoryAtPath:filePath withIntermediateDirectories:NO attributes:nil error:&error]; //Create folder
            if (error) {
                DEBUG_LOG_E("File.mm", "%s", [[error localizedDescription] UTF8String]);
            }
        }
        
    }
    
//    NSMutableArray *array = [[NSMutableArray alloc] init];
//    
//    char *temp = new char[strlen(filename)];
//    strcpy(temp, filename);
//    char *token = strtok(temp, "/");
//    /* walk through other tokens */
//    NSString *currentString;
//    while( token != NULL )
//    {
//        currentString = [[NSString alloc] initWithCString:token encoding:NSASCIIStringEncoding];
//        [array addObject:currentString];
//        
//        token = strtok(NULL, "/");
//    }
//    
//    [array removeObject:currentString];
//    
//    NSMutableString *ss = [[NSMutableString alloc] init];
//    [ss appendString: @"/"];
//    for (NSString *s in array)
//    {
//        [ss appendString: s];
//        [ss appendString: @"/"];
//        
////        createFolder(ss);
//        
//    }
//    
//    delete [] temp;
}

//static void createFolder(NSString *folderName)
//{
//    NSError *error;
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
//    NSString *dataPath = [documentsDirectory stringByAppendingPathComponent:folderName];
//    
//    if (![[NSFileManager defaultManager] fileExistsAtPath:dataPath])
//        [[NSFileManager defaultManager] createDirectoryAtPath:dataPath withIntermediateDirectories:NO attributes:nil error:&error]; //Create folder
//}

//static NSString *getDocumentPath(const std::string &filename)
//{
//    return [[NSString alloc] initWithCString:DOCUMENT_PATH(filename.c_str()) encoding:NSASCIIStringEncoding];
//}




#pragma mark REFERENCE http://mobile.antonio081014.com/2013/06/create-rename-delete-read-and-write.html

int CRUD_create(const char *filename, const void *buffer, unsigned long len)
{
    createDirectoryStructure(filename);
    
    NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename) encoding:NSASCIIStringEncoding];
    NSData *data = [NSData dataWithBytes:buffer length:len];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        if ([[NSFileManager defaultManager] createFileAtPath:filePath contents:data attributes:nil])
        {
            DEBUG_LOG_V("TAG", "Created File %s\n", [filePath UTF8String]);
            return 1;
        }
        
        DEBUG_LOG_E("File.mm", "Couldn't create file: %s - %d,%s\n", filename, errno, strerror(errno));
        return 0;
        
    }
    
    DEBUG_LOG_W("File.mm", "file exists %s\n", [filePath UTF8String]);
    return 0;
}
int CRUD_read(const char *filename, void **buffer, unsigned long *len)
{
    NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename) encoding:NSASCIIStringEncoding];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSData *data = [NSData dataWithContentsOfFile:filePath];
        
        *len = [data length];
        *buffer = new char[*len];
        
        memcpy(*buffer, [data bytes], *len);
        
        return 1;
    }
    
    DEBUG_LOG_W("File.mm", "file does not exists %s", [filePath UTF8String]);
    
    return 0;
}
int CRUD_update(const char *filename, const void *buffer, unsigned long len)
{
    NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename) encoding:NSASCIIStringEncoding];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSError *error = nil;
        NSData *content = [[NSData alloc] initWithBytes:buffer length:len];
        
        [content writeToFile:filePath atomically:YES];
        // If error happens, log it.
        if (error) {
            DEBUG_LOG_E("File.mm", "%s", [[error localizedDescription] UTF8String]);
            return 0;
        }
        return 1;
    }
    // If the file doesn't exists, log it.
    DEBUG_LOG_E("File.mm", "File %s doesn't exists", [filePath UTF8String]);
    return 0;
}
int CRUD_delete(const char *filename)
{
    NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename) encoding:NSASCIIStringEncoding];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
        NSError *error = nil;
        // This function also returnsYES if the item was removed successfully or if path was nil.
        // Returns NO if an error occurred.
        [[NSFileManager defaultManager] removeItemAtPath:filePath error:&error];
        if (error) {
            DEBUG_LOG_E("File.mm", "%s", [[error localizedDescription] UTF8String]);
            return 0;
        }
        return 1;
    }
    DEBUG_LOG_E("File.mm", "File %s doesn't exists", [filePath UTF8String]);
    return 0;
}

#pragma mark REFERENCE http://nshipster.com/nsfilemanager/

void setupFileSystem()
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSURL *bundleURL = [[NSBundle mainBundle] bundleURL];
    NSDirectoryEnumerator *enumerator = [fileManager enumeratorAtURL:bundleURL
                                          includingPropertiesForKeys:@[NSURLNameKey, NSURLIsDirectoryKey]
                                                             options:NSDirectoryEnumerationSkipsHiddenFiles
                                                        errorHandler:^BOOL(NSURL *url, NSError *error)
                                         {
                                             if (error) {
                                                 NSLog(@"[Error] %@ (%@)", error, url);
                                                 return NO;
                                             }
                                             
                                             return YES;
                                         }];
    
    NSMutableArray *mutableFileURLs = [NSMutableArray array];
    for (NSURL *fileURL in enumerator) {
        NSString *filename;
        [fileURL getResourceValue:&filename forKey:NSURLNameKey error:nil];
        
        NSNumber *isDirectory;
        [fileURL getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:nil];
        
        // Skip directories with '_' prefix, for example
        if ([filename hasPrefix:@"_"] && [isDirectory boolValue]) {
            [enumerator skipDescendants];
            continue;
        }
        
        if (![isDirectory boolValue]) {
            [mutableFileURLs addObject:fileURL];
        }
    }
    for (NSURL *fileURL in mutableFileURLs) {
        std::string s([fileURL fileSystemRepresentation]);
        NSString *filePath = [[NSString alloc] initWithCString:s.c_str() encoding:NSASCIIStringEncoding];
        
//        if([[filePath pathExtension] isEqualToString:@"lua"]) {
            NSData *data = [NSData dataWithContentsOfFile:filePath];
        
        NSDictionary *info = [[NSBundle mainBundle] infoDictionary];
        NSString *_bundleName = [NSString stringWithFormat:@"%@", [info objectForKey:@"CFBundleName"]];
        
        std::string bundleName([_bundleName UTF8String]);
        
        std::string _AssetPath(bundleName + std::string(".app/assets/"));
        
            size_t found=s.find(_AssetPath);
            size_t len = s.length();
            std::string str2 = s.substr (found + strlen(_AssetPath.c_str()),len);
        
        
        CRUD_create(str2.c_str(), [data bytes], [data length]);
            
//        }
        
    }
    
    
//    NSFileManager *fileMgr = [[NSFileManager alloc] init];
//    NSError *error = nil;
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [paths objectAtIndex:0];
//    NSArray *files = [fileMgr contentsOfDirectoryAtPath:documentsDirectory error:nil];
//    
//    NSLog(@"%@", files);
}


