#include "chardev.h"

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include"stdint.h"
 int ioctl_read_gyro_x(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_GYRO_X,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor gyro x:%d\n",*data);
         return 0;
  }
  
   int ioctl_read_gyro_y(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_GYRO_Y,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor gyro y:%d\n",*data);
         return 0;
  }

 int ioctl_read_gyro_z(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_GYRO_Z,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor gyro z:%d\n",*data);
         return 0;
  }

int ioctl_read_accelero_x(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_ACCELERO_X,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor accelero x:%d\n",*data);
         return 0;
  }
  
  int ioctl_read_accelero_y(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_ACCELERO_Y,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor accelero y:%d\n",*data);
         return 0;
  }
  
  int ioctl_read_accelero_z(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_ACCELERO_Z,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor accelero z:%d\n",*data);
         return 0;
  }
  
  
  int ioctl_read_magneto_x(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_MAGNETO_X,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor magneto x:%d\n",*data);
         return 0;
  }
  
  int ioctl_read_magneto_y(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_MAGNETO_Y,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor magneto y:%d\n",*data);
         return 0;
  }

  int ioctl_read_magneto_z(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_MAGNETO_Z,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor magneto z:%d\n",*data);
         return 0;
  }
  
  
  int ioctl_read_baro_z(int file)
  {
     int ret;
     uint16_t *data;
     char *message;
     
       ret= ioctl(file,READ_BARO,message);
       data=(uint16_t*)message;
         if(ret<0) {
            printf("ioctl read failed:%d",ret);
            exit(-1);
         }
         
         printf("Data from sensor baro:%d\n",*data);
         return 0;
  }
  
  int ioctl_write_file(int file,char * message)
  {
     int ret;
     ret= ioctl(file,WRITE_FILE,message);
         if(ret<0) {
            printf("ioctl write failed:%d",ret);
            exit(-1);
         }
  
  }




int main()
{
  int file;
  char  mess =52;
     file = open(DEVICE_FILE_NAME,0);
        if(file<0)
        {
           printf("This file cannot be opened: %s \n",DEVICE_FILE_NAME);
           exit(-1);
         }  
         /*
            calling different fuction to read different sensor parameters
         */
           ioctl_read_gyro_x(file);
           ioctl_read_gyro_y(file);
           ioctl_read_gyro_z(file);
         
           ioctl_read_accelero_x(file);
           ioctl_read_accelero_y(file);
           ioctl_read_accelero_z(file);
         
           ioctl_read_magneto_x(file);
           ioctl_read_magneto_y(file);
           ioctl_read_magneto_z(file);
           
           ioctl_read_baro_z(file);
           /*
              function to write to the file using ioctl function
           */
           ioctl_write_file(file,&mess);
         
           
         
         close(file);
         
         
         
         


   return 0;
}
