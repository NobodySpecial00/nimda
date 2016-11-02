#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;

//INITAL VARIABLES
char blue  [] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char red   [] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green [] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

// RUN VARIABLE CLASS
class runVars{
	public:
		string runVar;
};

// RUN VARIABLE INSTANE
runVars rv;

// COLOR PRINT FUNCTIONS
void pcol( string x, string y ){

	// GREEN SETTING
	if      ( x == "green" )
		cout << green << y << normal << endl;

	// RED SETTING
	else if ( x == "red" )
		cout << red << y << normal << endl;

	// BLUE SETTING
	else if ( x == "blue" )
		cout << blue << y << normal << endl;

	// YELLOW SETTING
	else if ( x == "yellow" )
		cout << yellow << y << normal << endl;

}

// GENERATE HELP FUNCTION
void help(){

        // USAGE SYNTAX        
        pcol("blue", "USAGE");
        cout << "kommandor [options] [parameters] " << endl;
        cout << "kommandor editconf [apache/sshd/logins]" << endl;
        cout << "kommandor removeusers/addusers [user1, user2, ...]" << endl;
        cout << "kommandor users [search string (similar to getent)]" << endl;

        cout << " " << endl;

        // OPTIONS
        pcol("blue", "OPTIONS \n");

        // MISC
        pcol("yellow", "Misc: ");
        cout << "help        : Displays this help prompt." << endl;
        cout << "editconf    : Edits a configuration file based on flags. \n" << endl;

        // USER AND GROUP MANAGEMENT
        pcol("yellow", "User and group management: ");
        cout << "users       : Displays the system users." << endl;
        cout << "addusers    : Adds the listed users in an interactive prompt." << endl;
        cout << "groups      : Displays the system groups." << endl;
        cout << "removeusers : Completely removes a specified user. \n" << endl; 

        // MEMORY USE AND STATISTICS
        pcol("yellow", "Memory use and process statistics: ");
        cout << "memuse      : Show the system memory usage." << endl;
        cout << "serverstat  : Display the server utilization. \n" << endl;

        // NETWORKING, ENCRYPTION, AND FIREWALL
        pcol("yellow", "Networking, encryption, and firewall: ");
        cout << "iptobinary  : Converts the following IP address to binary notation." << endl;
        cout << "setiptable  : Interactively generate iptables firewalls." << endl;
        cout << "encrypt     : Encrypts a file using gpg." << endl;
}



// BINARY STRING FOR IP
string toBinary(vector<int> octets){

	// GENERATE RESULT STRING
	string result;

	// FOR UNSIGNED J IN THE OCTET SIZE
	for (unsigned j=0; j < octets.size(); j++){

		// IF J IS GREATER THAN 0
		if (j>0)

			// CONCAT. A PERIOD TO THE BINARY RESULT
			result += '.';

		// SET THE MASK INTEGER
		int mask = 256;

		// WHILE MASK IS GREATER THAN OR EQUAL TO 1
		while (mask>>=1)

			// RESULT ADDS 0 + J IN OCTETS AND MASK INT DIFF THAN 0
			result += '0' + ((octets[j] & mask ) != 0);
	}

	// RETURN THE RESULT STRING
	return result;

}

// CONVERT STRING TO INT VECTOR
int getOctets(string ip, vector<int> &octets){

	// GENERATE SSTREAM
	stringstream ss(ip);

	// GENERATE TEMP STRING
	string temp;

	// WHILE GETLINE OF SS, TEMP, AND PERIOD
	while (getline(ss,temp,'.'))

		// PUSHBACK OCTETS, GENERATE C STRING
		octets.push_back(atoi(temp.c_str()));

	// RETURN 0
	return 0;

}

// GENERTE ERROR CALL FUNCTION
void err_call( string x ){

	// PRINT STIRNG IN RED
	cout << red << x << normal << endl;

}

