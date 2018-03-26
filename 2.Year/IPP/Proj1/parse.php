<?php
/****************************************/
/*			IPP - projekt 1.			*/
/* autor:	Jozef Drab 					*/
/* login: 	xdrabj00					*/
/* datum:	28.2.2018					*/
/* 										*/
/****************************************/
//echo "*****************************************************************************\n";
include 'lex.php';

	foreach ($argv as $arg) {
		$divider = explode("=", $arg);
		if(count($divider)==2) {
			$_Get[$divider[0]] = $divider[1];
		}
		else {
			$_Get[$divider[0]] = 0;
		}
	}

	if(isset($_Get['--help']) || isset($_Get['-help'])) {
		print("IPP Project 1.\n");
		print("Autor: xdrabj00\n");
		print("Available parameters:\n");
		print("	--help 		Parameter to help\n");
		print("	--source=file 	Parameter to input file\n");
	}
/*
	else if (isset($_Get['--source']) || isset($_Get['-source'])) {
		$pathFile = $_Get['--source'];
		$fFile = fopen($pathFile, "r");

		// vstupny subor
		if ($fFile == NULL) {
			printf( "ERROR - Entry file!\n" );
			echo "Program returned 11\n";
			exit(11);
		}
*/
		/*****************************************************************/
		$writer = new XMLWriter();  
		$writer->openURI('output.xml');  
		$writer->startDocument('1.0','UTF-8');   
		$writer->setIndent(8);  

		$writer->startElement('program');
			$writer->writeAttribute('language', 'IPPcode18');
		
				MakeLexiCheck($writer);

		$writer->endElement();
		$writer->endElement(); 

		$writer->endDocument();   
		$writer->flush();

//		$xmlFile = fopen("OutputXML", "r");
/*		while (($line = fgets($xmlFile)) !== false)
		{
			echo $line;
			echo "\n";
	}*/	

		$xmlFile = fopen("output.xml", "r");
		if ($xmlFile == NULL) {
			echo "zleeeee\n";
		}
		while (($line = fgets($xmlFile)) !== false) 
		{
		   echo $line;
		   echo "\n";
		}

		fclose($xmlFile);


	//}
	/*else  {
		printf( "ERROR - Unknown argument! Use '--help' to work.\n" );
		echo "Program returned 10\n";
		exit(10);
	}*/



?>
