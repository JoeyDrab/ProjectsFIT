<?php
/****************************************/
/*			IPP - projekt 1.			*/
/* autor:	Jozef Drab 					*/
/* login: 	xdrabj00					*/
/* datum:	28.2.2018					*/
/* 										*/
/****************************************/

include_once 'lex.php';

/* Funkcia prehlada Globalny, lokalny alebo docasny ramec, ci premenna existuje */
function CheckIfVarExists( $variable ) {

	global $GFarray;
	global $LFarray;
	global $TFarray;
/*
	$GFarray = array();
	$LFarray = array();
	$TFarray = array();

	$GLOBALS['GFarray'];
	$GLOBALS['LFarray'];
	$GLOBALS['TFarray'];
	/*
	global $GFarray;
	global $LFarray;
	global $TFarray;
	*/
	

	$conqueror = explode("@", $variable);
	switch ($conqueror[0]) {
		case "GF":
			for ($i = 0; $i < count($GFarray); $i++) {
				if ($GFarray[$i][0] == $conqueror[1]) {
					return true;
				}
			}
			break;
		
		case "LF":
			for ($i = 0; $i < count($LFarray); $i++) {
				if ($LFarray[$i][0] == $conqueror[1]) {
					return true;
				}
			}
			break;

		case "TF":
			for ($i = 0; $i < count($TFarray); $i++) {
				if ($TFarray[$i][0] == $conqueror[1]) {
					return true;
				}
			}
			break;
	}
}

function CreateVariable($variable, $line) {

	global $GFarray;
	global $LFarray;
	global $TFarray;

	$conqueror = explode("@", $variable);
	switch ($conqueror[0]) {
		case "GF":
			if (count($GFarray) != 0) {
				$sizeofarray = count($GFarray);

				$GFarray[$sizeofarray][0] = $conqueror[1];
			}
			else  {
				$GFarray[0][0] = $conqueror[1];
			}

			break;
			/**************************************************/
			/*
			$sizeofarray = count($GFarray);
			// 1
			//$sizeofarray++;
			// 2
			$GFarray[$sizeofarray] = "chuju";
			// 2
			$sizeofarray = count($GFarray);
			//$sizeofarray++;
			$GFarray[$sizeofarray] = "makaj";
			// 3
			*/
			/*************************************************/
		case "LF":
			if (count($LFarray) != 0) {
				$sizeofarray = count($LFarray);

				$LFarray[$sizeofarray][0] = $conqueror[1];
			}
			else  {
				$LFarray[0][0] = $conqueror[1];
			}

			break;

		case "TF":
			if (count($GFarray) != 0) {
				$sizeofarray = count($TFarray);

				$TFarray[$sizeofarray][0] = $conqueror[1];
			}
			else  {
				$TFarray[0][0] = $conqueror[1];
			}

			break;
		default:
			printf( "ERROR -  in line: " );
			echo $line;
			printf( " \n" );
			echo "Program returned 21\n";
			exit(21);
	}
}

function WriteToVariable( $variable, $write ) {

	global $GFarray;
	global $LFarray;
	global $TFarray;

	// 'string@ahoj' alebo 'GF@var'
	$writer = explode("@", $write);

	// 
	if ($writer[0] == "GF" || $writer[0] == "LF" || $writer[0] == "TF") {
		switch ($writer[0]) {
			case "GF":
				for ($i = 0; $i < count($GFarray); $i++) {
					if ($GFarray[$i][0] == $writer[1]) {
						$writer[1] = $GFarray[$i][1];
						$writer[0] = $GFarray[$i][2];
					}
				}
				break;
			
			case "LF":
				for ($i = 0; $i < count($GFarray); $i++) {
					if ($LFarray[$i][0] == $writer[1]) {
						$writer[1] = $LFarray[$i][1];
						$writer[0] = $LFarray[$i][2];
					}
				}
				break;

			case "TF":
				for ($i = 0; $i < count($GFarray); $i++) {
					if ($TFarray[$i][0] == $writer[1]) {
						$writer[1] = $TFarray[$i][1];
						$writer[0] = $TFarray[$i][2];
					}
				}
				break;
		}
	}
	/*
	echo "++++++++++++++++++++++++++++\n";
	echo $writer[0];
	echo "\n------------\n";
	echo $writer[1];
	echo "\n++++++++++++++++++++++++++++\n";
	*/
	if ($writer[0] == "int" || $writer[0] == "bool" || $writer[0] == "string")
	{
		$writer[0] = $writer[0];
	}
	else {
		printf( "ERROR -  Incompatibile data type: '" );
		echo $writer[0];
		printf( " '\n" );
		echo "Program returned 21\n";
		exit(21);
	}

	$conqueror = explode("@", $variable);
	switch ($conqueror[0]) {
		case "GF":
			for ($i = 0; $i < count($GFarray); $i++) {
				if ($GFarray[$i][0] == $conqueror[1]) {
					$GFarray[$i][1] = $writer[1]; // ahoj 	[data]
					$GFarray[$i][2] = $writer[0]; // string [typ]
					/*
					echo "#####################################\n nazov: ";
					echo $GFarray[$i][0];
					echo "\n data: ";
					echo $GFarray[$i][1];
					echo "\n typ: ";
					echo $GFarray[$i][2];
					echo "\n#####################################\n";
					*/
				}
			}
			break;
		
		case "LF":
			for ($i = 0; $i < count($LFarray); $i++) {
				if ($LFarray[$i][0] == $conqueror[1]) {
					$LFarray[$i][1] = $writer[1]; // ahoj 	[data]
					$LFarray[$i][2] = $writer[0]; // string [typ]
				}
			}
			break;

		case "TF":
			for ($i = 0; $i < count($TFarray); $i++) {
				if ($TFarray[$i][0] == $conqueror[1]) {
					$TFarray[$i][1] = $writer[1]; // ahoj 	[data]
					$TFarray[$i][2] = $writer[0]; // string [typ]
				}
			}
			break;
	}
}

