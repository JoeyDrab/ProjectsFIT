#include <iostream>
#include <fstream>
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

using namespace std;
inline bool fexists (const std::string& name);

int main(int argc, char const *argv[])
{
	int port=0;         // port 55555
    //string host;        // eva.fit.vutbr.cz
    string file;        // myfile.xml
    string hostName;
    string Url;
    string command;		// [-r/-w]
    int position;
    string myhost;
    string argfile;
    //size_t position;

    /******************** nacitanie argumentov **********************/
    if(argc==7)
     {                                    
        if(strcmp(argv[1],"-h")!=0)     
        {
          cerr << "CHYBNY PRVY ARGUMENT NA VSTUPE!\n";
          return 0;
        }
        // HOST (eva.fit.vutbr.cz) if(isnum(argv[2],"")==0)
        Url = argv[2];
        position = Url.find("http://");
        if (position == 0)
        {
        	Url = Url.substr(7,Url.length());
        }
        position = Url.find("www.");
        if (position == 0)
        {
        	Url = Url.substr(3,Url.length());
        }
        position = Url.find(":"); // ziskanie servra
        if(position != 0 && position == -1)
        	myhost = Url;
        else 
        {
	        myhost = Url.substr(0,position);
			Url = Url.substr(position+1,Url.length());
		}


        /**********************************************************/
        
        if(strcmp(argv[3],"-p")!=0)
        {
          cerr << "Chyba: CHYBNY TRETI ARGUMENT NA VSTUPE!\n";
          return 0;
        }

        // PORT (55555) if(isnum(argv[4],"")==0)
        port = atoi(argv[4]);

        if(!isdigit(port))
        {
          if(0 > port || port > 65535)
          {
            cerr << "Chyba: CHYBNY STVRTY ARGUMENT NA VSTUPE!\n";
            return 0;
          }
        }
        else {
          cerr << "Chyba: CHYBNY STVRTY ARGUMENT NA VSTUPE!\n";
          return 0;
        }
        // [-r/-w]
        if( strcmp(argv[5],"-r")==0 || strcmp(argv[5],"-w")==0 )
        {
          command = argv[5];
        }
        else
        {
          cerr << "Chyba: CHYBNY PIATY ARGUMENT NA VSTUPE!\n";
          return 0;
        }
        // myfile.xml
        argfile = argv[6];

     }
    else 
    {    
      cerr << "Chyba: VELA ARGUMENTOV!\n";
      return 0;
    } 
    /******************** koniec nacitania argumentov **********************/
    int MySocket = 0;
    struct sockaddr_in Server;
    struct hostent *hosten;
    struct server_socket;
    //int addrlen = sizeof(address);

    /************************ socket() *******************************/
    if ((MySocket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
      cerr << "Chyba: Neuspesne vytvorenie socketu!\n";
      return -1;
    }
    unsigned int bodka = 0;
    // spocitanie bodiek 
    for (unsigned int ch = 0; ch < myhost.length(); ch++)
    {
    	if(myhost[ch] == '.') bodka++;
    }
    if ( bodka == 3 && isdigit(myhost[0]) )
    {
    	Server.sin_addr.s_addr = inet_addr(myhost.c_str());
    	hostName = myhost.c_str();
    }
    else 
    {
    	//if(isalpha(myhost[0]) && myhost[0] != 'w')
    	//	myhost = "www." + myhost;
    	hosten = gethostbyname(myhost.c_str());
    	if(hosten == NULL)
		{
		    cerr << "Chyba: Neznamy server!\n";
		    return -1;
		}
		hostName = hosten->h_name;
		memmove(&(Server.sin_addr.s_addr), hosten->h_addr_list[0], 4);

    }

    Server.sin_family = AF_INET;
    Server.sin_port = htons( port );
    /************************ Connect *******************************/
    if(connect(MySocket, (struct sockaddr *)&Server, sizeof(Server)) < 0)
    {
    	cerr << "Chyba: Nemozne pripojenie!\n";
    	return -1;
    }
    if (MySocket == -1)
    {
    	cerr << "Chyba: Zlyhanie spojenia!\n";
    }
    /************************ Spojenie *******************************/
    int reading;
    char message[256]; // array with size of 1B 
    string CommMessage;
    string CommFile;
    ofstream writeMyFile;
    ifstream readMyFile;
    string ContentsOfFile;
    // MySocket
    // command
    // Url
    // hostName

    //-r značí, že klient bude ze serveru soubor číst;
    if(command == "-r")
    {
    	CommFile = argfile;
    	CommMessage = "GET" + CommFile;
    	int dlzka = 3;
    	dlzka += argfile.length();

    	if(send(MySocket, CommMessage.c_str(), CommMessage.length(), 0) < 0)
		{
			cerr << "Chyba: Odoslanie zlyhalo!\n" << endl;
			return -1;
		}
		bool konec = false;
		while( (konec == false) && (reading = read(MySocket,message,256)) )
		{
			if( reading < 0)
		    {
		       cerr << "Chyba: Neuspesne prevedenie funkcie read()!\n";
		       return -1;
		    }
		    else 
		    {
		    	if(message[0] == 'F' && message[1] == 'n' && message[2] == 'F')
		    	{
		    		cerr << "Chyba: Subor neexistuje!\n";
		    		return -1;
		    	}
		    	ContentsOfFile += message;
		    	if(ContentsOfFile.find("\r\n\r\n") != string::npos) konec = true;
		    	bzero(message,256); 	
		    }
		}
		writeMyFile.open(argfile);
        //ContentsOfFile
        if (writeMyFile.is_open()) {
            writeMyFile << ContentsOfFile;
        }
        writeMyFile.close();
        //break;
        return 0;
    }
    //-w značí, že klient bude na server soubor zapisovat;
    else if(command == "-w")
    {
    	if(fexists (argfile)==false)
        {
          cerr << "Chyba: Subor neide otvorit alebo neexistuje!\n";
          return 0;
        }
    	
        readMyFile.open(argfile);
 		char output[100];
 		//ContentsOfFile
 		if (readMyFile.is_open()) {
	 		while (!readMyFile.eof()) {

	    		readMyFile >> output;
	    		ContentsOfFile = ContentsOfFile + "\n";
	    		ContentsOfFile.append(output);
			}
		}
		ContentsOfFile += "\r\n\r\n";
		readMyFile.close();

    	CommFile = argfile;
    	CommMessage = "PUT" + CommFile + "|";

    	if(send(MySocket, CommMessage.c_str(), CommMessage.length(), 0) < 0)
		{
			cerr << "Chyba: Odoslanie zlyhalo!\n" << endl;
			return -1;
		}
		//odpoved

		if(send(MySocket, ContentsOfFile.c_str(), ContentsOfFile.length(), 0) < 0)
		{
			cerr << "Chyba: Odoslanie zlyhalo!\n" << endl;
			return -1;
		}
    }
    close(MySocket);
    cout << "End: Komunikacia ukoncena!\n";

}

inline bool fexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}