// SHOW USERS FUNCTION
void showUsers( int argc, char* argv[] ){

	// GENERATE INPUT FILE STREAM FOR PASSWD CHECK
	ifstream passwd("/etc/passwd");

	// IF PASSWD IS EXISTING
	if ( passwd ){

		if ( argc > 2 ){

			// SEARCHING PROMPT
			cout << yellow << "\nSearching for " << argv[2] << " in passwd: " << endl;

			// SET RUNVAR TO THIS AND RUN THIS
			rv.runVar = "cat /etc/passwd | grep " + string( argv[2] );
			system( (rv.runVar).c_str() );

		}
		else{

			// SHOW BASH SHELL USERS
			pcol("yellow", "\nUsers with bash shell: ");
			system("cat /etc/passwd | grep bash");
			cout << "\n --- \n" << endl;

			// SHOW ZSH SHELL USERS
			pcol("yellow", "Users with zsh shell: ");
			system("cat /etc/passwd | grep zsh");
			cout << "\n --- \n" << endl;

			// SHOW KSH SHELL USERS
			pcol("yellow", "Users with ksh shell: ");
			system("cat /etc/passwd | grep ksh");
			cout << "\n --- \n" << endl;

			// CLOSE THE PASSWD FILE STREAM
			passwd.close();
		}
	}else{

		// IF PASSWD IS NOT FOUND SHOW THIS
		err_call("/etc/passwd file not found.");

	}

	// CLOSE THE PASSWD FILE STREAM
	passwd.close();

}

// ADD USERS FUNCTIION
void addUsers( int argc, char* argv[] ){

	// IF ARGUMENTS ARE ADEQUIT
	if ( argc < 3){

		// IF NOT PRINT THIS
		err_call("missing parameters.");

	}
	else{

		// SHOW ADDING USER PROMPT
		cout << yellow << "adding user " << argv[2] << normal << endl;

		// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
		rv.runVar = "sudo adduser " + string( argv[2] );
		system( (rv.runVar).c_str() );

		// IF ARGUMENTS ARE GREATER
		if ( argc > 3 ){

			// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
			rv.runVar = "sudo adduser " + string( argv[3] );
			system( (rv.runVar).c_str() );

			// IF ARGUMENTS ARE GREATER
			if ( argc > 4 ){

				// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
				rv.runVar = "sudo adduser " + string( argv[3] );
				system( (rv.runVar).c_str() );

			}
			// END IF ARGUMENTS ARE GREATER

		}
		// END IF ARGUMENTS ARE GREATER

	}
	// END ELSE OF IF ARGUMENTS ARE ADEQUIT

}

// SHOW GROUPS FUNCTION
void showGroups( int argc, char* argv[] ){

	// GENERATE INPUT FILE STREAM FOR GROUP
	ifstream group("/etc/group");

	// IF THE GROUP FILE IS EXISTING
	if( group ){

		// SHOW DISPLAY GROUP PROMPT
		pcol("yellow", "\nDisplaying groups in the system: ");

		// RUN CAT GROUP
		system("cat /etc/group");

		// GENERATE BLANK LINE
		cout << " " << endl;

		// CLOSE THE GROUP FILE STREAM
		group.close();

	}else{

		// ERROR CALL GROUP NOT FOUND
		err_call("/etc/group not found.");

	}

	// CLOSE GROUP FILE STREAM
	group.close();

}

// GENERATE PROMPT VALUE
void prompt(){

	// GENERATE PROMPT MESSAGE
	pcol("blue", "\nNimda, your friendly neighborhood linux admin tool.");

}

// REMOVE USER FUNCTION
void removeUser( int argc, char* argv[] ){

	// IF INPUT ARGUMENTS ARE LESS THAN 3
	if ( argc < 3){

		// GENERATE THIS ERROR MESSAGE
		err_call("missing parameters.");

	}
	else{

		// DISPLAY REMOVE USER PROMPT
		cout << yellow << "removing user " << argv[2] << normal << endl;

		// REMOVE USER RUN THIS
		rv.runVar = "sudo userdel -r " + string( argv[2] );

		// RUN THE ABOVE PUT INTO THE RUN VARIABLE
		system( (rv.runVar).c_str() );

		// IF ARGUMENTS ARE GREATER THAN 3
		if ( argc > 3 ){

			// SET RUNVAR TO THIS
			rv.runVar = "sudo userdel -r " + string( argv[3] );

			// RUN THE ABOVE PUT INTO RUN VARIABLE
			system( (rv.runVar).c_str() );

			// IF ARGUMENTS ARE GREATER THAN 4
			if ( argc > 4 ){

				// SET RUNVAR TO THIS
				rv.runVar = "sudo userdel -r " + string( argv[4] );

				// RUN THE ABOVE PUT INTO RUN VARIABLE
				system( (rv.runVar).c_str() );

			}
			// END IF ARGUMENTS ARE GREATER THAN 4

		}
		// END IF ARGUMENTS ARE GREATER THAN 3

	}

}

