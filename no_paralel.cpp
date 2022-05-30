#include <iostream>
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



    if (choice == 1){
        for (int i = 0; i < msg.size(); i++){
            if(msg[i]==32){
                continue; //32 adalah ASCII karakter spasi, kita akan mengabaikannya
            } else {
                if((msg[i]+key) > 122) {
                    //setelah lowercase z pindah ke a, z ASCII adalah 122
                    int temp = (msg[i] + key) - 122;
                    encryptedText[i] = 96 + temp;
                } else if (msg[i] + key > 90 && msg[i] <= 96){
                    //setelah uppercase Z pindah ke A, 90 adalah Z ASCII
                    int temp = (msg[i] + key) - 90;
                    encryptedText[i] = 64 + temp;
                } else {
                    //karakter berada diantara A-Z & a-z
                    encryptedText[i] += key;
                }

            } //tutup kurung punya if
        }

    }
    else if(choice == 2){
        for (int i = 0; i < msg.size(); i++){
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

    if (choice == 1){
        cout << "Pesan setelah enkripsi cipher: " ;
        cout<<encryptedText;
    }
    else if(choice == 2){
        cout << "Pesan setelah dekripsi cipher: " ;
        cout<<decryptedText;
    }
        
    cout<<endl;
	duration = ((float)(t1.tv_usec - t0.tv_usec) / 1000000) + (float)(t1.tv_sec - t0.tv_sec);
	
	cout << "Duration: " << duration << " s"<< endl;
    return 0;

}