function GiveMeType( $variable ) {

	global $GFarray;
	global $LFarray;
	global $TFarray;
	
	$conqueror = explode("@", $variable);
	switch ($conqueror[0]) {
		case "GF":
			for ($i = 0; $i < count($GFarray); $i++) {

				if ($GFarray[$i][0] == $conqueror[1]) {
					return $GFarray[$i][2];
				}
			}
			break;
		
		case "LF":
			for ($i = 0; $i < count($LFarray); $i++) {
				if ($LFarray[$i][0] == $conqueror[1]) {
					return $LFarray[$i][2];
				}
			}
			break;

		case "TF":
			for ($i = 0; $i < count($TFarray); $i++) {
				if ($TFarray[$i][0] == $conqueror[1]) {
					return $TFarray[$i][2];
				}
			}
			break;
	}
}

function GiveMeTypeXML( $variable , $writer) {

	if($writer == NULL) 
	{
		echo "chybaaaaaaaaaaaaaaaaaaaaaaaaa\n";
		exit(55);
	}

	global $GFarray;
	global $LFarray;
	global $TFarray;
	global $navestiArray;

    $velkostp = count($navestiArray);
    for ($i=0; $i < $velkostp; $i++) { 
    	if($navestiArray[$i] == $variable) {
    		$writer->writeAttribute('type', 'label');
    		//fwrite($myXML, "          <type=\"label\">\n");
    			$writer->writeElement('text', $variable); 
    			//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $variable);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
    	}
    }
	
	$conqueror = explode("@", $variable);
	switch ($conqueror[0]) {
		case "GF":
			$writer->writeAttribute('type', 'var');
			//fwrite($myXML, "          <type=\"var\">\n");
				$writer->writeElement('text', $variable);
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $variable);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;
		
		case "LF":
			$writer->writeAttribute('type', 'var');
			//fwrite($myXML, "          <type=\"var\">\n");
				$writer->writeElement('text', $variable);
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $variable);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;

		case "TF":
			$writer->writeAttribute('type', 'var');
			//fwrite($myXML, "          <type=\"var\">\n");
				$writer->writeElement('text', $variable);
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $variable);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;

		case "int":
			$writer->writeAttribute('type', 'int');
			//fwrite($myXML, "          <type=\"int\">\n");
				$writer->writeElement('text', $conqueror[1]); 
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $conqueror[1]);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;

		case "bool":
			$writer->writeAttribute('type', 'bool');
			//fwrite($myXML, "          <type=\"bool\">\n");
				$writer->writeElement('text', $conqueror[1]); 
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $conqueror[1]);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;

		case "string":
			$writer->writeAttribute('type', 'string');
			//fwrite($myXML, "          <type=\"string\">\n");
				$writer->writeElement('text', $conqueror[1]);
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $conqueror[1]);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
			break;

		default:
			$writer->writeAttribute('type', 'type');
			//fwrite($myXML, "          <type=\"type\">\n");
				$writer->writeElement('text', $variable); 
				//fwrite($myXML, "            <text>");
    			//fwrite($myXML, $variable);
    			//fwrite($myXML, "</text>\n");
    		//fwrite($myXML, "          </type>\n");
	}
}

?>
