/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FliteScene Interface Source Code
++ FliteScene License holders are authorized to use this source code file 
++ for the purposes of integrating FliteScene with their software applications
++ in accordance with the license agreement.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++
++ Copyright (C) Harris Corporation 2006, 2010, 2016, 2017 - All Rights Reserved
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++ FILE:              IF_File_Services.h
++
++ CLASSIFICATION:    Unclassified
++
++ DESCRIPTION:
++
++      The File Services Interface defines procedures for loading file data
++     from a specified path.
++
++
++ LIMITATIONS: none
++
++ SOFTWARE HISTORY:
++
++  Refer to ClearCase for software history.
++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef _IF_FILE_SERVICES_H
#define _IF_FILE_SERVICES_H 1

#ifdef __cplusplus
extern "C" {
#endif

/**Documentation
 ******************************************************************************
 **  Reads in the given file based on the commands passed in.
 **
 **  Inputs:
 **    szFilename - Path/Filename of the target
 **    nOffset    - Offset (in bytes) from the beginning of the file
 **    nCount     - Number of bytes to read into the buffer
 **    pBuffer    - Pointer to a location to store the bytes
 **
 **  Returns:
 **  int - Number of bytes read from the file
 **
 *****************************************************************************/
int CSDM_Read(const char* szFilename,
                    int   nOffset,
                    int   nCount,
                    void* pBuffer);

/**Documentation
 ******************************************************************************
 **  Writes the given buffer either appending to a specified file, or
 **  obliterating the existing file and replacing it with a new file. This
 **  function can also serve to create a new file without performing a write
 **  operation by setting nCount to 0.
 **
 **  Inputs:
 **    szFilename - Path/Filename of the target
 **    nOffset    - Offset (in bytes) from the beginning of the file to perform
 **                 the write operation
 **    nCount     - Number of bytes to write into the file. Setting nCount to 0
 **                 will prevent the write operation from occurring and will
 **                 either create a new file or replace an existing file with an
 **                 empty file.
 **    nAppend    - 1 to append the data to an existing file
 **                 0 to delete the existing file and write the data to a new file
 **    pBuffer    - Pointer to a location of the data to store
 **    
 **  Returns:
 **    int - Number of bytes successfully written
 **
 *****************************************************************************/
int CSDM_Write(const char* szFilename,
                     int   nOffset,
                     int   nCount,
                     int   nAppend,
               const void* pBuffer);

/**Documentation
 ******************************************************************************
 ** Sets the file I/O console output
 **
 ** Input:
 **  nMode - 0 = Disabled (default)
 **          1 = Report File-Not-Found warnings
 **          2 = Report all file operations
 **
 *****************************************************************************/
void CSDM_SetFileReporting(int nMode);

#ifdef __cplusplus
/* close extern "C" block */
}
#endif

#endif
