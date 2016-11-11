#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <sys/stat.h>
using namespace std;
char red	[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char normal	[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
const string driveType[] = {"sdb", "sdb1"};
class runVars{
	public:
		string runVar;
};
runVars rv;
void help(){
	cout << "USAGE" << endl;
        cout << "\tnimda [options] [parameters] " << endl;
        cout << "\tnimda editconf [apache/sshd/logins]" << endl;
        cout << "\tnimda removeusers/addusers [user1, user2, ...]" << endl;
        cout << "\tnimda users [search string (similar to getent)]" << endl;
	cout << "OPTIONS" << endl;
        cout << "\thelp        : Displays this help prompt." << endl;
        cout << "\teditconf    : Edits a configuration file based on flags." << endl;
        cout << "\tusers       : Displays the system users." << endl;
        cout << "\taddusers    : Adds the listed users in an interactive prompt." << endl;
        cout << "\tgroups      : Displays the system groups." << endl;
        cout << "\tremoveusers : Completely removes a specified user." << endl; 
        cout << "\tmemuse      : Show the system memory usage." << endl;
        cout << "\tserverstat  : Display the server utilization." << endl;
        cout << "\tsetiptable  : Interactively generate iptables firewalls." << endl;
        cout << "\tencrypt     : Encrypts a file using gpg." << endl;
	cout << "\tbackup      : Backs up the specified directory." << endl;
}
void err_call( string x ){
	cout << red << x << normal << endl;
}
void showUsers( int argc, char* argv[] ){
	ifstream passwd("/etc/passwd");
	if ( passwd ){
		if ( argc > 2 ){
			if ( string( argv[2] ) == "all" ){
				rv.runVar = "cat /etc/passwd";
				system( (rv.runVar).c_str() );
			}
			cout << "Showing all " << argv[2] << " in passwd: " << endl;
			rv.runVar = "cat /etc/passwd | grep " + string( argv[2] );
			system( (rv.runVar).c_str() );
		}
		else{
			cout << "Users with BASH shell: " << endl;
			system("cat /etc/passwd | grep bash");
			cout << "---" << endl;
			cout << "Users with ZSH shell: " << endl;
			system("cat /etc/passwd | grep zsh");
			cout << "---" << endl;
			cout << "Users with Korn shell: " << endl;
			system("cat /etc/passwd | grep ksh");
			cout << "---" << endl;
			passwd.close();
		}
	}else{
		err_call("/etc/passwd file not found.");
	}
	passwd.close();
}
void addUsers( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << "adding user " << argv[2] << endl;
		rv.runVar = "sudo adduser " + string( argv[2] );
		system( (rv.runVar).c_str() );
		if ( argc > 3 ){
			rv.runVar = "sudo adduser " + string( argv[3] );
			system( (rv.runVar).c_str() );
			if ( argc > 4 ){
				rv.runVar = "sudo adduser " + string( argv[3] );
				system( (rv.runVar).c_str() );
			}
		}
	}
}
void showGroups( int argc, char* argv[] ){
	ifstream group("/etc/group");
	if( group ){
		cout << "Displaying groups: " << endl;
		system("cat /etc/group");
		group.close();

	}else{
		err_call("/etc/group not found.");

	}
	group.close();
}

void prompt(){
	cout << "Nimda, your friendly neighborhood Linux admin tool. " << endl;
}
void removeUser( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << "removing user " << argv[2] << endl;
		rv.runVar = "sudo userdel -r " + string( argv[2] );
		system( (rv.runVar).c_str() );
		if ( argc > 3 ){
			rv.runVar = "sudo userdel -r " + string( argv[3] );
			system( (rv.runVar).c_str() );
			if ( argc > 4 ){
				rv.runVar = "sudo userdel -r " + string( argv[4] );
				system( (rv.runVar).c_str() );
			}
		}
	}
}
void encryptFile( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << "encrypting file " << argv[2] << endl;
		rv.runVar = "sudo gpg -c " + string( argv[2] );
		system ( (rv.runVar).c_str() );
	}
}
void serverUtilization( int argc, char* argv[]){
	cout << "Uptime: " << endl;
	system("sudo uptime");
	cout << "---" << endl;
	cout << "Users connected: " << endl;
	system("sudo who -a");
	cout << "---" << endl;
	cout << "Last three logins: " << endl;
	system("sudo last -a | head -3");
	cout << "---" << endl;
	cout << "Most expensive process: " << endl;
	system("sudo top -b | head -10 | tail -4");
	cout << "---" << endl;
	cout << "Open ports: " << endl;
	system("netstat -antl");
	cout << "---" << endl;
	cout << "Current connections: " << endl;
	system("sudo ss -ilnsp");
	cout << "---" << endl;
}
void editFirewall(int argc, char* argv[]){
	if ( argc < 3 ){
		err_call("missing parameters.");
	}
	else{
		string argtwo = argv[2];
		if ( argtwo == "save" )
			system("iptables save");
		else if ( argtwo == "status" )
			system("iptables status");
		else if ( argtwo == "flush" )
			system("iptables -F");
		else if ( argtwo == "build" ) {
			cout << "Choose filter chain: " << endl;
			cout << "1.) chain=\"INPUT\"" << endl;
			cout << "2.) chain=\"OUTPUT\"" << endl;
			cout << "3.) chain=\"FORWARD\"" << endl;
			string filteropt;
			cout << ">";
			cin >> filteropt;
			string chain;
			if ( filteropt == "1" )
				chain = "INPUT";
			else if ( filteropt == "2")
				chain = "OUTPUT";
			else if ( filteropt == "3" )
				chain = "FORWARD";
			else
				err_call("Invalid parameter.");
			cout << "Get source IP address: " << endl;
			cout << "1.) Firewall using a single source IP." << endl;
			cout << "2.) Firewall using a source subnet." << endl;
			cout << "3.) Firewall using all source networks." << endl;
			string filtertype;
			cout << ">";
			cin >> filtertype;
			string ipsource;
			if ( filtertype == "1" ){
				cout << "Entre the IP of the source: " << endl;
				cout << ">";
				cin >> ipsource;
			}
			else if ( filtertype == "2"  ){
				cout << "Enter the SUBNET of the source" << endl;
				cout << ">";
				cin >> ipsource;
			}
			else if ( filtertype == "3" )
				ipsource = "0/0";
			else
				err_call("Invalid parameter.");
			cout << "Get destination IP address: " << endl;
			cout << "1.) Firewall using a single destination IP." << endl;
			cout << "2.) Firewall using a destination SUBNET." << endl;
			cout << "3.) Firewall using all destination networks." << endl;
			string filterdest;
			cout << ">";
			cin >> filterdest;
			string ipdest;
			if ( filterdest == "1" ){
				cout << "Enter the IP of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}
			else if ( filterdest == "2" ){
				cout << "Enter the SUBNET of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}
			else if ( filterdest == "3" ){
				ipdest = "0/0";
			}
			else
				err_call("Invalid parameter.");
			cout << "Get protocol: " << endl;
			cout << "1.) Block all TCP traffic." << endl;
			cout << "2.) Block a specific TCP service." << endl;
			cout << "3.) Block a specific port." << endl;
			string filterprot;
			cout << ">";
			cin >> filterprot;
			string proto;
			if ( filterprot == "1" )
				proto = "TCP";
			else if ( filterprot == "2" ) {
				cout << "Enter the TCP service name: " << endl;
				cout << ">";
				cin >> proto;
			}
			else if ( filterprot == "3" ){
				cout << "Enter the port name: " << endl;
				cout << ">";
				cin >> proto;
			}
			else
				err_call("Invalid parameter.");
			cout << "Get rule: " << endl;
			cout << "1.) rule=\"ACCEPT\"" << endl;
        		cout << "2.) rule=\"REJECT\"" << endl;
  	     		cout << "3.) rule=\"DROP\"" << endl;
       			cout << "4.) rule=\"LOG\"" <<endl;
			string filterrule;
			cout << ">";
			cin >> filterrule;
			string rule;
			if ( filterrule == "1" )
				rule = "ACCEPT";
			else if ( filterrule == "2" )
				rule = "REJECT";
			else if ( filterrule == "3" )
				rule = "DROP";
			else if ( filterrule == "4" )
				rule = "LOG";
			else
				err_call("Invalid parameter.");
			cout << "The generated rule is: " << endl;
			cout << red << "iptables -A " << chain << " -s " << ipsource << " -d " << ipdest << " -p " << proto << " -j " << rule << normal << endl;
			cout << "Save the rule to IP tables (y/n)?" << endl;
			string savetables;
			cout << ">";
			cin >> savetables;
			if ( savetables == "y"){
				rv.runVar = "iptables -A " + chain + " -s " + ipsource + " -d " + ipdest + " -p " + proto + " -j " + rule;
				system( (rv.runVar).c_str() );

			}
			else{
				err_call("Option other than \"y\" specified.");
			}
		}
	}
}
void showMemory(){
	cout << "Used memory: " << endl;
	system("vmstat -s -SM | grep used | grep memory | sed -e 's/^[ \t]*//'");
	cout << "---" << endl;
	cout << "Used swap: " << endl;
	system("vmstat -s -SM | grep used | grep swap | sed -e 's/^[ \t]*//'");
	cout << "---" << endl;
	cout << "Used disk space per filesystem: " << endl;
	system("df -H | grep -vE '^Filesystem|tmpfs|cdrom' | awk '{ print $5 \"\t\" $1 }'");
	cout << "---" << endl;
	cout << "CPU usage: " << endl;
	system("lscpu | grep CPU");
	cout << "---" << endl;
	cout << "Free output: " << endl;
	system("free -h");
	cout << "---" << endl;
	cout << "CPU load average: " << endl;
	double load[3];  
   	if (getloadavg(load, 3) != -1){  
   		printf("%f , %f , %f\n", load[0],load[1],load[2]);
		if ( load [0] > 0.50 ){
			err_call("CPU load average is above 0.50!");
		}
	}
	cout << "---" << endl;
}
void editConfigFile( int argc, char* argv[] ){
	if ( argc < 3 ){
		err_call("missing parameters.");
	}
	else{
		cout << "Editing configuration file. " << endl;
		rv.runVar = string( argv[2] );
		if ( rv.runVar == "sshd" ){
			rv.runVar = "vim /etc/ssh/sshd_config";
			system( (rv.runVar).c_str() );
		}
		else if ( rv.runVar == "logins" ){
			rv.runVar = "vim /etc/login.defs";
			system( (rv.runVar).c_str() );
		}
		else if ( rv.runVar == "apache" ){
			if ( argc > 3 ){
				string apacheType = string( argv[3] );
				if ( apacheType == "default" ){
					rv.runVar = "vim /etc/apache2/sites-enabled/000-default.conf";
					system( (rv.runVar).c_str() );
				}
			}
			else{
				rv.runVar = "vim /etc/apache2/apache2.conf";
				system( (rv.runVar).c_str() );

			}
		}
	}
}
void dirBackup( int argc, char* argv[] ){
	time_t curtime = time(0);
	char* time = ctime(&curtime);
	const int dir_err = mkdir(time, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	int x = 0;
	while ( x <= 1 ){
		cout << driveType[x] << endl;
		x++;
	}
}
// You must be kidding; to think you can really get away with what you've done.
