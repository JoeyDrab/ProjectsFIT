#!/bin/ksh         

arg_file=false;
arg_nparam=false;
arg_name=cwd;

S100B=""
S100B_count=0
S1KiB=""
S1KiB_count=0
S10KiB=""
S10KiB_count=0
S100KiB=""
S100KiB_count=0
S1MiB=""
S1MiB_count=0
S10MiB=""
S10MiB_count=0
S100MiB=""
S100MiB_count=0
S1GiB=""
S1GiB_count=0
S1GiBun=""
S1GiBun_count=0

if (($# == 0)); then
  echo invalid argument!
fi

	while getopts ":i:n" opt ; do
		case "$opt" in
	    i ) arg_file="$OPTARG";;  
		n ) arg_nparam=true;;
		\?) echo invalid argument! 
   		 esac
	done

shift $((OPTIND-1));
	arg_name=$1 


shopt -s globstar dotglob 

file_count=0
direct_count=0
k=0

cd "$1"

func() {

	if [ -f "$1" ]
	then
	    local var=file_count
	elif [ -d "$1" ]
	then
	    local var=direct_count
	else 
		continue
	fi

	[[ "$(basename "$1")" == .* ]]
	((++$var))

	if [ -f "$1" ]
	then
       	my_file="$n"
       	CHECK=0
       	CHECK=$(wc -c <"$my_file")
       	if [ "$CHECK" -lt 100 ]; 
       	 then
       		if [ "$arg_nparam" == true ];
	       	then
	       		if [ "$S100B_count" -le 79 ]
	       			then
	       			 S100B="$S100B#";	
					 S100B_count=$[$S100B_count+1];
				fi	 
	       	else 
	       		S100B="$S100B#"
    		fi
	    elif [ "$CHECK" -ge 100 ] && [ "$CHECK" -lt 1024 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S1KiB_count" -le 79 ]
	       			then
	       			 S1KiB="$S1KiB#";	
					 S1KiB_count=$[$S1KiB_count+1];
				fi	 
	       	else 
	       		S1KiB="$S1KiB#";
    		fi	     			       		    
	    elif [ "$CHECK" -ge 1024 ] && [ "$CHECK" -lt 10240 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S10KiB_count" -le 79 ]
	       			then
	       			 S10KiB="$S10KiB#";	
					 S10KiB_count=$[$S10KiB_count+1];
				fi	 
	       	else 
	       		S10KiB="$S10KiB#";
    		fi      	       		   	
	    elif [ "$CHECK" -ge 10240 ] && [ "$CHECK" -lt 102400 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S100KiB_count" -le 79 ]
	       			then
	       			 S100KiB="$S100KiB#";	
					 S100KiB_count=$[$S100KiB_count+1];
				fi	 
	       	else 
	       		S100KiB="$S100KiB#";
    		fi       		  
	    elif [ "$CHECK" -ge 102400 ] && [ "$CHECK" -lt 1048576 ];
	     then 
	     	if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1MiB_count" -le 79 ]
	       			then
	       			 S1MiB="$S1MiB#";	
					 S1MiB_count=$[$S1MiB_count+1];
				fi	 
	       	else 
	       		S1MiB="$S1MiB#";
	       	fi	
	    elif [ "$CHECK" -ge 1048576 ] && [ "$CHECK" -lt 10485760 ];
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S10MiB_count" -le 79 ]
	       			then
	       			 S10MiB="$S10MiB#";	
					 S10MiB_count=$[$S10MiB_count+1];
				fi	 
	       	else 
	       		S10MiB="$S10MiB#";
	       	fi       		  
	    elif [ "$CHECK" -ge 10485760 ] && [ "$CHECK" -lt 104857600 ]; 
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S100MiB_count" -le 79 ]
	       			then
	       			 S100MiB="$S100MiB#";	
					 S100MiB_count=$[$S100MiB_count+1];
				fi	 
	       	else 
	       		S100MiB="$S100MiB#";
	       	fi 	       			
	    elif [ "$CHECK" -ge 104857600 ] && [ "$CHECK" -lt 1073741824 ]; 
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1GiB_count" -le 79 ]
	       			then
	       			 S1GiB="$S1GiB#";	
					 S1GiB_count=$[$S1GiB_count+1];
				fi	 
	       	else 
	       		S1GiB="$S1GiB#";
	       	fi 
	    else 
	     if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1GiBun_count" -le 79 ]
	       			then
	       			 S1GiBun="$S1GiBun"	
					 S1GiBun_count=$[$SS1GiBun_count+1];
				fi	 
	       	else 
	       		S1GiBun="$S1GiBun#";
	       	fi 	
	       			  	  
		fi
	fi 
}

for n in **; do
	if [ "$arg_file" != "$n" ]; then 
	func "$n"
	fi
done

echo Root directory: $arg_name;
echo "Directories: " $direct_count
echo "All files: " $file_count
echo File size histogram:

echo '  <'100 B  ' ':  $S100B 
echo '  <'1 KiB  ' ':  $S1KiB 
echo '  <'10 KiB :  $S10KiB 
echo '  <'100 KiB:  $S100KiB 
echo '  <'1 MiB '' :  $S1MiB 
echo '  <'10 MiB :  $S10MiB 
echo '  <'100 MiB:  $S100MiB 
echo '  <' 1 GiB:  $S1GiB 
echo '  >=' 1GiB: $S1GiBun