#include "http.h" /* the HTTP facil.io extension */
#include <string.h>
#include <pthread.h>
#include <stdio.h>


double x01	= 0.0f;
double x02	= 0.0f;
double x11	= 0.0f;
double x12	= 0.0f;

double u	= 0.0f;

int on = 0;

FILE *f;



void on_request(http_s *request);
void* simulation();

void handleInputUpdate(char *path);
void handleGetSpeed();

FIOBJ HTTP_HEADER_X_DATA;

pthread_mutex_t mutex;


int main(void) {
  pthread_t simThread;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&simThread, NULL, simulation, NULL);

  
  
  
  HTTP_HEADER_X_DATA = fiobj_str_new("X-Data", 6);
  http_listen("3000", NULL, .on_request = on_request, .log = 1);
  fio_start(.threads = 1);
  
  fiobj_free(HTTP_HEADER_X_DATA);
}


char request_path[250];


void on_request(http_s *request) {
  
  strcpy(request_path, fiobj_obj2cstr(request->path).data);
  
  if (strncmp(request_path, "/input/", 7) == 0) {
  
  	 handleInputUpdate(request_path);
  	 http_set_cookie(request, .name = "my_cookie", .name_len = 9, .value = "data",
                  .value_len = 4);
  	http_set_header(request, HTTP_HEADER_CONTENT_TYPE,
                  http_mimetype_find("txt", 3));
  	http_set_header(request, HTTP_HEADER_X_DATA, fiobj_str_new("my data", 7));
  	http_send_body(request, "input set\n", strlen("input set\n"));
  	 
  }
  else if (strncmp(request_path, "/getSpeed", 9) == 0) {
  
  	double x02c = 0.0f;
  	pthread_mutex_lock(&mutex);	
  	x02c = x02;
  	pthread_mutex_unlock(&mutex);
  	
  	char buf[24];
  	sprintf(buf, "%lf", x02c);
  	
  	http_set_cookie(request, .name = "my_cookie", .name_len = 9, .value = "data",
                  .value_len = 4);
	http_set_header(request, HTTP_HEADER_CONTENT_TYPE,
	         http_mimetype_find("txt", 3));
	http_set_header(request, HTTP_HEADER_X_DATA, fiobj_str_new("my data", 7));
	http_send_body(request, buf, strlen(buf));
  }
  else if (strncmp(request_path, "/motorOff", 9) == 0){
  	on = 0;
  }
  else if (strncmp(request_path, "/motorOn", 8) == 0){
  	on = 1;
  }
  else {

    	http_set_cookie(request, .name = "my_cookie", .name_len = 9, .value = "data",
                  .value_len = 4);
	http_set_header(request, HTTP_HEADER_CONTENT_TYPE,
	         http_mimetype_find("txt", 3));
	http_set_header(request, HTTP_HEADER_X_DATA, fiobj_str_new("my data", 7));
	http_send_body(request, "404, path not found", strlen("404, path not found"));
    
  }
  	 
  
}

void* simulation() {
  while (1) {
  
    f = fopen("/tmp/comm.bin", "w");
    
    pthread_mutex_lock(&mutex);
    x11 = x01 + 0.005 * x02 + 0.0021 * u * on;
    x12 = x02 * 0.9540 + u * 0.8505 * on;
    
    x01 = x11;
    x02 = x12;
    
    fwrite(&x02, sizeof(double), 1, f);
    fwrite(&u, sizeof(double), 1, f);
    fclose(f);
    
    pthread_mutex_unlock(&mutex);
    
    usleep(5000); 
    
  }
}

void handleInputUpdate(char *path) {
	
	char buf[25];
	strcpy(buf, path+7);
	u = (double) atoi(buf);
		
}



