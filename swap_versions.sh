#!/bin/sh

rm fl
grep -rE '^#define.*_VERSION.*[0-9][0-9][0-9]\"' . > fl
grep -rE '^#define.*_CLIENT.*[0-9][0-9][0-9]\"' . >> fl

while read line; do

    file=`echo "$line" | sed -e 's/.\/\(.*\):#define[ \t]\{1,\}\([A-Za-z_0-9]\{1,\}\)[ \t]\{1,\}"\([A-Za-z_0-9]\{1,\}\)"/\1/'`
    variable=`echo "$line" | sed -e 's/.\/\(.*\):#define[ \t]\{1,\}\([A-Za-z_0-9]\{1,\}\)[ \t]\{1,\}"\([A-Za-z_0-9]\{1,\}\)"/\2/'`
    version_old=`echo "$line" | sed -e 's/.\/\(.*\):#define[ \t]\{1,\}\([A-Za-z_0-9]\{1,\}\)[ \t]\{1,\}"\([A-Za-z_0-9]\{1,\}\)"/\3/'`

    version_name=`echo $version_old | sed 's/\([A-Za-z0-9_]\{1,\}\)[0-9]\{3\}/\1/'`
    version_num_old=`echo $version_old | sed 's/\([A-Za-z_0-9]\{1,\}\)\([0-9]\{3\}\)/\2/'`

    version_new=`grep -E ${version_name}[0-9]\{3\} "$1" | head -n 1`
    version_num_new=`echo $version_new | sed 's/\([A-Za-z_0-9]\{1,\}\)\([0-9]\{3\}\)/\2/'`

    if [ `expr length "$version_new"` -gt 0 ]; then
	if [ "${version_num_old}" != "${version_num_new}" ]; then
	    echo -en '\E[1;31m'"\033[1${variable} ${version_old} -> ${version_name}${version_num_new}\033[0m"
	    echo "sed -i s/$version_old/${version_name}${version_num_new}/g $file" >> sedscript.sh
	    echo; echo
	else
	    echo -en '\E[32m'"\033[1${variable} ${version_old}\033[0m"
	    echo; echo
	fi
    else
	echo "$line" >> not_found
    fi

done < fl