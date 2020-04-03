/*------------------------------------------------------------------------------
  Copyright (c) 2020 The Simple Scheduler Project. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be found
  in the LICENSE file.
------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    char ch, file_name[50]="periodicSchedule.txt";
    FILE *fp;
    fp = fopen(file_name,"r");
    if(fp == NULL){
        perror("Error while opening the file");
        perror(file_name);
        exit(EXIT_FAILURE);
    }
    while((ch = fgetc(fp)) != EOF){
        printf("%c",ch);
    }
    fclose(fp);
    
    return 0;
}
