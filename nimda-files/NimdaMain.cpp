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
		const string funcMap[] = {
			"help", "users", "rusers", "groups", "memuse", "svstat", "ausers", "econf", "close", "cpc"
		};
		int strMap = 
			( argtest == funcMap[0] ) ? 0 : 
			( argtest == funcMap[1] ) ? 1 : 
			( argtest == funcMap[2] ) ? 2 : 
			( argtest == funcMap[3] ) ? 3 :
			( argtest == funcMap[4] ) ? 4 : 
			( argtest == funcMap[5] ) ? 5 : 
			( argtest == funcMap[6] ) ? 6 : 
			( argtest == funcMap[7] ) ? 7 : 
			( argtest == funcMap[8] ) ? 8 : 
			( argtest == funcMap[9] ) ? 9 : 0
		;
		switch ( strMap ){
			case 0:
				help();
				break;
			case 1:
				showUsers( argc, argv );
				break;
			case 2:
				removeUser( argc, argv );
				break;
			case 3:
				showGroups( argc, argv );
				break;
			case 4:
				showMemory();
				break;
			case 5:
				serverUtilization( argc, argv );
				break;
			case 6:
				addUsers( argc, argv );
				break;
			case 7:
				editConfigFile( argc, argv );
				break;
			case 8:
				editPort( argc, argv );
				break;
			case 9:
				cyCmd( argc, argv );
				break;
		}
	}
	return 0;
}
