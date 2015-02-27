//
//  ZipManager.cpp
//  IkasGame
//
//  Created by Sergio Garcia on 24/2/15.
//
//

#include "ZipManager.h"
#include <iostream>
#include <fstream>
#include "external/unzip/unzip.h"
#include "../Singletons/GameSettingsManager.h"
#include "../Helpers/AppleHelper.h"

using namespace std;

#define MAX_FILENAME 512
#define READ_SIZE 8192

// Singleton
ZipManager * ZipManager::_instance = NULL;

ZipManager* ZipManager::getInstance()
{
    if(!_instance) _instance = new ZipManager();
    return _instance;
}

ZipManager::ZipManager()
{
    
}

ZipManager::~ZipManager()
{
    
}

std::string ZipManager::getZipFilePath()
{
    string WritablePath = FileUtils::getInstance()->getWritablePath();
    string ZipFileName = GameSettingsManager::getInstance()->getZipName();
    string ZipFilePath = WritablePath + ZipFileName;
    return ZipFilePath;
}

std::string ZipManager::getDataFolderPath()
{
    string WritablePath = FileUtils::getInstance()->getWritablePath();
    string DataFolderPath = WritablePath + "data/";
    return DataFolderPath;
}

std::string ZipManager::getDataFolderFullPath(std::string filePath)
{
    std::string basePath = this->getDataFolderPath();
    std::string fullPath = basePath + filePath;
    return fullPath;
}

bool ZipManager::saveZipDataToDisk(std::vector<char>* buffer)
{
    log("buffet size :: %lu" , buffer->size());
    FILE* fp = fopen(this->getZipFilePath().c_str() , "wb");
    log("debug writtern :: %zu" , fwrite(buffer->data() , 1, buffer->size() , fp));
    fclose(fp);
    
    return true;
}

bool ZipManager::unzipZipDataAndDeletePreviousData()
{
    std::string savePath = this->getZipFilePath();
    std::string writablePath = this->getDataFolderPath();
    
    // Delete previous data folder
    FileUtils::getInstance()->removeDirectory(writablePath);
    FileUtils::getInstance()->createDirectory(writablePath);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AppleHelper::ignorePathFromiCloud(writablePath, true, true);
#endif
    
    unzFile zipfile = unzOpen(savePath.c_str());
    
    if (zipfile == NULL) {
        log("Error opening zip file");
        exit(1);
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    
    if (unzGetGlobalInfo(zipfile, &global_info ) != UNZ_OK)
    {
        printf( "could not read file global info\n" );
        unzClose(zipfile);
        exit(2);
    }
    
    // Buffer to hold data read from the zip file.
    char read_buffer[ READ_SIZE ];
    
    // Loop to extract all files
    uLong i;
    for ( i = 0; i < global_info.number_entry; ++i )
    {
        // Get info about current file.
        unz_file_info file_info;
        char filename[MAX_FILENAME];
        if ( unzGetCurrentFileInfo(
                                   zipfile,
                                   &file_info,
                                   filename,
                                   MAX_FILENAME,
                                   NULL, 0, NULL, 0 ) != UNZ_OK )
        {
            printf( "could not read file info\n" );
            unzClose( zipfile );
            exit(3);
        }
        
        // Check if this entry is a directory or file.
        const size_t filename_length = strlen( filename );
        if ( filename[ filename_length-1 ] == '/')
        {
            // Entry is a directory, so create it.
            std::string filePath(writablePath);
            filePath.append(filename);
            FileUtils::getInstance()->createDirectory(filePath);
        }
        else
        {
            // Entry is a file, so extract it.
            printf( "file:%s\n", filename );
            if ( unzOpenCurrentFile( zipfile ) != UNZ_OK )
            {
                printf( "could not open file\n" );
                unzClose( zipfile );
                exit(4);
            }
            
            // Open a file to write out the data.
            
            
            char *p = &filename[0];
            int pos = 1;
            
            while (*p != '\0') {
                if (*p == '/')
                    break;
                else
                    pos++;
                p++;
            }
            
            std::string filePath(writablePath);
            filePath.append(filename);
            log("PATH: %s", filePath.c_str());
            std::ofstream out(filePath.c_str(), std::ios::out | std::ios::binary);
            
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile( zipfile, read_buffer, READ_SIZE );
                if ( error < 0 )
                {
                    printf( "error %d\n", error );
                    unzCloseCurrentFile( zipfile );
                    unzClose( zipfile );
                    exit(5);
                }
                
                out.write(read_buffer, error);
                
            } while ( error > 0 );
            
            out.flush();
            out.close();
        }
        
        unzCloseCurrentFile( zipfile );
        
        // Go the the next entry listed in the zip file.
        if ( ( i+1 ) < global_info.number_entry )
        {
            if ( unzGoToNextFile( zipfile ) != UNZ_OK )
            {
                printf( "cound not read next file\n" );
                unzClose( zipfile );
                exit(6);
            }
        }
    }
    
    unzClose( zipfile );
    
    // Delete zip file
    FileUtils::getInstance()->removeFile(savePath);

    return true;
}

bool ZipManager::deleteZipData()
{
    log("hola");
    return false;
}