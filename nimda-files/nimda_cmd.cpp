#include <iostream>
#include <cstdlib>
using namespace std;
class runVars{
	public:
		void runCmd(string run){
			system( (run).c_str() );
		}
};
runVars rv;
void help(){
	cout << "USAGE" << endl;
        cout << "\tnimda [options] [parameters] " << endl;
	cout << "OPTIONS" << endl;
        cout << "\thelp        : Displays this help prompt." << endl;
        cout << "\teconf       : Edits a configuration [0-6]." << endl;
        cout << "\tusers       : Displays the system users." << endl;
        cout << "\taddusers    : Adds the listed users in an interactive prompt." << endl;
        cout << "\tgroups      : Displays the system groups." << endl;
        cout << "\tremusers    : Completely removes a specified user [x, y, z]." << endl; 
        cout << "\tmemuse      : Show the system memory usage." << endl;
        cout << "\tserverstat  : Display the server utilization." << endl;
	cout << "\tclose       : Closes a specified port [0-1, port]." << endl;
}
void showUsers( int argc, char* argv[] ){
	if ( argc > 2 ){
		if ( string( argv[2] ) == "all" ){
			rv.runCmd("cat /etc/passwd");
		}
		cout << "Showing all " << argv[2] << " in passwd: " << endl;
		rv.runCmd("cat /etc/passwd | grep " + string( argv[2] ));
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
	}
}
void addUsers( int argc, char* argv[] ){
	if ( argc < 3){
		cout << "missing parameters." << endl;;
	}
	else{
		cout << "adding user " << argv[2] << endl;
		rv.runCmd("sudo adduser " + string( argv[2] ));
		if ( argc > 3 ){
			rv.runCmd("sudo adduser " + string( argv[3] ));
			if ( argc > 4 ){
				rv.runCmd("sudo adduser " + string( argv[3] ));
			}
		}
	}
}
void showGroups( int argc, char* argv[] ){
	if ( argc > 2 ){
		cout << "Showing all " << argv[2] << " in group: " << endl;
		rv.runCmd("cat /etc/group | grep " + string( argv[2] ));
	}
	else{
		cout << "Displaying groups: " << endl;
		system("cat /etc/group");
	}
}
void removeUser( int argc, char* argv[] ){
	if ( argc < 3){
		cout << "missing parameters." << endl;
	}
	else{
		switch ( argc ){
			case 3:
				rv.runCmd("sudo userdel -r " + string( argv[2] ));
				break;
			case 4:
				rv.runCmd("sudo userdel -r " + string( argv[2] ));
				rv.runCmd("sudo userdel -r " + string( argv[3] ));
				break;
			case 5:
				rv.runCmd("sudo userdel -r " + string( argv[2] ));
				rv.runCmd("sudo userdel -r " + string( argv[3] ));
				rv.runCmd("sudo userdel -r " + string( argv[4] ));
				break;
			case 6:
				rv.runCmd("sudo userdel -r " + string( argv[2] ));
				rv.runCmd("sudo userdel -r " + string( argv[3] ));
				rv.runCmd("sudo userdel -r " + string( argv[4] ));
				rv.runCmd("sudo userdel -r " + string( argv[5] ));
				break;
			default:
				cout << "no argument found.";
				break;
		}
	}
}
void serverUtilization( int argc, char* argv[]){
	cout << "Users connected: " << endl;
	system("sudo who -a");
	cout << "---" << endl;
	cout << "Last three logins: " << endl;
	system("sudo last -a | head -3");
	cout << "---" << endl;
	cout << "Most expensive process: " << endl;
	system("sudo top -b | head -10 | tail -4");
	cout << "---" << endl;
	cout << "Listening connections: " << endl;
	system("netstat -tulpn");
	cout << "---" << endl;
	cout << "Current connections: " << endl;
	system("sudo ss -ilnsp");
	cout << "---" << endl;
	cout << "Network files being operated by a program: " << endl;
	system("sudo lsof -i -n -P");
	cout << "---" << endl;
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
}
void editConfigFile( int argc, char* argv[] ){
	if ( argc < 3 ){
		cout << "missing parameters." << endl;
	}
	else{
		cout << "Editing configuration file. " << endl;
		string convert = string(argv[2]);
		int condition = atoi( convert.c_str() );
		switch ( condition ){
			case 0:
				rv.runCmd("vim /etc/ssh/sshd_config");
				break;
			case 1:
				rv.runCmd("vim /etc/login.defs");
				break;
			case 2:
				rv.runCmd("vim /etc/security/limits.conf");
				break;
			case 3:
				rv.runCmd("vim /etc/apt/sources.list");
				break;
			case 4:
				rv.runCmd("vim /etc/sysctl.conf");
				break;
			case 5:
				rv.runCmd("vim /etc/rc.local");
				break;
			case 6:
				rv.runCmd("vim /etc/hosts");
				break;
			case 7:
				rv.runCmd("vim /etc/lightdm/lightdm.conf");
			default:
				cout << "option not found";
				break;
		}
	}
}
void editPort( int argc, char* argv[] ){
	if ( argc < 3 ){
		cout << "missing parameters." << endl;
	}else{
		string convert = string( argv[2] );
		int condition = atoi( convert.c_str() );
		switch ( condition ){
			case 0:
				rv.runCmd("iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport " + string(argv[3]) + " -j DROP");
			case 1:
				rv.runCmd("iptables -A INPUT -p udp -s 0/0 -d 0/0 --dport " + string(argv[3]) + " -j DROP");
		}
	}
}
// Paranoid, so paranoid.