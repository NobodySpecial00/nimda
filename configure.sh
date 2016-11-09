#/bin/bash
compile_cpp(){
	if (g++ nimda-files/NimdaMain.cpp nimda-files/nimda_cmd.cpp); then
		echo "KommandorMain compiled"
		if (mv a.out nimda); then
			echo "Renamed \"a.out\" to nimda."
		fi
	fi
}
create_bin_file(){
	if [ -e /usr/bin/nimda ]; then
		echo "/usr/bin/nimda already created."
	else
		if (mv nimda /usr/bin/nimda); then
			echo "nimda /usr/bin file generated."
		fi
	fi
}
compile_cpp
create_bin_file
