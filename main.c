#include <stdio.h>
#include <stdlib.h>
struct elements{
	char *stack;
	int top;
	int stack_size;
	char *queue;
	int front;
	int rear;
	int queue_size;
	char log_history[500];/*This is for log history */
	int log_index;
};
int reading_total_line(char *);/*This function returns the total line of the file*/
struct elements* reading_lines(char *,int,struct elements *);/*Reads the first input file for initialization*/
int is_stack_full(struct elements *);/*Chekcs stack availablity*/
int is_stack_empty(struct elements *); /*Chekcs stack availability*/
void push(struct elements *,char);/*Add new element to top of stack*/
void pop(struct elements *); /*Decrement the top of stack,doesn't delete the top element*/
char get_element_stack(struct elements *);/*Access the top element of stack*/
int is_queue_full(struct elements *);/*Check queue availability*/
int is_queue_empty(struct elements *);/*Check queue availability*/
void enqueue(struct elements *,char);/*Add new element to rear of the queue*/
void dequeue(struct elements *);/*Incerements the front of the queue*/
int commands(char *,struct elements *,int);/*Executes the commands from second input file*/
void write(struct elements *,int,char *);/*Write the each log history*/
int main(int argc, char* argv[])
{
	int total_size=0;
	total_size=reading_total_line(argv[1]);/*Accessing the first line and returning*/
	struct elements *array=(struct elements*)malloc(total_size*sizeof(struct elements));
	/*Allocate the memory according to firs line of given input file.*/
	/*This struct array includes clients and server*/
	array=reading_lines(argv[1],total_size,array);/*This function initalize the stack and queue size of struct*/
	commands(argv[2],array,total_size-1);
	write(array,total_size,argv[3]);
	free(array);

}
int reading_total_line(char *file_name){
	int c;
	int q,s;
	FILE *input_file;
	if ((input_file = fopen(file_name,"r")) == NULL){
       printf("Error! opening file");

        /* Program exits if the file pointer returns NULL. */
       return -1;
	   
   }else{
	fscanf(input_file,"%d",&c);/*Read first line*/
	
	fclose(input_file);
	return c;
	
   }
   
}
struct elements* reading_lines(char *file_name,int size,struct elements *array){
	int q,s,i,c;
	
