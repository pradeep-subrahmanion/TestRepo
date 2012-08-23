#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 100
#define SUCCESS 1
#define FAIL 0

void display(char *buffer,int len) {
 
 int i = 0;

 while(i != len)
   printf("%c\n",buffer[i++]);
  
 
}

void display_code_section(char *buffer) {

   int  sec_tb_off = *(int*)(void *)(buffer +40);
   printf("sec is %d",sec_tb_off);
   display(buffer+sec_tb_off,4);
}

int validate_elf(char *buffer) {

  if(*buffer == 0x7f && *(buffer+1) == 'E' && *(buffer+2) == 'L' && *(buffer+3)=='F')
    return SUCCESS;

 return FAIL;
}

int main(int argc,char **argv) {

  FILE *exec_fd = NULL;

  char *header = malloc(HEADER_SIZE);
  if(argc<2) {

    printf("Usage hackelf <path_to_binary_file>\n");
    return 0;

  }

  exec_fd = fopen(argv[1],"r");

  if(exec_fd == NULL) {

   printf("Error while opening binary file.Please check path.\n");
   return 0;

  }

  int size = fread(header,1,HEADER_SIZE,exec_fd);

  //int bf = header[4];

  //printf("class is %d",bf);

  //if(size != HEADER_SIZE) {

   //printf("error while reading file\n");
   //return 0;
  //}

  int magic_zero = header[0];

  if(validate_elf(header) == SUCCESS)
    printf("Valid elf file\n");
  else
    printf("Invalid elf file\n");

  display_code_section(header);

  free(header);

  fclose(exec_fd); 

}

