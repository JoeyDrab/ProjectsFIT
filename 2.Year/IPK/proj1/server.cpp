#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <functional>
#include <fstream>


using namespace std;
inline bool fexists (const std::string& name);


void socket();

int main(int argc, char** argv)              
{
    int port=0;         // port 55555
    //size_t position;

    /******************** nacitanie argumentov **********************/
    //cout << argc << endl;
    if(argc == 2)
    {
      //cout << "prvy: " << argv[1] << endl;
      //cout << "druhy: " << argv[2] << endl;
      if(!strcmp(argv[1],"-help")!=0)
      {
        cout << "Autor: Jozef Drab [xdrabj00]\nDatum: 12.3.2018" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        cout << "pre spustenie servera zadaj: ./ipk-server -p -[port]" << endl;
        cout << "pre spustenie klienta zadaj: ./ipk-client -h -[host] -p -[port] [-r|-w] -[file]\n";
        cout << "--------------------------------------------------------------------------------\n";
        return 0;
      }
      else 
      {
        cerr << "Zadaj '-help' pre napovedu!\n";
        return 0;
      }
    }
    else if(argc==3)
     {                                    
        if(strcmp(argv[1],"-p")!=0)     
        {
          cerr << "CHYBNY PRVY ARGUMENT NA VSTUPE!\n";
          cerr << "Zadaj '-help' pre napovedu!\n";
          return -1; 
        }
        // PORT (55555) if(isnum(argv[4],"")==0)
        port = atoi(argv[2]);

        if(!isdigit(port))
        {
          if(0 > port || port > 65535)
          {
            cerr << "CHYBNY STVRTY ARGUMENT NA VSTUPE!\n";
            cerr << "Zadaj '-help' pre napovedu!\n";
            return -1;
          }
        }
        else {
          cerr << "CHYBNY STVRTY ARGUMENT NA VSTUPE!\n";
          cerr << "Zadaj '-help' pre napovedu!\n";
          return -1;
        }

     }
    else 
    {    
      cerr << "NEVHODNY POCET ARGUMENTOV!\n";
      cerr << "Zadaj '-help' pre napovedu!\n";
      return -1;
    } 
    cout << "Spustenie: Cakam ..\n";
    /******************** koniec nacitania argumentov **********************/
    int client_socket = 0;
    int foreign_socket;
    struct sockaddr_in ServerAdr;
    struct sockaddr_in ClientAdr;
    //int addrlen = sizeof(address);

    /************************ socket() *******************************/
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
      cerr << "Chyba: Neuspesne vytvorenie socketu!\n";
      return -1;
    }

    ServerAdr.sin_family = AF_INET;
    ServerAdr.sin_addr.s_addr = INADDR_ANY;
    ServerAdr.sin_port = htons( port );
    //int hhh = bind(client_socket, (struct sockaddr *)&ServerAdr,sizeof(ServerAdr));
    //cout << "bind je: " << hhh << "\n";

    /************************ bind() *******************************/
    if (bind(client_socket, (struct sockaddr *)&ServerAdr,sizeof(ServerAdr))<0) 
                                 
    {
        cerr << "Chyba: Neuspesne prevedenie funkcie bind()!\n";
        return -1;
    }
    /************************ listen() *******************************/
    if (listen(client_socket, 6) < 0) 
    {
      cerr << "Chyba: Neuspesne prevedenie funkcie listen()!\n";
      return -1;
    }
    /************************ accept() *******************************/
    socklen_t SizeOfClientAdr = sizeof(ClientAdr);
    foreign_socket = accept(client_socket, (struct sockaddr *)&ClientAdr, &SizeOfClientAdr);

    if (foreign_socket < 0) 
    {
      cerr << "Chyba: Neuspesne prevedenie funkcie accept()!\n";
      return -1;
    }
    /************************ Spojenie *******************************/
    // zavolanie funkcie pre prenos - int RealConnection()
    int reading;
    char message[256];
    string final_message;
    string command;
    string littleFile;
    string StrMessage;
    string ContentsOfFile;
    string firstMessage;
    int position;
    ofstream writeMyFile;
    ifstream readMyFile;
    bool put = false;
    bool konec = false;
    bzero(message, 256);

    // nacitavam spravu
    while( konec == false && (reading = read(foreign_socket,message,256)) ) 
    {
      if( reading < 0)
      {
        cerr << "Chyba: Neuspesne prevedenie funkcie read()!\n";
        return -1;
      }
      else
      {
        if (message[0] == 'G' && message[1] == 'E' && message[2] == 'T')
        {
          command = "GET";
          StrMessage = message;
          position = StrMessage.find("|"); // pozicia "|" v obsahu
          littleFile = StrMessage.substr(3,(position-2)); 
          if(fexists (littleFile)==false)
          {
            StrMessage = "FnF"; // file not found
            if(send(foreign_socket, StrMessage.c_str(), StrMessage.length(), 0) < 0)
            {
              cerr << "Chyba: Odoslanie zlyhalo!\n" << endl;
              return -1;
            }
            return 0;
          }
          /**************************************************/
          readMyFile.open(littleFile);
          char output[256];
          //ContentsOfFile
          if (readMyFile.is_open()) {
            while (!readMyFile.eof()) {

                readMyFile >> output;
                ContentsOfFile = ContentsOfFile + output;
                ContentsOfFile = ContentsOfFile + "\n";
                //ContentsOfFile.append(output);
            }
            ContentsOfFile = ContentsOfFile.substr(0,ContentsOfFile.length()-1);
            ContentsOfFile += "\r\n\r\n";
            readMyFile.close();
          }
          if(send(foreign_socket, ContentsOfFile.c_str(), ContentsOfFile.length(), 0) < 0)
          {
            cerr << "Chyba: Odoslanie zlyhalo!\n" << endl;
            return -1;
          }
          /**************************************************/
        }
        else if ((message[0] == 'P' && message[1] == 'U' && message[2] == 'T') || put == true)
        {
          put = true;
          command = "PUT";
          if (message[0] == 'P' && message[1] == 'U' && message[2] == 'T')
          {
            firstMessage = message;
            position = firstMessage.find("|"); // pozicia "|" v obsahu
            littleFile = firstMessage.substr(3,(position-3)); // subor : myfile.xml
            StrMessage = firstMessage.substr((position+1),firstMessage.length()); // zvysok
          }
          StrMessage += message; // cely obsah suboru 
          if(StrMessage.find("\r\n\r\n") != string::npos) konec = true;      
          bzero(message,256);
        
          // prijatie obsahu suboru 
          /************************ zapisanie do suboru ***********/
          if (konec == true) 
          {
            writeMyFile.open(littleFile);
            //ContentsOfFile
            if (writeMyFile.is_open()) {
                writeMyFile << StrMessage;
            }
            writeMyFile.close();
          }
          /************************ zatvorenie suboru ***********/
        }  
      }
      bzero(message, 256);
      //final_message.append(message);      

    }
    close(foreign_socket);

    /*

    //GET
    //skontrolujn ci existuje subor
    //poslem write
    //koniec

    //PUT
    //odpis OK
    //read
    //vytvor subor zapis dopnho
    //konec

    //odpoved
    */
    cout << "Koniec: Komunikacia ukoncena!\n";
  }

  inline bool fexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


