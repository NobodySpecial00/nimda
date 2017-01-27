#include <iostream>
#include <unistd.h>
#include "nimda_cmd.h"
using namespace std;
int main(int argc, char* argv[]){
	if ( getuid() != 0 )
		cout << "Run as root." << endl;
	else{
		if ( argc < 2 )
			help();
		string argtest = argv[1];
		if      ( argtest == "help"               )
			help();
		else if ( argtest == "users"              )
			showUsers( argc, argv );
		else if ( argtest == "remusers"        )
			removeUser( argc, argv );
		else if ( argtest == "groups"             )
			showGroups( argc, argv );
		else if ( argtest == "memuse"             )
			showMemory();
		else if ( argtest == "serverstat"         )
			serverUtilization( argc, argv );
		else if ( argtest == "addusers"           )
			addUsers( argc, argv );
		else if ( argtest == "econf"           )
			editConfigFile( argc, argv );
		else if ( argtest == "close" )
			editPort( argc, argv );
		else
			cout << "Argument not found." << endl;
	}
	return 0;
}
