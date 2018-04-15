#!/usr/bin/python
# # # # # # # # # # # # # # # # # #
# 		IPP - projekt 2							#
# Interpret pre jazyk IPP18 			#
# Autor: Jozef Drab < xdrabj00> 	#
# Datum: 15.04.2018								#
# # # # # # # # # # # # # # # # # #

from case_instruct import interpreting
import sys

was_instruction = False
was_arg1 = False
was_arg2 = False
was_arg3 = False
arg1_type = ""
arg2_type = ""
arg3_type = ""
arg1_name = ""
arg2_name = ""
arg3_name = ""
instruct_name = ""
counter_line = 0
counter_instruct = 0

instruction = ""

class Instruct(object):
		name = ""
		argument1 = ""
		typ1 = ""
		argument2 = ""
		typ2 = ""
		argument3 = ""
		typ3 = ""

# The class "constructor" - It's actually an initializer 
		def __init__(self, name, argument1, typ1, argument2, typ2, argument3, typ3):
				self.name = name
				self.argument1 = argument1
				self.typ1 = typ1
				self.argument2 = argument2
				self.typ2 = typ2
				self.argument3 = argument3
				self.typ3 = typ3

def make_instruct_obj(name, argument1, typ1, argument2, typ2, argument3, typ3):
		global instruction
		instruction = Instruct(name, argument1, typ1, argument2, typ2, argument3, typ3)
		return instruction

#############################################################################

def find_between( s, first, last ):
	try:
		start = s.index( first ) + len( first )
		end = s.index( last, start )
		return s[start:end]
	except ValueError:
		return ""


def AnalyzeLine( line, counter ):

	#"This prints a passed string into this function"
	global was_instruction
	global arg1_type
	global arg2_type
	global arg3_type
	global arg1_name
	global arg2_name
	global arg3_name
	global instruct_name
	global instruction # object name
	global counter_line
	global counter_instruct


	#nahrada="<ahojky volam sa ukulele>"
	if( counter == 1 and (line != "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" )):
		print(
			"ERROR: Illegal format of input file!"
		)
		exit(31) # chybný XML formát ve vstupním souboru
	if( counter == 2 and (line != "<program language=\"IPPcode18\">" )):
		print(
			"ERROR: Illegal format of input file!"
		)
		exit(31) # chybný XML formát ve vstupním souboru

	if( counter != 1 and counter != 2 ):
		#line = line.translate(str.maketrans({"<":  r"", ">":  r""}))
		
		# check input file if ARG1 is correctly written
		if "</arg1>" in line:
			if "<arg1" in line:
				splitted = line.split(" ")[0]			#arg1
				if( splitted == "<arg1" ): 
					arg1_type = find_between( line.split(" ")[1], "type=\"", "\">" )
					arg1_type = arg1_type.lower()
					if( arg1_type != "int" and arg1_type != "bool" and arg1_type != "string" 
							and arg1_type != "label" and arg1_type != "type" and arg1_type != "var" ):
						print("ERROR: Illegal format of input file ( Unknown type )!")
						exit(32) # chyba lexikální nebo syntaktické analýzy
					arg1_name = find_between( line, "\">", "</arg1>" )
			else: 
				print("ERROR: Illegal format of input file ( arg1 )!")
				exit(31) # chybný XML formát ve vstupním souboru

		# check input file if ARG2 is correctly written
		if "</arg2>" in line:
			if "<arg2" in line:
				splitted = line.split(" ")[0]			#arg2
				if( splitted == "<arg2" ): 
					arg2_type = find_between( line.split(" ")[1], "type=\"", "\"" )
					arg2_type = arg2_type.lower()
					if( arg2_type != "int" and arg2_type != "bool" and arg2_type != "string" 
							and arg2_type != "label" and arg2_type != "type" and arg2_type != "var" ):
						print("ERROR: Illegal format of input file ( Unknown type )!")
						exit(32) # chyba lexikální nebo syntaktické analýzy
					arg2_name = find_between( line, "\">", "</arg2>" )
			else: 
				print("ERROR: Illegal format of input file ( arg2 )!")
				exit(31) # chybný XML formát ve vstupním souboru

		# check input file if ARG2 is correctly written
		if "</arg3>" in line:
			if "<arg3" in line:
				splitted = line.split(" ")[0]			#arg2
				if( splitted == "<arg3" ): 
					arg3_type = find_between( line.split(" ")[1], "type=\"", "\"" )
					arg3_type = arg3_type.lower()
					if( arg3_type != "int" and arg3_type != "bool" and arg3_type != "string" 
							and arg3_type != "label" and arg3_type != "type" and arg3_type != "var" ):
						print("ERROR: Illegal format of input file ( Unknown type )!")
						exit(32) # chyba lexikální nebo syntaktické analýzy
					arg3_name = find_between( line, "\">", "</arg3>" )
			else: 
				print("ERROR: Illegal format of input file ( arg3 )!")
				exit(31) # chybný XML formát ve vstupním souboru

		# if new instruction, check input format and annul args
		if "</instruction>" in line:
			make_instruct_obj(instruct_name, arg1_name, arg1_type, arg2_name,  arg2_type, arg3_name, arg3_type)
			if(instruct_name != "BREAK"):
				if(interpreting( instruction ) == 999):
					was_instruction = False
					arg1_name = ""
					arg2_name = ""
					arg3_name = ""
					return 999
			else:
				if(instruction.argument1 == "" and instruction.argument2 == "" and instruction.argument3 == ""):
					print("line: " + str(counter_line), file=sys.stdout)
					print("Count of realized instructions: " + str(counter_instruct), file=sys.stdout)
        #exit(54)
				else:
					print("ERROR: Too much/less args in 'BREAK' instruction!")
					exit(32)

			was_instruction = False
			arg1_name = ""
			arg2_name = ""
			arg3_name = ""

		elif "<instruction" in line:
			if ( was_instruction == True): 
				print("ERROR: Illegal format of input file!")	
				exit(31) # chybný XML formát ve vstupním souboru
			was_instruction = True
			counter_instruct = find_between( line, "order=\"", "\" opcode" )
			splitted = line.split(" ")[2]			#instruction

			instruct_name = find_between( splitted, "opcode=\"", "\"" )
			instruct_name = instruct_name.upper()

		elif "</program>" in line:
			exit(0)

	counter_line +=1
	return 


