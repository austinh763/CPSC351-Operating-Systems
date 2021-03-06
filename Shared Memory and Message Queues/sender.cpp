#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include "msg.h"    /* For the message struct */
using namespace std;
//message a;

/* The size of the shared memory chunk */
#define SHARED_MEMORY_CHUNK_SIZE 1000

/* The ids for the shared memory segment and the message queue */
int shmid, msqid;

/* The pointer to the shared memory */
void* sharedMemPtr;

/**
 * Sets up the shared memory segment and message queue
 * @param shmid - the id of the allocated shared memory
 * @param msqid - the id of the shared memory
 */

void init(int& shmid, int& msqid, void*& sharedMemPtr)
{
    /* TODO:
     1. Create a file called keyfile.txt containing string "Hello world" (you may do
     so manually or from the code).
     2. Use ftok("keyfile.txt", 'a') in order to generate the key.
     3. Use the key in the TODO's below. Use the same key for the queue
     and the shared memory segment. This also serves to illustrate the difference
     between the key and the id used in message queues and shared memory. The id
     for any System V objest (i.e. message queues, shared memory, and sempahores)
     is unique system-wide among all SYstem V objects. Two objects, on the other hand,
     may have the same key.
     */

    cout << " in sender program" << endl;
    ofstream outfile("keyfile.txt");
    outfile << "1. Hello world!" << endl;
    outfile << "2. Hello World!" << endl;
    outfile << "3. Hello World!" << endl;
    outfile << "4. Hello world!" << endl;
    outfile << "5. Hello World!" << endl;
    outfile << "6. Hello World!" << endl;
    outfile << "7. Hello world!" << endl;
    outfile << "8. Hello World!" << endl;
    outfile << "9. Hello World!" << endl;
    outfile.close();

    key_t mem_key;
    mem_key = ftok("keyfile.txt",'a');



    /* TODO: Get the id of the shared memory segment. The size of the segment must be SHARED_MEMORY_CHUNK_SIZE */

    shmid = shmget(mem_key,SHARED_MEMORY_CHUNK_SIZE,IPC_CREAT|0666);
    if(shmid == -1 ){
        cout << " error getting shared memory " << endl;
    }
    else if(shmid >0){
        cout << " getting shared memory successful " << endl;
    }


    // what if shmid equals 0
    /* TODO: Attach to the shared memory */
    sharedMemPtr = (void *) shmat(shmid,NULL,0);
    if(sharedMemPtr == NULL){
        cout << " error attaching " << endl;
    }
    else if(sharedMemPtr != NULL){
        cout << " attaching successfull " << endl;
    }



    /* TODO: Attach to the message queue */
    msqid = msgget(mem_key,0666| IPC_CREAT);


    if( msqid == -1){
        cout << "queue was not created" << endl;
    }
    else if(msqid != -1){
        cout << " msg queue created " << endl;
    }

    /* Store the IDs and the pointer to the shared memory region in the corresponding parameters */

}

/**
 * Performs the cleanup functions
 * @param sharedMemPtr - the pointer to the shared memory
 * @param shmid - the id of the shared memory segment
 * @param msqid - the id of the message queue
 */

void cleanUp(const int& shmid, const int& msqid, void* sharedMemPtr)
{
    /* TODO: Detach from shared memory */
    cout << " in sender cleanup " << endl;
    shmdt(sharedMemPtr);



}

/**
 * The main send function
 * @param fileName - the name of the file
 */
void send(const char* fileName)
{
    cout << " in send function  " << endl;
    /* Open the file for reading */
    FILE* fp = fopen(fileName, "r");


    /* A buffer to store message we will send to the receiver. */
    message sndMsg;

    /* A buffer to store message received from the receiver. */
    message rcvMsg;

    /* Was the file open? */
    if(!fp)
    {
        perror("fopen");
        exit(-1);
    }

    /* Read the whole file */
    while(!feof(fp))// finds end of file
    {
        /* Read at most SHARED_MEMORY_CHUNK_SIZE from the file and store them in shared memory.
         * fread will return how many bytes it has actually read (since the last chunk may be less
         * than SHARED_MEMORY_CHUNK_SIZE).
         */
        if((sndMsg.size = fread(sharedMemPtr, sizeof(char), SHARED_MEMORY_CHUNK_SIZE, fp)) < 0)
        {
            perror("fread");
            exit(-1);
        }

        sndMsg.mtype = 1;
        sndMsg.size = SHARED_MEMORY_CHUNK_SIZE;
        /* TODO: Send a message to the receiver telling him that the data is ready
         * (message of type SENDER_DATA_TYPE)
         */

        if(msgsnd(msqid,&sndMsg ,sizeof(sndMsg),0)){
            perror("Message receive error");
            exit(1);
        }


        /* TODO: Wait until the receiver sends us a message of type RECV_DONE_TYPE telling us
         * that he finished saving the memory chunk.
         */
        if(msgrcv(msqid, &rcvMsg, sizeof(rcvMsg), RECV_DONE_TYPE,0) < 0){
            perror("message receive error");
            exit(1);
        }
    }


    /** TODO: once we are out of the above loop, we have finished sending the file.
     * Lets tell the receiver that we have nothing more to send. We will do this by
     * sending a message of type SENDER_DATA_TYPE with size field set to 0.
     */
    sndMsg.mtype = SENDER_DATA_TYPE;
    sndMsg.size = 0;
    if(msgsnd(msqid,&sndMsg,sizeof(sndMsg),0) < 0) {
        perror("message send error");
        exit(1);
    }


    /* Close the file */
    fclose(fp);

}


int main(int argc, char** argv)
{

    /* Check the command line arguments */
    if(argc < 2)
    {
        fprintf(stderr, "USAGE: %s <FILE NAME>\n", argv[0]);
        exit(-1);
    }

    /* Connect to shared memory and the message queue */
    init(shmid, msqid, sharedMemPtr);

    /* Send the file */
    send(argv[1]);

    /* Cleanup */
    cleanUp(shmid, msqid, sharedMemPtr);
    cout << " done" << endl;

    return 0;
}
