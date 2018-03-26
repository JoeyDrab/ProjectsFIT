#!/bin/sh
# Autor: Jozef Drab xdrabj00 FIT VUT 27.03.2017
arg_file=""
arg_nparam=false;
arg_name=cwd;

declare -A matrix
declare -A array
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
filetype=""
a=""

##########################################################
if [ "$#" -eq 0 ]; then
  { echo "    ERROR: Invalid argument!" >&2; exit ; }
fi
if [ "$#" -gt 4 ]; then
  { echo "    ERROR: Invalid argument!" >&2; exit ; }
fi

	while getopts ":i:n" opt ; do
		case "$opt" in
	    i ) arg_file="$OPTARG";;  
	    n ) arg_nparam=true;;
   		 esac
	done
shift $((OPTIND-1));
	arg_name=$1 
if [ "$arg_name" = "$arg_file" ]; then { echo "    ERROR: Equel root directory and ignor_dir!" >&2; exit 1; } fi
charvar=${#arg_name}
lomitko=${arg_name:0:$[$charvar-1]}
lomitko=$lomitko"/"
if [ "$arg_name" = "$lomitko" ]; then { echo "    ERROR: Slash behind dir name!" >&2; exit 1; } fi
if [ "$arg_file" != "" ]; then 
charvar=${#arg_file}
lomitko=${arg_file:0:$[$charvar-1]}
lomitko=$lomitko"/"
fi
if [ "$arg_file" = "$lomitko" ]; then { echo "    ERROR: Slash behind dir name of ignored dir!" >&2; exit 1; } fi
for (( c=0;c<10;c++ )); do
if [[ $arg_name == *$c* ]]; then
  { echo "    ERROR: Invalid name of directory!" >&2; exit 1; } fi
done
for (( c=0;c<10;c++ )); do
if [[ $arg_file == *$c* ]]; then
  { echo "    ERROR: Invalid name of directory!" >&2; exit 1; } fi
done



globway=""
file_count=0
direct_count=0
index=0
counter=0
cd "$1"
#if [ "$cd" = "" ]; then { echo "    ERROR: Directory or file does not exist!" >&2; exit 1; } fi
x=""
y=""
z=0
supercounter=0
##########################################################

func() {

	globway=$1
	globway=${globway##*/}
	if [ "$globway" != "$arg_file" ];
	then
		if [ -f "$1" ]
		then
			supercounter=$[$supercounter+1];
	    		local var=file_count
			 a=`find $n -type f -exec file -b {} \;| sort | uniq -c | sort -n -r | head | sed 's/^[ \t]*//' | tr '\n' ':'`
		 	x=$(echo -e ${a} | cut -d":" -f1)
		 	y=$(echo -e $a | cut -d" " -f2-)
		 	if [ "${matrix[0,0]}" = "" ]; 
		 	 then 
		  	  matrix[0,0]=$y
		  	  matrix[0,1]="${matrix[0,1]}#"
		  	   matrix[0,2]=$[${matrix[0,2]}+1];
			else 
		 		for (( i=0; i <= $[$index+1]; i++ )); do
		 		if [ "$i" -eq "$[$index+1]" ]; 
		 		 then 
		 		 	matrix[$i,0]=$y
		 		 	matrix[$i,1]="${matrix[$i,1]}#"
		 		 	matrix[$i,2]=$[${matrix[$i,2]}+1];	
		 		 	index=$[$index+1];
					break
		 		elif [ "$y" = "${matrix[$i,0]}" ]; 
		 		 then 	
		 		 	if [ "$arg_nparam" == true ];
	       			 	 then 
	       				if [ "$[matrix[$i,2]]" -le 66 ];
	       				 then
	       			 		matrix[$i,1]="${matrix[$i,1]}#"
		  					matrix[$i,2]=$[${matrix[$i,2]}+1];
		  					break
		  				else	
		  					matrix[$i,2]=$[${matrix[$i,2]}+1];
		  					break
						fi	 
	       			else 
	       					matrix[$i,1]="${matrix[$i,1]}#"
		  					matrix[$i,2]=$[${matrix[$i,2]}+1];
		  					break
    				fi  
		  		fi
		 	 	done
			fi
		counter=$[$index+1]
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
	       			if [ "$S100B_count" -le 66 ]
	       			then
	       			 S100B="$S100B#";	
				 S100B_count=$[$S100B_count+1];
				fi	 
	       		else 
	       		S100B="$S100B#"
    			fi
    	##########################################################	
	    elif [ "$CHECK" -ge 100 ] && [ "$CHECK" -lt 1024 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S1KiB_count" -le 66 ]
	       			then
	       			 S1KiB="$S1KiB#";	
					 S1KiB_count=$[$S1KiB_count+1];
				fi	 
	       	else 
	       		S1KiB="$S1KiB#";
    		fi
    	##########################################################		     			       		    
	    elif [ "$CHECK" -ge 1024 ] && [ "$CHECK" -lt 10240 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S10KiB_count" -le 66 ]
	       			then
	       			 S10KiB="$S10KiB#";	
					 S10KiB_count=$[$S10KiB_count+1];
				fi	 
	       	else 
	       		S10KiB="$S10KiB#";
    		fi  
    	##########################################################	    	       		   	
	    elif [ "$CHECK" -ge 10240 ] && [ "$CHECK" -lt 102400 ]; 
	     then 
	     	if [ "$arg_nparam" == true ];
	       	then 
	       		if [ "$S100KiB_count" -le 66 ]
	       			then
	       			 S100KiB="$S100KiB#";	
					 S100KiB_count=$[$S100KiB_count+1];					 
				fi	 
	       	else 
	       		S100KiB="$S100KiB#";
    		fi 
    	##########################################################	      		  
	    elif [ "$CHECK" -ge 102400 ] && [ "$CHECK" -lt 1048576 ];
	     then 
	     	if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1MiB_count" -le 66 ]
	       			then
	       			 S1MiB="$S1MiB#";	
					 S1MiB_count=$[$S1MiB_count+1];
				fi	 
	       	else 
	       		S1MiB="$S1MiB#";
	       	fi	
	    ##########################################################   	
	    elif [ "$CHECK" -ge 1048576 ] && [ "$CHECK" -lt 10485760 ];
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S10MiB_count" -le 66 ]
	       			then
	       			 S10MiB="$S10MiB#";	
				 S10MiB_count=$[$S10MiB_count+1];
			fi	 
	       	else 
	       		S10MiB="$S10MiB#";
	       	fi
	    ##########################################################   	       		  
	    elif [ "$CHECK" -ge 10485760 ] && [ "$CHECK" -lt 104857600 ]; 
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S100MiB_count" -le 66 ]
	       			then
	       			 S100MiB="$S100MiB#";	
					 S100MiB_count=$[$S100MiB_count+1];
				fi	 
	       	else 
	       		S100MiB="$S100MiB#";
	       	fi 	  
	    ##########################################################   	     			
	    elif [ "$CHECK" -ge 104857600 ] && [ "$CHECK" -lt 1073741824 ]; 
	     then 
	       	 if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1GiB_count" -le 66 ]
	       			then
	       			 S1GiB="$S1GiB#";	
					 S1GiB_count=$[$S1GiB_count+1];
				fi	 
	       	else 
	       		S1GiB="$S1GiB#";
	       	fi 
	    ##########################################################   	
	    else 
	     if [ "$arg_nparam" == true ];
	       	 then 
	       		if [ "$S1GiBun_count" -le 66 ]
	       			then
	       			 S1GiBun="$S1GiBun"	
					 S1GiBun_count=$[$SS1GiBun_count+1];
				fi	 
	       	else 
	       		S1GiBun="$S1GiBun#";
	       	fi 	
	       			  	  
		fi
	fi 
fi
}

new_arg=""
for n in **; do
	if [ "$arg_file" != "" ]; then 
	new_arg=$arg_file
	new_arg="$new_arg/";
	if [[ $n != *$new_arg* ]]; then
	func "$n"
	fi
	else func "$n"; fi
done
for (( i = 0; i < counter; i++ )); do
	for (( j = 0; j < counter; j++ )); do
		if [ "$[array[$i,2]]" -lt "$[matrix[$j,2]]" ];
		 then
		 array[$i,0]=${matrix[$j,0]}
		 array[$i,1]=${matrix[$j,1]}
		 array[$i,2]=${matrix[$j,2]}
		 array[$i,3]=$j	
		fi 
	done
	matrix[$[array[$i,3]],2]=0
done

if [ "$counter" -gt 10 ]; 
  then 
	counter=10 
  fi
direct_count=$[$direct_count+1];
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
echo '  <' 1 GiB :  $S1GiB
echo '  >=' 1 GiB:  $S1GiBun
echo File type histogram:

for (( i = 0; i < counter; i++ )); do
	myvar=${array[$i,0]}
	chrlen=${#myvar}
	space=' '
	if [ "$chrlen" -gt 40 ];
	 then
		string=${myvar:0:44}
		string2=${myvar:40:4}
		string3="...:"
		resultst="${string/$string2/$string3}" 
		array[$i,0]=$resultst
		echo '  '${array[$i,0]} ${array[$i,1]}
	else 	
	  if [ "$chrlen" -gt 0 ]; 
	   then
		string4=${myvar:0:$[$chrlen-1]}
		rest=$[40-$chrlen]
		for (( f=0; f <= $[$rest+3]; f++ )); do
		  if [ "$f" -eq "$[$rest+3]" ];
		    then
			string5="$string5:"
		  fi	
		   string4=$string4$space
		done
		string4=$string4":"
		string4=${string4//-/ :}
		echo '  '"${string4//-/ :}" ${array[$i,1]}
	 else echo Unread file!
	  fi
	fi
done
