#include <iostream>
#include <fstream>
#include "clip/clip.h"

using namespace std;

int main() {
    string action;
    cin>>action;
    fstream fio;
    fio.open("pws.txt", ios::app | ios::out | ios::in);

    if(action == "ENCRYPT"){
        string plainText, key, application;
        cout<<"Application:";
        cin>>application;
        cout<<"Plain Text:";
        cin>>plainText;
        cout<<"Key:";
        cin>>key;
        for(int i=1;i<=key.length();i++) {
            for (int x = 1; x <= plainText.length(); x++) {
                if(x>(i-1)*(plainText.length()/key.length()) & x<(i+1)*(plainText.length()/key.length())){
                    if(int(plainText[x-1]) + int(key[i-1])<127){
                        plainText[x-1] = char(int(plainText[x-1]) + int(key[i-1]));
                    }
                    else{
                        plainText[x-1] = char(int(plainText[x-1]) + int(key[i-1])-95);
                    }
                }
                if(i==key.length() & x>(i)*(plainText.length()/key.length())){
                    if(int(plainText[x-1]) + int(key[i-1])<127){
                        plainText[x-1] = char(int(plainText[x-1]) + int(key[i-1]));
                    }
                    else{
                        plainText[x-1] = char(int(plainText[x-1]) + int(key[i-1])-95);
                    }
                }
            }
        }

        fio<<application<<":"<<plainText<<endl;
    }

    if(action == "DECRYPT" || action =="decrypt" || action=="d"){
        string fileText, cryptText, key, application, userApp;
        cryptText, application = "";
        int c = 0;
        cout<<"Application:";
        cin>>userApp;
        cout<<"\n";
        cout<<"Key:";
        cin>>key;
        getline(fio, fileText);
        int x = -1;

        while(application != userApp && c < fileText.length()) {

            for (int i = x+1; i < fileText.length(); i++) {
                if (fileText[i] == *":") {
                    c = i;
                    break;
                }
            }
            for (int i = 0; i < c; i++) { application += fileText[i]; }
            cout<<application;
            x=c;
        }
        for(int i=c+1;i<fileText.length();i++){cryptText += fileText[i];}

        for(int i=1;i<=key.length();i++) {
            for (int x = 1; x <= cryptText.length(); x++) {
                if(x>(i-1)*(cryptText.length()/key.length()) & x<(i+1)*(cryptText.length()/key.length())){
                    if(int(cryptText[x-1]) - int(key[i-1])>31){
                        cryptText[x-1] = char(int(cryptText[x-1])-int(key[i-1]));
                    }
                    else{
                        cryptText[x-1] = char(int(cryptText[x-1])-int(key[i-1])+95);
                    }
                }
                if(i==key.length() & x>(i)*(cryptText.length()/key.length())){
                    if(int(cryptText[x-1]) - int(key[i-1])>31){
                        cryptText[x-1] = char(int(cryptText[x-1])-int(key[i-1]));
                    }
                    else{
                        cryptText[x-1] = char(int(cryptText[x-1])-int(key[i-1])+95);
                    }
                }
            }
        }

        clip::set_text(cryptText);
    }

    fio.close();
    return 0;
}
