#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "nimda_cmd.h"
using namespace std;
int main(int argc, char* argv[]){
	if ( getuid() != 0 ){
		cout << "Please run as root." << endl;
	}
	else{
		if ( argc < 2 ){
			cout << "No parameters found, try \"sudo nimda help\" for commands." << endl;
			return 1;
		}
		string argtest = argv[1];
		if      ( argtest == "help"               )
			help();
		else if ( argtest == "users"              )
			showUsers( argc, argv );
		else if ( argtest == "removeusers"        )
			removeUser( argc, argv );
		else if ( argtest == "groups"             )
			showGroups( argc, argv );
		else if ( argtest == "memuse"             )
			showMemory();
		else if ( argtest == "encrypt"            )
			encryptFile( argc, argv );
		else if ( argtest == "serverstat"         )
			serverUtilization( argc, argv );
		else if ( argtest == "setiptable"         )
			editFirewall( argc, argv );
		else if ( argtest == "addusers"           )
			addUsers( argc, argv );
		else if ( argtest == "editconf"           )
			editConfigFile( argc, argv );
		else if ( argtest == "backup" )
			dirBackup( argc, argv );
		else
			err_call("\nArgument not found.\n");
	}
	return 0;
}