	FILE *input_file;
	if ((input_file = fopen(file_name,"r")) == NULL){
       printf("Error! opening file");

        /* Program exits if the file pointer returns NULL. */
  
	   
   }else{
	   fscanf (input_file, "%d", &c);
	 for(i=0;i<size;i++){
		 
		 fscanf (input_file, "%d %d", &q,&s);
		 array[i].stack_size=s;
		 array[i].queue_size=q;
		 array[i].stack=malloc(array[i].stack_size*sizeof(char));
		 array[i].queue=malloc(array[i].queue_size*sizeof(char));
		 array[i].top=-1;
		 array[i].front=-1;		 
		 array[i].rear=-1;
		 array[i].log_index=-1;

	 }
	fclose(input_file);
	
   }
   return array;
}
int is_stack_full(struct elements *element){
	
	if(element->top==element->stack_size-1){
		return 1;
	}
	return 0;
}
int is_stack_empty(struct elements *element){
	if(element->top==-1){
		return 1;
	}
	return 0;
}
void push(struct elements *element,char c){
	
	if(!is_stack_full(element)){
		
		element->stack[++element->top]=c;
	}else{
		element->log_history[++element->log_index]='2';
		element->log_history[element->log_index+1]='\0';
	}
	
}
void pop(struct elements *element){
	if(!is_stack_empty(element)){
		element->top--;
	}
}
char get_element_stack(struct elements *element){
	if(!is_stack_empty(element)){
		return element->stack[element->top];
	}
	else{
		printf("Stack is empty\n");
	}
	
}
int is_queue_full(struct elements *element){
	
	if((element->front==element->rear+1)||(element->front==0&&element->rear==element->queue_size-1)){
		return 1;
	}
		
	return 0;
}
int is_queue_empty(struct elements *element){
	if(element->front==-1){

		return 1;
	}
	return 0;
}
void enqueue(struct elements *element,char c){
	if(!is_queue_full(element)){
		if(element->front==-1){
			element->front=0;
		}
		/*Circular queue for efficient memory usage*/
		element->rear=(element->rear+1)%element->queue_size;
		element->queue[element->rear]=c;
	}else{
		element->log_history[++element->log_index]='1';
		element->log_history[element->log_index+1]='\0';
	}
}
void dequeue(struct elements *element){
	if(!is_queue_empty(element)){
		if(element->front==element->rear){
			element->rear=-1;
			element->front=-1;
		}else{
			element->front=(element->front+1)%element->queue_size;
		}
	}
}
int commands(char *file_name,struct elements *array2,int serverIndex){
	int i,index,commandSize;
	char slot1,slot2,slot3;
	FILE *input_file;
	if ((input_file = fopen(file_name,"r")) == NULL){
       printf("Error! opening file");

        /* Program exits if the file pointer returns NULL. */
  
	   
   }else{
	   fscanf (input_file, "%d", &commandSize);
	    for(i=0;i<commandSize;i++){
		 
		 fscanf (input_file, " %c %c %c",&slot1,&slot2,&slot3);
		 if(slot1=='A'){
			 index=slot2-'0'-1;
			 enqueue(&array2[index],slot3);
			 
		 }
		 if(slot1=='I'){
			 index=slot2-'0'-1;
			 push(&array2[index],slot3);
		 }
		 if(slot1=='S'){
			 index=slot2-'0'-1;
			 if(!is_stack_empty(&array2[index])){
				 array2[index].log_history[++array2[index].log_index]=array2[index].stack[array2[index].top];
				 array2[index].log_history[array2[index].log_index+1]='\0';
				 enqueue(&array2[serverIndex],get_element_stack(&array2[index]));
				 pop(&array2[index]);
				 
			 }
			 else{
				 if(!is_queue_empty(&array2[index])){
					 array2[index].log_history[++array2[index].log_index]=array2[index].queue[array2[index].front];
					 array2[index].log_history[array2[index].log_index+1]='\0';
					 enqueue(&array2[serverIndex],array2[index].queue[array2[index].front]);
					 dequeue(&array2[index]);
					 
				 }else{
					 array2[index].log_history[++array2[index].log_index]='3';
					 array2[index].log_history[array2[index].log_index+1]='\0';
				 }
			 }
		 }
		 if(slot1=='O'){
			 if(!is_stack_empty(&array2[serverIndex])){
				 array2[serverIndex].log_history[++array2[serverIndex].log_index]=array2[serverIndex].stack[array2[serverIndex].top];
				 array2[index].log_history[array2[index].log_index+1]='\0';
				 pop(&array2[serverIndex]);
			 }else{
				 if(!is_queue_empty(&array2[serverIndex])){
					 array2[serverIndex].log_history[++array2[serverIndex].log_index]=array2[serverIndex].queue[array2[serverIndex].front];
					 array2[serverIndex].log_history[array2[serverIndex].log_index+1]='\0';
					 dequeue(&array2[serverIndex]);
				 }else{
					 array2[serverIndex].log_history[++array2[serverIndex].log_index]='3';
					 array2[serverIndex].log_history[array2[serverIndex].log_index+1]='\0';
				 }
				 
			 }
			 
		 }
	 }
	
   }
   return 1;
}
void write(struct elements *array2,int index,char *outputfile){
	int i,j;
	FILE *output_file;
	output_file=fopen(outputfile,"w");
	for(i=0;i<index;i++){
		for(j=0;j<=array2[i].log_index;j++){
		fprintf(output_file,"%c ",array2[i].log_history[j]);
		}
		fprintf(output_file,"\n");
	}
	
}