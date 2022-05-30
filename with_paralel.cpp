#include <iostream>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

int main()
{

    int choice,thread, ID,key,length;
    choice = 2;
    struct timeval t0, t1;
    float duration;
    string msg,encryptedText,decryptedText;

    msg = "MPI’s send and receive calls operate in the following manner. First, process A decides a message needs to be sent to process B. Process A then packs up all of its necessary data into a buffer for process B. These buffers are often referred to as envelopes since the data is being packed into a single message before transmission (similar to how letters are packed into envelopes before transmission to the post office). After the data is packed into a buffer, the communication device (which is often a network) is responsible for routing the message to the proper location. The location of the message is defined by the process’s rank.";
    encryptedText = msg;
    decryptedText = msg;
	key = 3;
    length = msg.length();
    int save[length];
    int local_save[length/thread];

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &thread);
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);

    MPI_Status status;

    if (ID == 0){
            for (int i = 0;i < length;i++){
                save[i] = i;
            }
            
            gettimeofday(&t0, NULL);
    } 

    
    if (choice == 1){
  
        MPI_Scatter (&save,length/thread,MPI_INT,&local_save,length/thread,MPI_INT,0,MPI_COMM_WORLD);

        for (int i =0 ; i < length/thread;i++){
            int x = local_save[i];
            if(msg[x]==32){
                local_save[i] = 32;
            } else {
                if((msg[x]+key) > 122) {
                    local_save[i] = 96 + ((msg[x] + key) - 122);
                } else if (msg[x] + key > 90 && msg[x] <= 96){
                    local_save[i] = 64 + ((msg[x] + key) - 90);
                } else {
                    local_save[i] = msg[x] + key;
                }

            }
        }
        
        MPI_Gather(&local_save , length/thread, MPI_INT , &save , length/thread , MPI_INT , 0 , MPI_COMM_WORLD);

    }
    else if(choice == 2){
       for (int i = (ID * msg.size()/thread); i < (msg.size()/(ID+1)); i ++){
            if(msg[i]==32){
                continue; 
            } else {
                if((msg[i] - key) < 97 && (msg[i] - key) > 90){
                    int temp = (msg[i] - key) + 26;
                    decryptedText[i] = temp;
                } else if((msg[i] - key) < 65){
                    int temp = (msg[i] - key) + 26;
                    decryptedText[i] = temp;
                } else {
                    decryptedText[i] = msg[i] - key;
                }
            }
        } 
    }
        
    else {
        if(ID == 0){
            cout << "Pilihan salah";
        }
        return 0;
    }

    
    gettimeofday(&t1, NULL);
    if (ID == 0)
	{
        if (choice == 1){
            cout << "Pesan setelah enkripsi cipher: " ;
            for (int i =0 ;i < length;i++){
                encryptedText [i]= save[i];
                cout<<encryptedText[i];
            }
        }
        else if(choice == 2){
            cout << "Pesan setelah dekripsi cipher: " ;
            cout<<decryptedText;
        }
        
        cout<<endl;
		duration = ((float)(t1.tv_usec - t0.tv_usec) / 1000000) + (float)(t1.tv_sec - t0.tv_sec);
	
		cout << "Duration: " << duration << " s"<< endl;
	}
    MPI_Finalize();

    return 0;

}
