/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

unsigned int maximum(unsigned int i, unsigned int j) {
  if(i >= j) {
    return i;  
  } else {
    return j;  
  }
}

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
  // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
  //260762008 Tianze Lin

  	FILE *bmpfile = fopen(bmp_filename,"rb");
	
	//check BM and data size
	char b,m;
	fread(&b,1,1,bmpfile);
	fread(&m,1,1,bmpfile);
	if(b!='B' || m!='M'){
		printf("Wrong File.");
		exit(-1);
	}
	unsigned int dataSize;
	fread(&dataSize,1,sizeof(unsigned int),bmpfile);
	if(dataSize==0){
		printf("Wrong File.");
		exit(-1);
	}
	fclose(bmpfile);
	
	//read data into heap and store
	*data_size=dataSize;
	bmpfile = fopen(bmp_filename,"rb");
	*img_data = (char*)malloc(dataSize*sizeof(char));
	fread(*img_data,1,dataSize,bmpfile);
	
	//read each of the information fields and store
  	*width=*((unsigned int*)(*img_data+18));
  	*height=*((unsigned int*)(*img_data+22));
  	*bits_per_pixel=*((unsigned int*)(*img_data+28));
  	*data_offset=*((unsigned int*)(*img_data+10));
	
	//compute padding
	int a = *width**bits_per_pixel/8;
	if(a%4 !=0){
		for(int i=1;;i++){
			a++;
			if(a%4==0){
				*padding=i;
				break;
			}
		}
	}
	else{
		*padding=0;
	}
	fclose(bmpfile);
  // TO HERE
  
  return 0;  
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
  // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
	FILE* output_img = fopen(output_bmp_filename, "wb");
	int w= img_width;
	int h = img_height;

	//allocate memory and copy the contents
	unsigned char* img = (unsigned char*)malloc(3*w*h);
	memcpy(img,img_data+54,3*w*h);
	unsigned char* fileheader = (unsigned char*)malloc(14);
	memcpy(fileheader,img_data,14);
	unsigned char* infoheader = (unsigned char*)malloc(40);
	memcpy(infoheader,img_data+14,40);
	
	//write a loop to set the color
	for(int i=0; i<w; i++){
    		for(int j=0; j<h; j++){
			if(i<=x_max && i>=x_min && j<=y_max && j>=y_min){
				int x,y,r,g,b;
                        	x=i; y=j;
        			img[(x+y*w)*3+2] = red;
        			img[(x+y*w)*3+1] = green;
        			img[(x+y*w)*3+0] = blue;
			}
    		}
	}
	unsigned char pad[3] ={0,0,0};
	
	//save the result in a new file
	fwrite(fileheader,1,14,output_img);
	fwrite(infoheader,1,40,output_img);
	for(int i=h-1; i>-1; i--){
    		fwrite(img+(3*w*(h-i-1)),3,w,output_img);
    		fwrite(pad,1,padding,output_img);
	}

	free(img);
	free(fileheader);
	free(infoheader);
	img = NULL;
	fileheader = NULL;
	infoheader = NULL;
	fclose(output_img);	
  // TO HERE!
  
  bmp_close( &img_data );
  
  return 0;
}         

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
  unsigned int w,h;
  unsigned int bpp, data_size, pad, data_offset;
  
  //width and height of the new image
  w = img_width1;
  if(x_offset >= 0) {
    w = maximum(img_width1, img_width2 + x_offset); 
  }else{
    w = maximum(img_width2, img_width1 - x_offset);
  }
  h = img_height1;
  if(y_offset >= 0) {
      h = maximum(img_height1, img_height2 + y_offset); 
  }else{
      h = maximum(img_height2, img_height1 - y_offset);
  }
  
  //coordinate
  unsigned int x_start1, x_start2, y_start1, y_start2;
  unsigned int x_end1, x_end2, y_end1, y_end2;
  x_start1 = 0;
  y_start1 = 0;
  x_start2 = 0;
  y_start2 = 0;
  if(x_offset >= 0) {
    x_start2 = x_offset;
  }else{
    x_start1 = (-1)*x_offset; 
  }
  if(y_offset >= 0) {
    y_start2 = y_offset;
  } else {    
    y_start1 = (-1)*y_offset;
  }
  x_end1 = x_start1 + img_width1;
  y_end1 = y_start1 + img_height1;
  x_end2 = x_start2 + img_width2;
  y_end2 = y_start2 + img_height2;

  //allocate memory
  bpp = maximum(bits_per_pixel1, bits_per_pixel2);
  unsigned int byte_per_pixel = bpp/8;
  data_offset = maximum(data_offset1, data_offset2);
  pad = (4-(w*byte_per_pixel)%4)%4;
  data_size = data_offset + (w*byte_per_pixel + pad)*h;
  char* img = (char*)malloc((data_size+data_offset)*sizeof(char));
  
  //initialize the header and change some information fields
  if(data_offset == data_offset1) {
    memcpy(img, img_data1, data_offset1);
  } else {
    memcpy(img, img_data2, data_offset2);   
  }
  memcpy(img+2, &data_size, sizeof(unsigned int));
  memcpy(img+18, &w, sizeof(unsigned int));
  memcpy(img+22, &h, sizeof(unsigned int));
  memcpy(img+28, &bpp, sizeof(unsigned int));

  //use for loop to edit each pixel to achieve the collage
  for(int y=0; y<y_end1; y++){
	for(int x=0; x<x_end1; x++){
	     if(y>=y_start1 && x>=x_start1){
		 int a = data_offset + x*byte_per_pixel + y*(w*byte_per_pixel + pad);
		 int b = data_offset1 + (x-x_start1)*bits_per_pixel1/8 + (y-y_start1)*(img_width1*bits_per_pixel1/8 + padding1);
		 img[a] = img_data1[b];
		 img[a+1] = img_data1[b+1];
		 img[a+2] = img_data1[b+2];
             }	
	}
  }
  for(int y=0; y<y_end2; y++){
        for(int x=0; x<x_end2; x++){
	     if(y>=y_start2 && x>=x_start2){
                 int a = data_offset + x*byte_per_pixel + y*(w*byte_per_pixel + pad);
                 int b = data_offset2 + (x-x_start2)*bits_per_pixel2/8 + (y-y_start2)*(img_width2*bits_per_pixel2/8 + padding2);
                 img[a] = img_data2[b];
                 img[a+1] = img_data2[b+1];
                 img[a+2] = img_data2[b+2];
             }
		
        }
  }

  //save the result into new file
  FILE* fp = fopen(bmp_result, "wb"); 
  if(fp == NULL) {
    exit (-1);
  }
  fwrite(img, 1, data_size, fp);
  fclose(fp);    
  
  free(img);
  img = NULL;
  // TO HERE!
      
  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
