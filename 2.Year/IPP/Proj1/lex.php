<?php
/****************************************/
/*			IPP - projekt 1.			*/
/* autor:	Jozef Drab 					*/
/* login: 	xdrabj00					*/
/* datum:	28.2.2018					*/
/* 										*/
/****************************************/
include_once 'table.php';
include_once 'parse.php';


	global $GFarray;
	global $LFarray;
	global $TFarray;

/*********************************************************************/
/*********************************************************************/
function KeywordCheck($string, $queue, $linecounter)
{
	global $GFarray;
	global $LFarray;
	global $TFarray;

	$found = false;

	$arrayOfKeyWords = array("DEFVAR" , "MOVE" , "LABEL" , "JUMPIFEQ" , "WRITE" , 
		"CONCAT" , "JUMP" , "CREATEFRAME" , "PUSHFRAME" , "POPFRAME" , "CALL" , 
		"RETURN" , "PUSHS" , "POPS" , "ADD" , "SUB" , "MUL" , "IDIV" , "LT" , 
		"GT" , "EQ" , "AND" , "OR" , "NOT" , "INT2CHAR" , "STRI2INT" , "READ" , 
		"CONCAT" , "STRLEN" , "GETCHAR" , "SETCHAR" , "TYPE" , "JUMPIFNEQ" , 
		"DPRINT" , "BREAK");

	for ($i = 0; $i<=34; $i++) {
		if (strcasecmp($string, $arrayOfKeyWords[$i]) == 0) {		
			$found = true;
			break;
		}
	}
	// checking if KEYWORD IS ON A RIGHT POSSITION
	if ($found == true && $queue != 0) {
		printf( "ERROR - Lexical error (KeyWord in wrong possition) in line: " );
		echo $linecounter;
		printf( " \n" );
		echo "Program returned 21\n";
		exit(21);
	}
	// checking if FIRST POSSITION BELONGS TO KEYWORD
	else if ($found == false && $queue == 0) {
		printf( "ERROR - Lexical error in line: " );
		echo $linecounter;
		printf( " \n" );
		printf( "Keyword: '" );
		echo $string;
		printf( "' unknown\n" );
		echo "Program returned 21\n";
		exit(21);
	}
	// checking if identificator has int@prem, bool$prem, LF@prem, ...
	$arrayOfRollMop = array("int" , "bool" , "string" , "GF" , "LF" , "TF");

	if ($found == false) {
		if (strpos($string, "@") !== false) {
			$nasloSa = false;
			$ramec = explode("@", $string);
			for ($i=0; $i <= 5; $i++) { 				
				if (!strcmp($ramec[0], $arrayOfRollMop[$i])) {
					$nasloSa = true;
					break;
				}
			}
			if ($nasloSa == false) {
				printf( "ERROR - Lexical error in line: " );
				echo $linecounter;
				printf( " \n" );
				printf( "Unknown: " );
				echo "'";
				echo $ramec[0];
				echo "'";
				printf( " in " );
				echo "'";
				echo $string;
				echo "'";
				printf( " \n" );
				echo "Program returned 21\n";
				exit(21);
			}
			else {
				if (!strcmp($ramec[0], "string") && !strcmp($string, "WRITE")) {
					return true;
				}
				else return false;

			}
		}	
	}
}
function ThrowErr($linecounter) {
	printf( "ERROR -  in line: " );
	echo $linecounter;
	printf( " \n" );
	echo "Program returned 21\n";
	exit(21);
}