// ENCRYPT FILE FUNCTION
void encryptFile( int argc, char* argv[] ){

	// IF ARGUMENTS ARE LESS THAN 3
	if ( argc < 3){

		// ERROR CALL THIS
		err_call("missing parameters.");

	}
	else{

		// ENCRYPT FILE PROMPT
		cout << yellow << "encrypting file " << argv[2] << normal << endl;

		// MAKE RUN VAR THIS
		rv.runVar = "sudo gpg -c " + string( argv[2] );

		// RUN THIS
		system ( (rv.runVar).c_str() );

	}
	// END ELSE IF ARGUMENTS ARE LESS THAN 3

}


// SERVER STATISTICS FUNCTION
void serverUtilization( int argc, char* argv[]){

	// SERVER UTILIZATION INFORMATION
	pcol("yellow", "Displaying server utilization information: ");
	pcol("green", "Uptime: ");
	system("sudo uptime");
	cout << "\n --- \n" << endl;

	// USERS CONNECTED
	pcol("green", "Users connected: ");
	system("sudo who -a");
	cout << "\n --- \n" << endl;
	pcol("green", "Last 3 logins: ");
	system("sudo last -a | head -3");
	cout << "\n --- \n" << endl;

	// MOST EXPENSIVE PROCESS RUNNING ON THIE SYSTEM
	pcol("green", "Most expensive process: ");
	system("sudo top -b | head -10 | tail -4");
	cout << "\n --- \n" << endl;

	// CURRENT OPEN PORTS
	pcol("green", "Open ports: ");
	system("sudo nmap -sT localhost | grep -E \"(tcp|udp)\"");
	cout << "\n --- \n" << endl;

	// CURRENT CONNECTIONS
	pcol("green", "Current connections: ");
	system("sudo ss -s");
	cout << "\n --- \n" << endl;

}

