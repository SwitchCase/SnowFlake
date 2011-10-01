#!/bin/bash

# Creates a Jail in the directory.
# The jail is capable of running a C/C++ binary and /bin/bash although you will not be able to ls etc.,. in it
if [ $# -lt 1 ]; then
	echo "Usage: $0 <jail directory>\n"
	exit 1
fi
JAIL=$1
USR=prisoner
GRP=prison
if [ $JAIL = "/" ]; then
	echo "Not a good idea to use $JAIL as JAIL!!!\n"
	exit 1
fi
echo "Creating Jail at $JAIL\n"

if [ ! -d $JAIL ]; then
	mkdir $JAIL
fi

if [ -d $JAIL ]; then
	for x in usr bin var dev etc home lib root
	do
		echo "Created $JAIL/$x\n"
		mkdir -p $JAIL/$x
		chmod 0544 $JAIL/$x
	done
fi
mkdir $JAIL/home/$USR
chmod 0777 $JAIL/home/$USR
echo "Creating passwd and group files\n"
echo "root:x:0:0:root:/root:/bin/bash\n$USR:x:1001:1001:$USR:/home/$USR:/dev/null\n" > $JAIL/etc/passwd
echo "root:x:0\n$GRP:x:1001\n" > $JAIL/etc/group
chattr -i $JAIL/etc/passwd
chattr -i $JAIL/etc/group
echo "Creating $JAIL/dev/null\n"
mknod $JAIL/dev/null c 1 3
echo "Setting up files for bash\n"
cp /bin/bash $JAIL/bin/bash
echo "int main() {}" > $JAIL/home/$USR/sample.cpp
g++ $JAIL/home/$USR/sample.cpp -o $JAIL/home/$USR/sample
for progs in /bin/bash /usr/bin/g++ $JAIL/home/$USR/sample 
do
	for x in `ldd -v $progs | awk -F " => " '{print $2}' | sed 's/(.*)//g' | sed '/^\s*$/d' | sort -u`
	do
		echo "Copying $x\n"
		DIR=${x%/*}
		if [ ! -d $JAIL/$DIR ]; then
			mkdir -p $JAIL/$DIR 
		fi	
		cp $x $JAIL/$x
		chmod 0555 $JAIL/$x
	done
done
