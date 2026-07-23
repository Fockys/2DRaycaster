#include "../globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dataLocation = NULL;

int setDataDirectory(void){
   char *appData = getenv("AppData");
   if (appData == NULL) {
      dataLocation = "";
      return 1;
   }
   char *directoryName = "\\fockys\\raycast\\";
   size_t appDataLen = strlen(appData);
   size_t pathLen = appDataLen + strlen(directoryName) + 1;
   dataLocation = malloc(pathLen);
   if (dataLocation == NULL) {
      return 1;
   }

   dataLocation = strcat(appData,directoryName);

   
   return 0;
}