// IPTABLES FIREWALL FUNCTIOIN
void editFirewall(int argc, char* argv[]){

	// IF ARGUMENTS ARE LESS THAN 3
	if ( argc < 3 ){

		// ERROR CALL THIS
		err_call("missing parameters.");

	}
	else{

		// SET THE THIRD ARGUMENT (SECOND PARAMATER) TO A STRING VALUE
		string argtwo = argv[2];

		// IF ARGTWO IS SAVE
		if ( argtwo == "save" )
			system("iptables save");

		// ELSE IF ARGTWO IS STATUS
		else if ( argtwo == "status" )
			system("iptables status");

		// ELSE IF ARGTWO IS FLUSH
		else if ( argtwo == "flush" )
			system("iptables -F");

		// ELSE IF ARGTWO IS BUILD
		else if ( argtwo == "build" ) {

			// FILTER CHAIN TYPE PROMPT
			pcol("green", "Choose filter chain: ");
			cout << "1.) chain=\"INPUT\"" << endl;
			cout << "2.) chain=\"OUTPUT\"" << endl;
			cout << "3.) chain=\"FORWARD\"" << endl;

			// USER INPUT
			string filteropt;
			cout << ">";
			cin >> filteropt;
			string chain;

			// IF FILTER OPTION IS ONE
			if ( filteropt == "1" )
				chain = "INPUT";

			// ELSE IF FILTER OPTION IS TWO
			else if ( filteropt == "2")
				chain = "OUTPUT";

			// ELSE IF FILTER OPT IS 3
			else if ( filteropt == "3" )
				chain = "FORWARD";

			// ELSE
			else{
				// ERROR CALL THIS
				err_call("Invalid parameter.");

			}
			// END ELSE IF FILTER OPTION IS ONE

			// SOURCE IP ADDRESS PROMPT
			pcol("green", "Get source IP address: ");
			cout << "1.) Firewall using a single source IP." << endl;
			cout << "2.) Firewall using a source subnet." << endl;
			cout << "3.) Firewall using all source networks." << endl;
			string filtertype;
			cout << ">";
			cin >> filtertype;
			string ipsource;

			// IF FILTER TYPE IS ONE
			if ( filtertype == "1" ){
				cout << "Entre the IP of the source: " << endl;
				cout << ">";
				cin >> ipsource;
			}

			// ELSE IF FILTER TYPE IS TWO
			else if ( filtertype == "2"  ){
				cout << "Enter the SUBNET of the source" << endl;
				cout << ">";
				cin >> ipsource;
			}

			// ELSE IF FILTER TYPE IS 3
			else if ( filtertype == "3" ){
				ipsource = "0/0";
			}

			// ELSE
			else{
				// ERROR CALL THIS
				err_call("Invalid parameter.");

			}
			// END ELSE IF FILTER TYPE IS ONE

			// DESTINATION IP ADDRESS PROMPT
			pcol("green", "Get destination IP address: ");
			cout << "1.) Firewall using a single destination IP." << endl;
			cout << "2.) Firewall using a destination SUBNET." << endl;
			cout << "3.) Firewall using all destination networks." << endl;

			// USER INPUT
			string filterdest;
			cout << ">";
			cin >> filterdest;
			string ipdest;

			// IF FILTER DESTINATION IS 1
			if ( filterdest == "1" ){
				cout << "Enter the IP of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}

			// ELSE IF FILTER DESTINATION IS TWO
			else if ( filterdest == "2" ){
				cout << "Enter the SUBNET of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}

			// ELSE IF FILTER DESTINATION IS 3
			else if ( filterdest == "3" ){
				ipdest = "0/0";
			}

			// ELSE
			else{
			
				// ERROR CALL THIS
				err_call("Invalid parameter.");
			
			}

			// GET PROTOCOL PROMPT
			pcol("green", "Get protocol: ");
			cout << "1.) Block all TCP traffic." << endl;
			cout << "2.) Block a specific TCP service." << endl;
			cout << "3.) Block a specific port." << endl;

			// USER INPUT
			string filterprot;
			cout << ">";
			cin >> filterprot;
			string proto;

			// IF FILTER PROTOCOL IS ONE
			if ( filterprot == "1" ){
				proto = "TCP";
			}

			// ELSE IF FILTER PROTOCOL IS TWO
			else if ( filterprot == "2" ) {
				cout << "Enter the TCP service name: " << endl;
				cout << ">";
				cin >> proto;
			}

			// ELSE IF FILTER PROTOCOL IS 3
			else if ( filterprot == "3" ){
				cout << "Enter the port name: " << endl;
				cout << ">";
				cin >> proto;
			}

			// ELSE
			else{

				// ERROR CALL THIS
				err_call("Invalid parameter.");

			}

			// GET RULE PROMPT
			pcol("green", "Get rule: ");
			cout << "1.) rule=\"ACCEPT\"" << endl;
        		cout << "2.) rule=\"REJECT\"" << endl;
  	     		cout << "3.) rule=\"DROP\"" << endl;
       			cout << "4.) rule=\"LOG\"" <<endl;

       			// USER INPUT
			string filterrule;
			cout << ">";
			cin >> filterrule;
			string rule;

			// IF FILTER RULE IS ONE
			if ( filterrule == "1" ){
				rule = "ACCEPT";
			}

			// ELSE IF FILTER RULE IS TWO
			else if ( filterrule == "2" ){
				rule = "REJECT";
			}

			// ELSE IF FILTER RULE IS 3
			else if ( filterrule == "3" ){
				rule = "DROP";
			}

			// ELSE IF FILTER RULE IS 4
			else if ( filterrule == "4" ){
				rule = "LOG";
			}

			// ELSE
			else{

				// ERROR CALL THIS
				err_call("Invalid parameter.");

			}

			// GENERATED RULE PROMPT
			cout << "The generated rule is: " << endl;
			cout << red << "iptables -A " << chain << " -s " << ipsource << " -d " << ipdest << " -p " << proto << " -j " << rule << normal << endl;

			// SAVE THE RULE PROMPT
			pcol("yellow", "Save the rule to IP tables (y/n)?");

			// USER INPUT
			string savetables;
			cout << ">";
			cin >> savetables;

			// IF THE USER WANTS TO SAVE THE TABLES
			if ( savetables == "y"){

				// SET RUNVAR TO THIS
				rv.runVar = "iptables -A " + chain + " -s " + ipsource + " -d " + ipdest + " -p " + proto + " -j " + rule;

				// RUN THIS
				system( (rv.runVar).c_str() );

			}

			// ELSE
			else{

				// ERROR CALL THIS
				err_call("Option other than \"y\" specified.");

			}
			// END ELSE IF THE USER WANTS TO SAVE THE TABLES

		}
		// END ELSE IF ARGTWO IS BUILD

	}
	// END ELSE IF ARGUMENTS ARE LESS THAN 3

}

// IP TO BINARY CONVERSION MAIN FUNCTION
void ipInfoConv( int argc, char* argv[] ){

	// IF ARGUMENTS ARE LESS THAN 3
	if ( argc < 3 ){

		// ERROR CALL THIS
		err_call("mssing parameters.");

	}
	else{

		// SET A STRING FOR THE IP
		string string_ip = string( argv[2] );
		vector<int> octetsIP;

		// RUN GETOCTETS ON VECTOR AND STRING
		getOctets(string_ip, octetsIP);

		// SHOW BINARY VALUE
		cout << "Binary IP: " << toBinary(octetsIP) << endl;
	}
}


// SHOW SYSTEM MEMORY USAGE
void showMemory(){

	// DISPLAYING MEM USE PROMPT
	pcol("yellow", "Displaying memory usage: \n");

	// USED MEMORY PROMPT
	pcol("green", "\nUsed memory: ");
	system("vmstat -s -SM | grep used | grep memory | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;

	// USED SWAP
	pcol("green", "\nUsed swap: ");
	system("vmstat -s -SM | grep used | grep swap | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;

	// FREE DISK SPACE
	pcol("green", "\nFree disk space: ");
	system("df -h | grep -v Filesystem");
	cout << "\n --- \n" << endl;

	// CPU USAGE
	pcol("green", "\nCPU usage: ");
	system("lscpu | grep CPU");
	cout << "\n --- \n" << endl;

	// CPU USAGE
	pcol("green", "\nFree Output: ");
	system("free -h");
	cout << "\n --- \n" << endl;

	// CPU LOADAVERAGE
	pcol("green", "Load average: ");
	double load[3];  

	// IF LOAD AVERAGE FROM GETLOADAVG IS NOT NEGATIVE ONE
   	if (getloadavg(load, 3) != -1){  
   		printf("%f , %f , %f\n", load[0],load[1],load[2]);

   		// IF THE LOAD AVERAGE IS GREATER THAN 50
		if ( load [0] > 0.50 ){

			// ERROR CALL THIS
			err_call("CPU load average is above 0.50!");

		}
		// END IF THE LOAD AVERAGE IS GREATER THAN 50

	}
	// END IF LOAD AVERAGE FROM GETLOADAVG IS NOT NEGATIVE ONE

	// GENERATE BLANK LINE
	cout << "\n --- \n" << endl;

}

void editConfigFile( int argc, char* argv[] ){

	// IF ARGUMENTS ARE LESS THAN 3
	if ( argc < 3 ){

		// ERROR THIS
		err_call("missing parameters.");

	}
	else{

		// PROMPT
		cout << yellow << "Editing configuration file. \n" << normal << endl;

		// SET RUNVAR TO THIS
		rv.runVar = string( argv[2] );

		// IF RUNVAR IS EQUAL TO SSHD
		if ( rv.runVar == "sshd" ){

			// RESET RUNVAR TO THIS THEN RUN IT
			rv.runVar = "vim /etc/ssh/sshd_config";
			system( (rv.runVar).c_str() );

		}
		else if ( rv.runVar == "logins" ){

			// RESET RUNVAR TO THIS THEN RUN IT
			rv.runVar = "vim /etc/login.defs";
			system( (rv.runVar).c_str() );

		}
		else if ( rv.runVar == "apache" ){

			if ( argc > 3 ){

				// GENERATE APACHE TYPE STRING TO ARGUMENT 4
				string apacheType = string( argv[3] );

				// IF APACHE TYPE IS DEFAULT
				if ( apacheType == "default" ){

					// SET RUNVAR TO THIS THEN RUN IT
					rv.runVar = "vim /etc/apache2/sites-enabled/000-default.conf";
					system( (rv.runVar).c_str() );

				}

			}
			else{

				// SET RUNVAR TO THIS THEN RUN IT
				rv.runVar = "vim /etc/apache2/apache2.conf";
				system( (rv.runVar).c_str() );

			}
			// END IF ARGUMENTS ARE GREATER THAN 3

		}
		// END IF RUNVAR IS EQUAL TO SSHD

	}
	// END IF ARGUMENTS ARE LESS THAN 3

}