/*********************************************************************/
/*********************************************************************/
function MakeLineCheck($pole, $linecounter) {

	global $GFarray;
	global $LFarray;
	global $TFarray;
	global $navestiArray;

	$pole[0] = strtoupper($pole[0]);

	switch ($pole[0]) {
	/*********************************** MOVE ****************************/
    case "MOVE":
    	if(count($pole)<3) {
        	ThrowErr($linecounter);
    	}
    	else if (CheckIfVarExists($pole[1]) == true)
    	{
    		// ak sa premenna nasla
    		WriteToVariable( $pole[1], $pole[2] );
            $conqueror = explode("@", $pole[2]);
            if($conqueror[0] == "string" && count($pole)>3 ) 
            {
                $slovo = 3;          
                while($slovo < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$slovo]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) )
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $slovo++;
                }
            }
            else if(count($pole)>3 && $conqueror[0] != "string") ThrowErr($linecounter);
    	}
    	else ThrowErr($linecounter);
    	break;
    /*********************************** CREATEFRAME ****************************/
    case "CREATEFRAME":
        if(count($pole)!=1) {
        	ThrowErr($linecounter);
        }
        break;
    /*********************************** PUSHFRAME ****************************/
    case "PUSHFRAME":
    	if(count($pole)!=1) {
        	ThrowErr($linecounter);
    	}
        break;
    /*********************************** POPFRAME ****************************/
    case "POPFRAME":
    	if(count($pole)!=1) {
        	ThrowErr($linecounter);
    	}
        break;
    /*********************************** DEFVAR ****************************/
    case "DEFVAR":
    	if(count($pole)!=2) {
        	ThrowErr($linecounter);
        	
    	}
    	else if (CheckIfVarExists($pole[1]) == false) {
    		CreateVariable($pole[1], $linecounter);
    	}
    	else ThrowErr($linecounter);

        break;
    /*********************************** CALL ****************************/
    case "CALL":
    	if(count($pole)!=2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		$pravda = false;
    		$velkostp = count($navestiArray);
    		for ($i=0; $i < $velkostp; $i++) { 
    			if($navestiArray[$i] == $pole[1]) {
    				$pravda = true;
    			}
    		}
    		if ($pravda == false) {
    			global $PoleNeinicNavesti;
    			$PoleNeinicNavesti[count($PoleNeinicNavesti)] = $pole[1];
    		}
    	}
        break;
    /*********************************** RETURN ****************************/
    case "RETURN":
    	if(count($pole)!=1) {
        	ThrowErr($linecounter);
    	}
        break;
    /********************************/
    /*********************************** PUSHS ****************************/
    case "PUSHS":
    	if(count($pole)<2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		// < symb1 >
    		$conqueror1 = explode("@", $pole[1]);
			if ($conqueror1[0] !== "GF" && $conqueror1[0] !== "LF" && $conqueror1[0] !== "TF" && 
				$conqueror1[0] !== "string" && $conqueror1[0] !== "bool" && $conqueror1[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror1[0] == "GF" || $conqueror1[0] == "LF" || $conqueror1[0] == "TF") {
				if(CheckIfVarExists($pole[1]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /*********************************** POPS ****************************/
    case "POPS":
    	if(count($pole)!=2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    	}
        break;
    /*********************************** ADD ****************************/
    /**************************************************************************//*
                else if (CheckIfVarExists($pole[1]) == true)
            {
                // ak sa premenna nasla
                WriteToVariable( $pole[1], $pole[2] );
                $conqueror = explode("@", $pole[2]);
                if($conqueror[0] == "string")
                {
                    $slovo = 3;          
                    while($slovo < count($pole)) // zacina od tretieho konci pri poslednom
                    {
                        $arrayno = str_split($pole[$slovo]);
                        foreach ($arrayno as $char) {
                            if( $char !==  '\\' && !ctype_alnum($char) )
                            {
                               ThrowErr($linecounter); 
                            }
                        }
                        $slovo++;
                    }
                }
            }
            /**************************************************************************/
    case "ADD":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		else {
	    		// < symb1 >
	    		$conqueror = explode("@", $pole[2]);
	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typjedna = GiveMeType($pole[2]);
	    		}
	    		else if($conqueror[0] == "string") {
                    $typjedna = "string";
                    if (count($pole) > 4)
                    {
                        if(strpos($pole[2], "@") === true)
                            $poradie = 3;
                        else 
                        {      
                            $poradie = 3;
                            while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                            {
                                echo "retazec: ";
                                echo $pole[$poradie];
                                echo "\n";
                                if(strpos($pole[$poradie], "@") !== false) break;
                                $arrayno = str_split($pole[$poradie]);
                                foreach ($arrayno as $char) {
                                    echo "pismeno: ";
                                    echo $char;
                                    echo "\n";
                                    if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                                    {
                                       ThrowErr($linecounter); 
                                    }
                                }
                                $poradie++;
                            }
                        }
                    }
                }
	    		else if($conqueror[0] == "bool") $typjedna = "bool";
	    		else if($conqueror[0] == "int") $typjedna = "int";

	    		// < symb2 >
	    		$conqueror = explode("@", $pole[$poradie]);
	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typdva = GiveMeType($pole[3]);
	    		}
	    		else if($conqueror[0] == "string") $typdva = "string";
	    		else if($conqueror[0] == "bool") $typdva = "bool";
	    		else if($conqueror[0] == "int") $typdva = "int";

	    		if ( ($typjedna != "int") || ("int" != $typdva)) {
	    			printf( "ERROR -  Semantics error in line: " );
					echo $linecounter;
					printf( " \nWrong types!\n" );
					echo "Program returned 21\n";
					exit(21);
	    		}
	    	}
    	}
        break;
    /*********************************** SUB ****************************/
    case "SUB":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		else {
	    		// < symb1 >
	    		$conqueror = explode("@", $pole[2]);

	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typjedna = GiveMeType($pole[2]);
	    		}
	    		else if($conqueror[0] == "string") $typjedna = "string";
	    		else if($conqueror[0] == "bool") $typjedna = "bool";
	    		else if($conqueror[0] == "int") $typjedna = "int";

	    		// < symb2 >
	    		$conqueror = explode("@", $pole[3]);
	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typdva = GiveMeType($pole[3]);
	    		}
	    		else if($conqueror[0] == "string") $typdva = "string";
	    		else if($conqueror[0] == "bool") $typdva = "bool";
	    		else if($conqueror[0] == "int") $typdva = "int";

	    		if ( ($typjedna != "int") || ("int" != $typdva)) {
	    			printf( "ERROR -  Semantics error in line: " );
					echo $linecounter;
					printf( " \nWrong types!\n" );
					echo "Program returned 21\n";
					exit(21);
	    		}
	    	}
    	}
        break;
    /*********************************** MUL ****************************/
    case "MUL":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		else {
	    		// < symb1 >
	    		$conqueror = explode("@", $pole[2]);

	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typjedna = GiveMeType($pole[2]);
	    		}
	    		else if($conqueror[0] == "string") $typjedna = "string";
	    		else if($conqueror[0] == "bool") $typjedna = "bool";
	    		else if($conqueror[0] == "int") $typjedna = "int";

	    		// < symb2 >
	    		$conqueror = explode("@", $pole[3]);
	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typdva = GiveMeType($pole[3]);
	    		}
	    		else if($conqueror[0] == "string") $typdva = "string";
	    		else if($conqueror[0] == "bool") $typdva = "bool";
	    		else if($conqueror[0] == "int") $typdva = "int";

	    		if ( ($typjedna != "int") || ("int" != $typdva)) {
	    			printf( "ERROR -  Semantics error in line: " );
					echo $linecounter;
					printf( " \nWrong types!\n" );
					echo "Program returned 21\n";
					exit(21);
	    		}
	    	}
    	}
        break;
    /*********************************** IDIV ****************************/
    case "IDIV":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		else {
	    		// < symb1 >
	    		$conqueror = explode("@", $pole[2]);

	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typjedna = GiveMeType($pole[2]);
	    		}
	    		else if($conqueror[0] == "string") $typjedna = "string";
	    		else if($conqueror[0] == "bool") $typjedna = "bool";
	    		else if($conqueror[0] == "int") $typjedna = "int";

	    		// < symb2 >
	    		$conqueror = explode("@", $pole[3]);
	    		if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    			$typdva = GiveMeType($pole[3]);
	    		}
	    		else if($conqueror[0] == "string") $typdva = "string";
	    		else if($conqueror[0] == "bool") $typdva = "bool";
	    		else if($conqueror[0] == "int") $typdva = "int";

	    		if ( ($typjedna != "int") || ("int" != $typdva)) {
	    			printf( "ERROR -  Semantics error in line: " );
					echo $linecounter;
					printf( " \nWrong types!\n" );
					echo "Program returned 21\n";
					exit(21);
	    		}
	    	}
    	}
        break;
    /********************************/
    /*********************************** LT ****************************/
    case "LT":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror1 = explode("@", $pole[2]);
			if ($conqueror1[0] !== "GF" && $conqueror1[0] !== "LF" && $conqueror1[0] !== "TF" && 
				$conqueror1[0] !== "string" && $conqueror1[0] !== "bool" && $conqueror1[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror1[0] == "GF" || $conqueror1[0] == "LF" || $conqueror1[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
            /**************************************************************/
            if ($conqueror1[0] == "string" && count($pole) > 4)
            {
                if(strpos($pole[2], "@") === true)
                    $poradie = 3;
                else 
                {      
                    $poradie = 3;
                    while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                    {
                        if(strpos($pole[$poradie], "@") !== false) break;
                        $arrayno = str_split($pole[$poradie]);
                        foreach ($arrayno as $char) {
                            if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                            {
                               ThrowErr($linecounter); 
                            }
                        }
                        $poradie++;
                    }
                }   
            }
            else if($conqueror1[0] !== "string" && count($pole) > 4) ThrowErr($linecounter);
            /**************************************************************/
    		// < symb2 >
    		$conqueror2 = explode("@", $pole[$poradie]);
			if ($conqueror2[0] !== "GF" && $conqueror2[0] !== "LF" && $conqueror2[0] !== "TF" && 
				$conqueror2[0] !== "string" && $conqueror2[0] !== "bool" && $conqueror2[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror2[0] == "GF" || $conqueror2[0] == "LF" || $conqueror2[0] == "TF") {
				if(CheckIfVarExists($pole[3]) == false) {
    				ThrowErr($linecounter);
    			}
    		}

            /**************************************************************/
            if ($conqueror2[0] == "string")
            {
                $poradie++;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }
            }
            /**************************************************************/

    	}
        break;
    /*********************************** GT ****************************/
    case "GT":
    	if(count($pole)<4) {
            ThrowErr($linecounter);
        }
        else {
            if(CheckIfVarExists($pole[1]) == false) {
                ThrowErr($linecounter);
            }
            // < symb1 >
            $conqueror1 = explode("@", $pole[2]);
            if ($conqueror1[0] !== "GF" && $conqueror1[0] !== "LF" && $conqueror1[0] !== "TF" && 
                $conqueror1[0] !== "string" && $conqueror1[0] !== "bool" && $conqueror1[0] !== "int") {
                ThrowErr($linecounter);
            }
            else if ($conqueror1[0] == "GF" || $conqueror1[0] == "LF" || $conqueror1[0] == "TF") {
                if(CheckIfVarExists($pole[2]) == false) {
                    ThrowErr($linecounter);
                }
            }
            $poradie = 3;
            /**************************************************************/
            if ($conqueror1[0] == "string" && count($pole) > 4)
            {
                if(strpos($pole[2], "@") === true)
                    $poradie = 3;
                else 
                {      
                    $poradie = 3;
                    while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                    {
                        if(strpos($pole[$poradie], "@") !== false) break;
                        $arrayno = str_split($pole[$poradie]);
                        foreach ($arrayno as $char) {
                            if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                            {
                               ThrowErr($linecounter); 
                            }
                        }
                        $poradie++;
                    }
                }   
            }
            else if($conqueror1[0] !== "string" && count($pole) > 4) ThrowErr($linecounter);
            /**************************************************************/
            // < symb2 >
            $conqueror2 = explode("@", $pole[$poradie]);
            if ($conqueror2[0] !== "GF" && $conqueror2[0] !== "LF" && $conqueror2[0] !== "TF" && 
                $conqueror2[0] !== "string" && $conqueror2[0] !== "bool" && $conqueror2[0] !== "int") {
                ThrowErr($linecounter);
            }
            else if ($conqueror2[0] == "GF" || $conqueror2[0] == "LF" || $conqueror2[0] == "TF") {
                if(CheckIfVarExists($pole[$poradie]) == false) {
                    ThrowErr($linecounter);
                }
            }

            /**************************************************************/
            if ($conqueror2[0] == "string")
            {
                $poradie++;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }
            }
            /**************************************************************/

        }
        break;
    /*********************************** EQ ****************************/
    case "EQ":
    	if(count($pole)<4) {
            ThrowErr($linecounter);
        }
        else {
            if(CheckIfVarExists($pole[1]) == false) {
                ThrowErr($linecounter);
            }
            // < symb1 >
            $conqueror1 = explode("@", $pole[2]);
            if ($conqueror1[0] !== "GF" && $conqueror1[0] !== "LF" && $conqueror1[0] !== "TF" && 
                $conqueror1[0] !== "string" && $conqueror1[0] !== "bool" && $conqueror1[0] !== "int") {
                ThrowErr($linecounter);
            }
            else if ($conqueror1[0] == "GF" || $conqueror1[0] == "LF" || $conqueror1[0] == "TF") {
                if(CheckIfVarExists($pole[2]) == false) {
                    ThrowErr($linecounter);
                }
            }
            /**************************************************************/
            if ($conqueror1[0] == "string" && count($pole) > 4)
            {
                if(strpos($pole[2], "@") === true)
                    $poradie = 3;
                else 
                {      
                    $poradie = 3;
                    while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                    {
                        if(strpos($pole[$poradie], "@") !== false) break;
                        $arrayno = str_split($pole[$poradie]);
                        foreach ($arrayno as $char) {
                            if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                            {
                               ThrowErr($linecounter); 
                            }
                        }
                        $poradie++;
                    }
                }   
            }
            else if($conqueror1[0] !== "string" && count($pole) > 4) ThrowErr($linecounter);
            /**************************************************************/
            // < symb2 >
            $conqueror2 = explode("@", $pole[$poradie]);
            if ($conqueror2[0] !== "GF" && $conqueror2[0] !== "LF" && $conqueror2[0] !== "TF" && 
                $conqueror2[0] !== "string" && $conqueror2[0] !== "bool" && $conqueror2[0] !== "int") {
                ThrowErr($linecounter);
            }
            else if ($conqueror2[0] == "GF" || $conqueror2[0] == "LF" || $conqueror2[0] == "TF") {
                if(CheckIfVarExists($pole[3]) == false) {
                    ThrowErr($linecounter);
                }
            }

            /**************************************************************/
            if ($conqueror2[0] == "string")
            {
                $poradie++;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }
            }
            /**************************************************************/

        }
        break;
    /*********************************** AND ****************************/
    case "AND":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "bool") {
				ThrowErr($linecounter);
			}
			// < symb2 >
			$conqueror = explode("@", $pole[3]);
			if ($conqueror[0] !== "bool") {
				ThrowErr($linecounter);
			}
    	}
        break;
    /*********************************** OR ****************************/
    case "OR":
    	if(count($pole)!=4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "bool") {
				ThrowErr($linecounter);
			}
			// < symb2 >
			$conqueror = explode("@", $pole[3]);
			if ($conqueror[0] !== "bool") {
				ThrowErr($linecounter);
			}
    	}
        break;
    /*********************************** NOT ****************************/
    case "NOT":
    	if(count($pole)!=3) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "bool") {
				ThrowErr($linecounter);
			}
    	}
        break;
    /*********************************** INT2CHAR ****************************/
    case "INT2CHAR":
    	if(count($pole)!=3) {
    		echo "problem1\n";
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		else if(!is_numeric($pole[2])) {
    			ThrowErr($linecounter);
    		}
    	}
        break;
    /*********************************** STRI2INT ****************************/
    case "STRI2INT":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    		// < symb2 >
    		else if(!is_numeric($pole[3])) {
    			ThrowErr($linecounter);
    		}
    	}
        break;
    /********************************/
    /*********************************** READ ****************************/
    case "READ":
    	if(count($pole)!=3) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		if ($pole[1] !== "int" && $pole[1] !== "string" && $pole[1] !== "bool") {
				ThrowErr($linecounter);
			}
    	}
        break;
    /*********************************** WRITE ****************************/
    case "WRITE":
    	if(count($pole)<2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		// < symb1 >
    		$conqueror = explode("@", $pole[1]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[1]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
            if($conqueror[0] == "string" && count($pole) > 2) 
            {
                $poradie = 3;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }
            }
    	}
        break;
    /********************************/
    /*********************************** CONCAT ****************************/
    case "CONCAT":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
	    	$conqueror = explode("@", $pole[2]);

	    	if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	    		$typjedna = GiveMeType($pole[2]);
	    	}
	    	else if($conqueror[0] == "string") $typjedna = "string";
	    	else if($conqueror[0] == "bool") $typjedna = "bool";
	   		else if($conqueror[0] == "int") $typjedna = "int";
	   		else ThrowErr($linecounter);

            $poradie = 3;
            /**************************************************************/
            if ($conqueror[0] == "string" && count($pole) > 4)
            {
                if(strpos($pole[2], "@") === true)
                    $poradie = 3;
                else 
                {      
                    $poradie = 3;
                    while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                    {
                        if(strpos($pole[$poradie], "@") !== false) break;
                        $arrayno = str_split($pole[$poradie]);
                        foreach ($arrayno as $char) {
                            if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                            {
                               ThrowErr($linecounter); 
                            }
                        }
                        $poradie++;
                    }
                }   
            }
            /**************************************************************/
	    	// < symb2 >
	    	$conqueror = explode("@", $pole[$poradie]);
	    	if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
	   			$typdva = GiveMeType($pole[$poradie]);
	   		}
	    	else if($conqueror[0] == "string") $typdva = "string";
	    	else if($conqueror[0] == "bool") $typdva = "bool";
	   		else if($conqueror[0] == "int") $typdva = "int";
	   		else ThrowErr($linecounter);
            /**************************************************************/
            if ($conqueror[0] == "string" && count($pole) > 4)
            {
                $poradie++;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }  
            }
            /**************************************************************/

	    	if ( ($typjedna != "string") || ($typdva != "string")  ) {
	   			printf( "ERROR -  Semantics error in line: " );
				echo $linecounter;
				printf( " \nWrong types!\n" );
				echo "Program returned 21\n";
				exit(21);
	    	}

    	}
        break;
    /*********************************** STRLEN ****************************/
    case "STRLEN":
    	if(count($pole)<3) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}

            /**************************************************************/
            if ($conqueror[0] == "string" && count($pole) > 3)
            {
                $poradie = 3;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }  
            }
            /**************************************************************/
    	}
        break;
    /*********************************** GETCHAR ****************************/
    case "GETCHAR":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		// < symb2 >
    		else if(!is_numeric($pole[3])) {
    			ThrowErr($linecounter);
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /*********************************** SETCHAR ****************************/
    case "SETCHAR":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		else if(!is_numeric($pole[2])) {
    			ThrowErr($linecounter);
    		}
    		// < symb2 >
    		$conqueror = explode("@", $pole[3]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /*********************************** TYPE ****************************/
    case "TYPE":
    	if(count($pole)<3) {
        	ThrowErr($linecounter);
    	}
    	else {
    		if(CheckIfVarExists($pole[1]) == false) {
    			ThrowErr($linecounter);
    		}
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /********************************/
    /*********************************** LABEL ****************************/
    case "LABEL":
    	if(count($pole)!=2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		$pravda = false;
    		$velkostp = count($navestiArray);
    		for ($i=0; $i < $velkostp; $i++) { 
    			if($navestiArray[$i] == $pole[1]) {
    				$pravda = true;
    			}
    		}
    		if ($pravda == true) {
    				printf( "ERROR -  Try for redefinition: " );
					echo $linecounter;
					printf( " \n" );
					echo "Program returned 52\n";
					exit(52);
    		}

    		$velkostp = count($navestiArray);
    		$navestiArray[$velkostp] = $pole[1];
    	}
        break;
    /*********************************** JUMP ****************************/
    case "JUMP":
    	if(count($pole)!=2) {
        	ThrowErr($linecounter);
    	}
    	else {
    		$pravda = false;
    		$velkostp = count($navestiArray);
    		for ($i=0; $i < $velkostp; $i++) { 
    			if($navestiArray[$i] == $pole[1]) {
    				$pravda = true;
    			}
    		}
    		if ($pravda == false) {
    			global $PoleNeinicNavesti;
    			$PoleNeinicNavesti[count($PoleNeinicNavesti)] = $pole[1];
    		}

    	}
        break;
    /*********************************** JUMPIFEQ ****************************/
    case "JUMPIFEQ":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		$pravda = false;
    		$velkostp = count($navestiArray);
    		for ($i=0; $i < $velkostp; $i++) { 
    			if($navestiArray[$i] == $pole[1]) {
    				$pravda = true;
    			}
    		}
    		if ($pravda == false) {
    			global $PoleNeinicNavesti;
    			$PoleNeinicNavesti[count($PoleNeinicNavesti)] = $pole[1];
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
			// < symb2 >
			$conqueror = explode("@", $pole[3]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /*********************************** JUMPIFNEQ ****************************/
    case "JUMPIFNEQ":
    	if(count($pole)<4) {
        	ThrowErr($linecounter);
    	}
    	else {
    		$pravda = false;
    		$velkostp = count($navestiArray);
    		for ($i=0; $i < $velkostp; $i++) { 
    			if($navestiArray[$i] == $pole[1]) {
    				$pravda = true;
    			}
    		}
    		if ($pravda == false) {
    			global $PoleNeinicNavesti;
    			$PoleNeinicNavesti[count($PoleNeinicNavesti)] = $pole[1];
    		}
    		// < symb1 >
    		$conqueror = explode("@", $pole[2]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[2]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
			// < symb2 >
			$conqueror = explode("@", $pole[3]);
			if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
				$conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
				ThrowErr($linecounter);
			}
			else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
				if(CheckIfVarExists($pole[3]) == false) {
    				ThrowErr($linecounter);
    			}
    		}
    	}
        break;
    /********************************/
    /*********************************** DPRINT ****************************/
    case "DPRINT":
    	if(count($pole)<2) {
        	ThrowErr($linecounter);
    	}
        else
        {
            $conqueror = explode("@", $pole[1]);
            if ($conqueror[0] !== "GF" && $conqueror[0] !== "LF" && $conqueror[0] !== "TF" && 
                $conqueror[0] !== "string" && $conqueror[0] !== "bool" && $conqueror[0] !== "int") {
                ThrowErr($linecounter);
            }
            else if ($conqueror[0] == "GF" || $conqueror[0] == "LF" || $conqueror[0] == "TF") {
                if(CheckIfVarExists($pole[1]) == false) {
                    //echo "fakjuuuuuuuuuuuu: ";
                    //echo $pole[1];
                    //echo "\n";
                    ThrowErr($linecounter);
                }
            }
            if($conqueror[0] == "string" && count($pole) > 2) 
            {
                $poradie = 3;
                while($poradie < count($pole)) // zacina od tretieho konci pri poslednom
                {
                    $arrayno = str_split($pole[$poradie]);
                    foreach ($arrayno as $char) {
                        if( $char !==  '\\' && !ctype_alnum($char) && !ctype_space($char))
                        {
                           ThrowErr($linecounter); 
                        }
                    }
                    $poradie++;
                }
            }
        }
        break;
    /*********************************** BREAK ****************************/
    case "BREAK":
    	if(count($pole)!=1) {
        	ThrowErr($linecounter);
    	}
        break;

	}

}
/*********************************************************************/
/*********************************************************************/
function MakeLexiCheck($writer) {

	global $GFarray;
	global $LFarray;
	global $TFarray;

	$poc = 1;
	$linecounter=1;
	$order=1;
	while ( $line = fgets(STDIN) ) {
		$pole = array();
        /*
    		echo "********************  Line: ";
    		echo $linecounter;
    		echo "  ********************\n";
        */
		$strings = explode(" ", $line);
		//*****************************************************//
		// . IPPcode18 in first line
		if ($linecounter == 1) {
			if(count($strings)>=2 && !strcmp($strings[0], ".") 
				&& !strcmp($strings[1], "IPPcode18"))
			{
                if(count($strings)>2 && strcmp($strings[2][0], "#"))
                {
                    printf( "ERROR - Lexical error in line: 1!\n" );
                    echo "Program returned 21\n";
                    exit(21);
                }
                $linecounter++;
                continue;
			}
			else 
			{
				printf( "ERROR - Lexical error in line: 1!\n" );
				echo "Program returned 21\n";
				exit(21);
			}
		}
		//****************************************************//
		// reading strings and sending to fing keyword
		$prepinac = false;
        for($i=0; $i<count($strings); $i++) {

        	if ($i == 0) $prepinac = false;
	        // skip line if finds '#' (comments) or '\n' (end of line)
	        if (!strcmp($strings[$i], "\n") || !strcmp($strings[$i], "#") || strpos($strings[$i][0], "#") !== false) {
	        	break;
	        }

	        // delete '\n' from the end of final word in line
	        $strings[$i] = str_replace("\n", "", $strings[$i]);	        
			if (strpos($strings[$i], "\n") !== false) {
				$strings[$i] = substr($strings[$i], 0, -1);
			}
            /*
    	        echo $poc;
    	        echo " - ";
    	        echo $strings[$i];
    	        echo "\n";
            */
	        $poc++;

	        // ak sa naslo string@ ... tak vsetko za nim musi byt len cislo, pismeno alebo \
	        if ($prepinac == true) {

	        	$chars = substr($strings[$i], 0, strlen($strings[$i]));
	        	for($j=0; $j <= strlen($chars)-1; $j++) {

		        	if ( strpos($chars[$j], '\\') !== false || ctype_alnum($chars[$j]) || 
		        		strpos($chars[$j], '\n') !== false)
		        	{	 
		        		continue;
					}
					else {
						printf( "ERROR - Lexical error - in line: " );
						echo $linecounter;
						printf( " \n" );
						echo "Program returned 21\n";
						exit(21);
					}
				}
	        }

	        if( true == KeywordCheck($strings[$i], $i, $linecounter)) {
	        	$prepinac = true;
	        }
	        $pole[$i] = $strings[$i];


	    }

	    MakeLineCheck($pole, $linecounter);
	    $linecounter++;
	    //****************************************************//
        if(strcmp($strings[0], "\n"))
	    if((strcmp($strings[0], "#") !==0 || strcmp($strings[0][0], "#")!==0) !== false) {
		    $pole[0] = strtoupper($pole[0]);
            $writer->startElement('instruction');

                $writer->writeAttribute('order', $order); 
			    $order++;
                $writer->writeAttribute('opcode', $pole[0]); 


    			if ( (count($pole) == 2) ) {

                    $writer->startElement('arg1');
    			    //fwrite($myXML, "        <arg1>\n");
    			    	GiveMeTypeXML( $pole[1], $writer );
    			    //fwrite($myXML, "        </arg1>\n");
                    $writer->endElement();
    			}
    			else if ( count($pole) == 3 ) {
                    $writer->startElement('arg1');
    				//fwrite($myXML, "        <arg1>\n");
    					GiveMeTypeXML( $pole[1], $writer );
                    $writer->endElement();
    			    //fwrite($myXML, "        </arg1>\n");

                    $writer->startElement('arg2');
					//fwrite($myXML, "        <arg2>\n");
						GiveMeTypeXML( $pole[2], $writer );
                    $writer->endElement();
				    //fwrite($myXML, "        </arg2>\n");

    			}
    			else if (count($pole) >= 4  ) {
                    $writer->startElement('arg1');
    				//fwrite($myXML, "        <arg1>\n");
    					GiveMeTypeXML( $pole[1], $writer );
                    $writer->endElement();
    		    	//fwrite($myXML, "        </arg1>\n");

                    $writer->startElement('arg2');
					//fwrite($myXML, "        <arg2>\n");
						GiveMeTypeXML( $pole[2], $writer );
                    $writer->endElement();
				    //fwrite($myXML, "        </arg2>\n");

                    $writer->startElement('arg3');
				    //fwrite($myXML, "        <arg3>\n");
				    	GiveMeTypeXML( $pole[3], $writer );
                    $writer->endElement();
				    //fwrite($myXML, "        </arg3>\n");

    			}
            $writer->endElement();
			//fwrite($myXML, "      </opcode>\n");
			//fwrite($myXML, "      </order>\n");
			//fwrite($myXML, "    </instruction>\n");
		}
	    //****************************************************//
    }

    global $PoleNeinicNavesti;
    global $navestiArray;
    $pravdaO = count($PoleNeinicNavesti);
    $velkostp = count($navestiArray);
    $velkostp2 = count($PoleNeinicNavesti);

    for ($i=0; $i < $velkostp; $i++) { 

    	for ($j=0; $j < $velkostp2; $j++) { 

    	    if($navestiArray[$i] == $PoleNeinicNavesti[$j]) {
    	   		$pravdaO--;
    	    }
    	}
    }
    if ($pravdaO!==0) {
    	printf( "ERROR - Undefinied label - in line: " );
    	echo $linecounter;
    	printf( " \n" );
    	echo "Program returned 21\n";
    	exit(21);
    }
		
	
}


?>
