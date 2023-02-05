#include "buffer.h"

struct buffer {
	char *data;
	int size;
	int consumed;
	FILE *file;
};

Buffer *newBuffer(int cap, const char *file){
	Buffer *buffer = (Buffer *)malloc(sizeof(struct buffer));
	if(buffer == NULL) return NULL;

	buffer->size = cap;
	buffer->consumed = 0;
	buffer->data = (char *)malloc(sizeof(char) * buffer->size);
	if(buffer->data == NULL) return NULL;
	buffer->file = fopen(file, "w");
	if(buffer->file == NULL){
		free(buffer->data);
		free(buffer);
		return NULL; 
	}
	return buffer;
}

int pushData(Buffer *buffer, char *answer){
	int tam_answer = strlen(answer);
	if(buffer->consumed + tam_answer > buffer->size){
		writeData(buffer);
	}
	buffer->consumed += snprintf(buffer->data + buffer->consumed, buffer->size - buffer->consumed, "%s", answer);
	return tam_answer;
}

void writeData(Buffer *buffer){
	if(buffer->consumed != 0){
		fprintf(buffer->file, "%s", buffer->data);
		buffer->data[0] = '\0';
		buffer->consumed = 0;
	}
}

void freeBuffer(Buffer *buffer) {
	free(buffer->data);
	fclose(buffer->file);
	free(buffer);
}

void printBuffer(Buffer *buffer){
    printf("%s", buffer->data);
}