#************************ main program *******************#
#print("*********************************************")
if(len(sys.argv) != 2):
	print(
		"ERROR: Illegal arguments at the input!"
		#file=sys.stderr
		)
	exit(1)
for argum in sys.argv[-1:]:
	if(len(sys.argv) == 2 and (sys.argv[1] == "--help")):
		print(
			"\nIPP - Projekt 2. (05.04.2018)" + 
			"\nAuthor: Jozef Drab < xdrabj00 >" +
			"\nUse following arguments:" +
			'\n\t{0:20} {1:1}\n'.format("--help","Input help") +
			'\t{0:20} {1:1}\n'.format("--source=file","Input file")
			)
		print("*********************************************")
		exit(0)
	else:
		try:
			Conqueror = argum.split("=")
			if (len(Conqueror) > 2):
				print(
					"Illegal arguments at the input!"
					#file=sys.stderr
					)
				exit(1)
			if (Conqueror[0] == "--source"):
				try:
					if (len(Conqueror) != 2 or not Conqueror[1]):
						print(
							"Error: Illegal input arguments!"
							#file=sys.stderr
							)
						exit(1)
					opakuj_sa = False
					first = True
					while (first == True or opakuj_sa == True):
						#print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
						first = False
						opakuj_sa == False
						with open(Conqueror[1]) as file:  
							line = file.readline()
							counter= 1
							while line:
								oneline=line.strip()
								if (AnalyzeLine(oneline, counter) == 999):
									opakuj_sa = True
									break
								#print(oneline)
								counter+=1
								line = file.readline()
							#if(opakuj_sa == True):
							#	break

				except IOError:
					print(
						"Error in input file!"
						#file=sys.stderr
						)
					exit(2)

		except Exception as err:
			print(
				"Error: " + repr(err)
				)
			exit(1)
#print("*********************************************")

