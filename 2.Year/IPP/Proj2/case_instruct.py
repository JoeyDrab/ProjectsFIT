#!/usr/bin/python
# # # # # # # # # # # # # # # # # #
#     IPP - projekt 2             #
# Interpret pre jazyk IPP18       #
# Autor: Jozef Drab < xdrabj00>   #
# Datum: 15.04.2018               #
# # # # # # # # # # # # # # # # # #

import copy
import sys
'''
class sstack(object):
    glob = []
    local = []
    temporary = []

    # The class "constructor" - It's actually an initializer 
    def __init__(self, glob, local, temporary):
        self.glob = glob
        self.local = local
        self.temporary = temporary

def make_instruct_obj(glob, local, temporary):
    global stck
    stck = sstack(glob, local, temporary)
    return stck


def add_to_glob(variable, value):
    stck.glob.append(variable, value)
'''

class Stack:
    def __init__(self):
        self.typ=[]
        self.value=[]

    def isEmpty(self):
        return self.typ==[]
        return self.value==[]

    def push(self, typ, value):
        self.typ.append(typ)
        self.value.append(value)
        #print(self.items)

    def pop_typ(self):
        return self.typ.pop()
    def pop_value(self):
        return self.value.pop()


s = Stack()

#GFlist =[[][]]
glob_label = ""
GFlist_name = []
GFlist_type = []
GFlist_value = []
labels_list = []

LFlist_name = []
LFlist_value = []
LFlist_type = []

TFlist_name = []
TFlist_value = []
TFlist_value = []
ignore_while = False

############################################
def check_if_exists(variable):

  if( variable.split("@")[0] == "GF"):
    if( variable in GFlist_name):
      return 1
  elif( variable.split("@")[0] == "LF"):
    if( variable in LFlist_name):
      return 1
  elif( variable.split("@")[0] == "TF"):
    if( variable in TFlist_name):
      return 1
############################################
def return_index(variable):

  if( variable.split("@")[0] == "GF"):
    if( variable in GFlist_name):
      return GFlist_name.index(variable)
  elif( variable.split("@")[0] == "LF"):
    if( variable in LFlist_name):
      return LFlist_name.index(variable)
  elif( variable.split("@")[0] == "TF"):
    if( variable in TFlist_name):
      return TFlist_name.index(variable)
############################################
def give_me_value(variable):
  index = return_index(variable)
  if( variable.split("@")[0] == "GF"):
    if( variable in GFlist_name):
      return GFlist_value[index]

  elif( variable.split("@")[0] == "LF"):
    if( variable in LFlist_name):
      return GFlist_value[index]

  elif( variable.split("@")[0] == "TF"):
    if( variable in TFlist_name):
      return GFlist_value[index]
############################################
def give_me_type(variable):
  index = return_index(variable)
  if( variable.split("@")[0] == "GF"):
    if( variable in GFlist_name):
      return GFlist_type[index]

  elif( variable.split("@")[0] == "LF"):
    if( variable in LFlist_name):
      return GFlist_type[index]

  elif( variable.split("@")[0] == "TF"):
    if( variable in TFlist_name):
      return GFlist_type[index]
############################################
def write_value_to_var(variable, value, typ):
  index = return_index(variable)
  if( variable.split("@")[0] == "GF"):
    if( variable in GFlist_name):
      GFlist_value[index] = value
      GFlist_type[index] = typ
  elif( variable.split("@")[0] == "LF"):
    if( variable in LFlist_name):
      LFlist_value[index] = value
      LFlist_type[index] = typ
  elif( variable.split("@")[0] == "TF"):
    if( variable in TFlist_name):
      LFlist_value[index] = value
      LFlist_type[index] = typ
############################################
def create_variable(variable):

  if( variable.split("@")[0] == "GF"):
    if( variable not in GFlist_name):
      GFlist_name.append(variable)
      GFlist_value.append("")
      GFlist_type.append("")
  elif( variable.split("@")[0] == "LF"):
    if( variable not in LFlist_name):
      LFlist_name.append(variable)
      LFlist_value.append("")
      LFlist_type.append("")
  elif( variable.split("@")[0] == "TF"):
    if( variable not in TFlist_name):
      TFlist_name.append(variable)
      TFlist_value.append("")
      TFlist_type.append("")

  

##############################################################################

def interpreting( instruction ):
    global GFlist_name
    global LFlist_name
    global TFlist_name

    global GFlist_value
    global LFlist_value
    global TFlist_value

    global GFlist_type
    global LFlist_type
    global TFlist_type

    global glob_label
    global ignore_while

    if(instruction.name == "LABEL" and instruction.argument1 == glob_label):
      ignore_while = False
    '''
    #print(ignore_while)
    #print(glob_label)
    #global instruction # object name
    print(instruction.name)
    if( instruction.argument1 != ""):
      print("Argument ( %(n)s ) has type  ( %(s)s )" % {'n': instruction.argument1, 's': instruction.typ1})
    if( instruction.argument2 != ""):
      print("Argument ( %(n)s ) has type  ( %(s)s )" % {'n': instruction.argument2, 's': instruction.typ2})
    if( instruction.argument3 != ""):
      print("Argument ( %(n)s ) has type  ( %(s)s )" % {'n': instruction.argument3, 's': instruction.typ3})
    '''
    if ( ignore_while == False):
      ###################################################################################################
      if( instruction.name == "MOVE"):
        #if correctly written
        if( instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == "" ):
          if( instruction.typ1 == "var" and (instruction.typ2 == "var" or instruction.typ2 == "int" or
          instruction.typ2 == "bool" or instruction.typ2 == "string")):
            # if first argument (variable) exists
            if(check_if_exists(instruction.argument1) == 1):
                # if second argument is variable
                if('@' in instruction.argument2 and instruction.typ2 == "var"):
                  # if variable (arg2) exists
                  if(check_if_exists(instruction.argument2) == 1):
                    value = give_me_value(instruction.argument2)
                    typ = give_me_type(instruction.argument2)
                    write_value_to_var(instruction.argument1, value, typ)
                  else:
                    print("ERROR: Illegal format of input file ( Unknown variable )!")
                    exit(54)
                # if arg2 is literal
                else:
                  value = instruction.argument2
                  typ = instruction.typ2
                  if(typ == "int" or typ == "bool" or typ == "string"):
                    write_value_to_var(instruction.argument1, value, typ)
            else:
              print("ERROR: Illegal format of input file ( Unknown variable )!")
              exit(54) # chyba lexikální nebo syntaktické analýzy
          else:
            print("ERROR: Illegal format of input file!")
            exit(32)
        else:
          print("ERROR: Illegal format of input file (Instruct MOVE has invalid arguments)!")
          exit(32)
      ###################################################################################################  TODO
      elif( instruction.name == "CREATEFRAME"):
        #TFlist_name = []
        #TFlist_value = []
        #print("------------------- mam CREATEFRAME ------------------------")
        aaa = 1
      elif( instruction.name == "POPFRAME"):
        aaa = 1
        #print("------------------- mam POPFRAME ------------------------")
      elif( instruction.name == "PUSHFRAME"):
        #del TFlist_name[:]
        #del TFlist_value[:]
        aaa = 1
        #print("------------------- mam PUSHFRAME ------------------------")
      ###################################################################################################
      elif( instruction.name == "DEFVAR"):
        if(instruction.argument2 == "" and instruction.argument3 == ""):
          if( check_if_exists(instruction.argument1) != 1):
            create_variable(instruction.argument1)
          else:
            print("ERROR: Illegal format of input file ( Redefinied variable )!")
            exit(52) # chyba lexikální nebo syntaktické analýzy
        else: 
          print("ERROR: Illegal format of input file ( Defvar syntax )!")
          exit(32) # chyba lexikální nebo syntaktické analýzy
      ###################################################################################################  TODO
      elif( instruction.name == "CALL"):
        aaa = 1
        #print("------------------- mam CALL ------------------------")
      ##########################################################
      elif( instruction.name == "RETURN"):
        aaa = 1
        #print("------------------- mam RETURN ------------------------")
      #########################################################################################
      elif( instruction.name == "PUSHS"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if(instruction.typ1 == "var"):
            if(check_if_exists(instruction.argument1)):
              typ1 = give_me_type(instruction.argument1)
              val1 = give_me_value(instruction.argument1)
          elif(instruction.typ1 == "int" or instruction.typ1 == "string" or instruction.typ1 == "bool"):
            if "@" in instruction.argument1:
              val1=instruction.argument1.split("@")[1]
              if((instruction.argument1.split("@")[0]).lower() == instruction.typ1):
                typ1=instruction.argument1.split("@")[0].lower()
            else:
              val1 = instruction.argument1
              typ1 = instruction.typ1
          else:
            print("ERROR: Irelevant type of args in instruction 'ADD'!")
            exit(32)
          # mam hodnotu a typ symb1
          '''
          print("print(val1): ")
          print(val1)
          print("print(typ1): ")
          print(typ1)
          '''
          s.push(typ1, val1)
        else:
          print("ERROR: Illegal format of input file ( Pushs syntax )!")
          exit(32)
        #print("------------------- mam PUSHS ------------------------")
      ##########################################################
      elif( instruction.name == "POPS"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if(instruction.typ1 == "var"):
            if(check_if_exists(instruction.argument1)):
              write_value_to_var(instruction.argument1, s.pop_value(), s.pop_typ())
            else:
              print("ERROR: Unknown variable in instruction 'POP'!")
              exit(54) # chyba lexikální nebo syntaktické analýzy
          else:
            print("ERROR: Required variable in instruction 'POP'!")
            exit(32)
        else:
          print("ERROR: Illegal format of input file ( POP syntax )!")
          exit(32)
        #print("------------------- mam POPS ------------------------")
      #########################################################################################
      elif( instruction.name == "ADD"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if((instruction.argument2.split("@")[0]).lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'ADD'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if((instruction.argument3.split("@")[0]).lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            else:
              print("ERROR: Irelevant type of args in instruction 'ADD'!")
              exit(32)
            # mam hodnotu a typ symb2
            #if(val1 != "int")

            if "@" in str(val1):
              if(val1.split("@")[0].lower() == "int"):
                val1=int(val1.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'ADD'!")
                exit(32)
            if "@" in str(val2):
              if(val2.split("@")[0].lower() == "int"):
                val2=int(val2.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'ADD'!")
                exit(32)

            if(typ1 == "int" and typ2 == "int"):  
              if(str(val1).isdigit() == True and str(val2).isdigit() == True):
                res_add = int(val1) + int(val2)
                write_value_to_var(instruction.argument1, res_add, "int")
              else:
                print("ERROR: Int with not digits in instruction 'ADD'!")
                exit(32)
            else:
              print("ERROR: Irelevant type of args in instruction 'ADD'!")
              exit(32)
        else:
          print("ERROR: Irelevant numb of args in instruction 'ADD'!")
          exit(32) 
        #print("------------------- mam ADD ------------------------")
      ###########################################################
      elif( instruction.name == "SUB"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if((instruction.argument2.split("@")[0]).lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'SUB'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if((instruction.argument3.split("@")[0]).lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            else:
              print("ERROR: Irelevant type of args in instruction 'SUB'!")
              exit(32)
            # mam hodnotu a typ symb2
            if "@" in str(val1):
              if(val1.split("@")[0].lower() == "int"):
                val1=int(val1.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'SUB'!")
                exit(32)
            if "@" in str(val2):
              if(val2.split("@")[0].lower() == "int"):
                val2=int(val2.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'SUB'!")
                exit(32)
            if(typ1 == "int" and typ2 == "int"):  
              if(str(val1).isdigit() == True and str(val2).isdigit() == True):
                res_sub = int(val1) - int(val2)
                write_value_to_var(instruction.argument1, res_sub, "int")
              else:
                print("ERROR: Int with not digits in instruction 'SUB'!")
                exit(32)
            else:
              print("ERROR: Irelevant type of args in instruction 'SUB'!")
              exit(32)
        else:
          print("ERROR: Irelevant numb of args in instruction 'SUB'!")
          exit(32) 
        #print("------------------- mam SUB ------------------------")
      ###########################################################
      elif( instruction.name == "MUL"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if((instruction.argument2.split("@")[0]).lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'MUL'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if((instruction.argument3.split("@")[0]).lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            else:
              print("ERROR: Irelevant type of args in instruction 'MUL'!")
              exit(32)
            # mam hodnotu a typ symb2
            if "@" in str(val1):
              if(val1.split("@")[0].lower() == "int"):
                val1=int(val1.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'MUL'!")
                exit(32)
            if "@" in str(val2):
              if(val2.split("@")[0].lower() == "int"):
                val2=int(val2.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'MUL'!")
                exit(32)

            if(typ1 == "int" and typ2 == "int"):  
              if(str(val1).isdigit() == True and str(val2).isdigit() == True):
                res_mul = int(val1) * int(val2)
                write_value_to_var(instruction.argument1, res_mul, "int")
              else:
                print("ERROR: Int with not digits in instruction 'MUL'!")
                exit(32)
            else:
              print("ERROR: Irelevant type of args in instruction 'MUL'!")
              exit(32)
        else:
          print("ERROR: Irelevant numb of args in instruction 'MUL'!")
          exit(32) 
        #print("------------------- mam MUL ------------------------")
      ###########################################################
      elif( instruction.name == "IDIV"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if((instruction.argument2.split("@")[0]).lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'IDIV'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if((instruction.argument3.split("@")[0]).lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            else:
              print("ERROR: Irelevant type of args in instruction 'IDIV'!")
              exit(32)
            # mam hodnotu a typ symb2
            if "@" in str(val1):
              if(val1.split("@")[0].lower() == "int"):
                val1=int(val1.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'IDIV'!")
                exit(32)
            if "@" in str(val2):
              if(val2.split("@")[0].lower() == "int"):
                val2=int(val2.split("@")[1])
              else:
                print("ERROR: Irelevant type of args in instruction 'IDIV'!")
                exit(32)
            if(typ1 == "int" and typ2 == "int"):  
              if(str(val1).isdigit() == True and str(val2).isdigit() == True):
                if(int(val2) != 0):
                  res_mul = int(val1) // int(val2)
                  write_value_to_var(instruction.argument1, res_mul, "int")
                else:
                  print("ERROR: Div by zero in instruction 'IDIV'!")
                  exit(57) # divide by zero
              else:
                print("ERROR: Int with not digits in instruction 'IDIV'!")
                exit(32)
            else:
              print("ERROR: Irelevant type of args in instruction 'IDIV'!")
              exit(32)
        else:
          print("ERROR: Irelevant numb of args in instruction 'IDIV'!")
          exit(32) 
        #print("------------------- mam IDIV ------------------------")
      #########################################################################################
      elif( instruction.name == "LT"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int" or instruction.typ2 == "bool" or instruction.typ2 == "string"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if((instruction.argument2.split("@")[0]).lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'LT'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ1 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int" or instruction.typ3 == "bool" or instruction.typ3 == "string"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if(instruction.argument3.split("@")[0].lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            # mam hodnotu a typ symb2
            else:
              print("ERROR: Irelevant type of args in instruction 'LT'!")
              exit(52)
            if "@" in val1:
              val1=val1.split("@")[1]
            if "@" in val2:
              val2=val2.split("@")[1]

            if( typ1 == typ2 ):
              if(typ1 != "bool"):
                if(val1 < val2):
                  result_bool = "true"
                else:
                  result_bool = "false"
              else:
                if( val1 == "true" or val2 == "false"):
                  result_bool = "false"
                else:
                  result_bool = "true"
              write_value_to_var(instruction.argument1, result_bool, "bool")

            else:
              print("ERROR: Not equal types of args in instruction 'LT'!")
              exit(52)
          else:
            print("ERROR: Unknown variable in 'LT' instruction!")
            exit(54)
        else:
          print("ERROR: Irelevant numb of args in instruction 'LT'!")
          exit(32)

        '''
        var = GFlist_name
        #val = GFlist_value
        print("********** print(var) :")
        print(var)
        print("********** print(*GFlist_name) :")
        print(*GFlist_name)
        print("********** print(*GFlist_name, sep='/n') :")
        print(*GFlist_name, sep='\n')
        print("********** print(len(GFlist_name)) :")
        print(len(GFlist_name))
        print(" **** insideee: ")
        s1.push(var)
        #s2.push(val)
        #del GFlist_name[:]
        #GFlist_name.clear()
        var = 52
        #GFlist_name[:] = []
        print(" **** insideee: ")
        s1.push("66")
        #GFlist_value.clear()
        #GFlist_value[:] = []
        #del GFlist_value[:]
        GFlist_name = s1.pop()
        #GFlist_value = s2.pop()
        print("********** print(GFlist_name)")
        print(GFlist_name)
        #GFlist_name.append(s1.pop())
        #GFlist_value.append(s2.pop())
        #print("pisem:")
        #for p in GFlist_name: print(p)

        nahrada1 = GFlist_name
        nahrada2 = GFlist_value
        GFlist_name = nahrada1
        GFlist_value = nahrada2
        print(s1.isEmpty())
        '''
        #print("------------------- mam LT ------------------------")
      ###########################################################
      elif( instruction.name == "GT"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int" or instruction.typ2 == "bool" or instruction.typ2 == "string"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if(instruction.argument2.split("@")[0].lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'LT'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ1 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int" or instruction.typ3 == "bool" or instruction.typ3 == "string"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if(instruction.argument3.split("@")[0].lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            # mam hodnotu a typ symb2
            else:
              print("ERROR: Irelevant type of args in instruction 'GT'!")
              exit(52)
            if "@" in val1:
              val1=val1.split("@")[1]
            if "@" in val2:
              val2=val2.split("@")[1]

            if( typ1 == typ2 ):
              if(typ1 != "bool"):
                if(val1 > val2):
                  result_bool = "true"
                else:
                  result_bool = "false"
              else:
                if( val1 == "false" or val2 == "true"):
                  result_bool = "false"
                else:
                  result_bool = "true"
              write_value_to_var(instruction.argument1, result_bool, "bool")

            else:
              print("ERROR: Not equal types of args in instruction 'GT'!")
              exit(52)
          else:
            print("ERROR: Unknown variable in 'LT' instruction!")
            exit(54)
        else:
            print("ERROR: Irelevant numb of args in instruction 'GT'!")
            exit(32)
        #print("------------------- mam GT ------------------------")
      ###########################################################
      elif( instruction.name == "EQ"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int" or instruction.typ2 == "bool" or instruction.typ2 == "string"):
                if "@" in instruction.argument2:
                  val1=instruction.argument2.split("@")[1]
                  if(instruction.argument2.split("@")[0].lower() == instruction.typ2):
                    typ1=instruction.argument2.split("@")[0].lower()
                else:
                  val1 = instruction.argument2
                  typ1 = instruction.typ2
            else:
              print("ERROR: Irelevant type of args in instruction 'EQ'!")
              exit(32)
            # mam hodnotu a typ symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int" or instruction.typ3 == "bool" or instruction.typ3 == "string"):
                if "@" in instruction.argument3:
                  val2=instruction.argument3.split("@")[1]
                  if(instruction.argument3.split("@")[0].lower() == instruction.typ3):
                    typ2=instruction.argument3.split("@")[0].lower()
                else:
                  val2 = instruction.argument3
                  typ2 = instruction.typ3
            # mam hodnotu a typ symb2
            else:
              print("ERROR: Irelevant type of args in instruction 'LT'!")
              exit(52)
            if "@" in val1:
              val1=val1.split("@")[1]
            if "@" in val2:
              val2=val2.split("@")[1]

            if( typ1 == typ2 ):
              if(typ1 != "bool"):
                if(val1 == val2):
                  result_bool = "true"
                else:
                  result_bool = "false"
              else:
                if( (val1 == "true" and val2 == "true") or (val1 == "false" and val2 == "false")):
                  result_bool = "true"
                else:
                  result_bool = "false"
              write_value_to_var(instruction.argument1, result_bool, "bool")

            else:
              print("ERROR: Not equal types of args in instruction 'EQ'!")
              exit(52)
          else:
            print("ERROR: Unknown variable in 'EQ' instruction!")
            exit(54)
        else:
            print("ERROR: Irelevant numb of args in instruction 'LT'!")
            exit(32)
        #print("------------------- mam EQ ------------------------")
      #########################################################################################
      elif( instruction.name == "AND"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "bool"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'AND' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "bool"):
                typ2=instruction.typ3
                val2=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'AND' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb2
            if "@" in val1:
              if(val1.split("@")[0].lower() == "bool"):
                val1=val1.split("@")[1]
            if "@" in val2:
              if(val2.split("@")[0].lower() == "bool"):
                val2=val2.split("@")[1]

            if((val1 != "true" and val1 != "false") or (val2 != "true" and val2 != "false")):
              print("ERROR: Invalid types of operands in 'AND' instruction!")
              exit(53)

            if(typ1 == "bool" and typ2 == "bool"):
              if(val1 == "true" and val2 == "true"):
                res_bool = "true"
              else:
                res_bool = "false"
              write_value_to_var(instruction.argument1, res_bool, "bool")
            else:
              print("ERROR: Invalid types of operands in 'AND' instruction!")
              exit(53)

          else:
            print("ERROR: Unknown variable in 'AND' instruction!")
            exit(54)
        else:
          print("ERROR: Too much/less args in 'AND' instruction!")
          exit(32)
        #print("------------------- mam AND ------------------------")
      ##########################################################
      elif( instruction.name == "OR"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "bool"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'OR' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "bool"):
                typ2=instruction.typ3
                val2=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'OR' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb2
            if "@" in val1:
              if(val1.split("@")[0].lower() == "bool"):
                val1=val1.split("@")[1]
            if "@" in val2:
              if(val2.split("@")[0].lower() == "bool"):
                val2=val2.split("@")[1]

            if((val1 != "true" and val1 != "false") or (val2 != "true" and val2 != "false")):
              print("ERROR: Invalid types of operands in 'OR' instruction!")
              exit(53)

            if(typ1 == "bool" and typ2 == "bool"):
              if(val1 == "false" and val2 == "false"):
                res_bool = "false"
              else:
                res_bool = "true"
              write_value_to_var(instruction.argument1, res_bool, "bool")
            else:
              print("ERROR: Invalid types of operands in 'OR' instruction!")
              exit(53)

          else:
            print("ERROR: Unknown variable in 'OR' instruction!")
            exit(54)
        else:
          print("ERROR: Too much/less args in 'OR' instruction!")
          exit(32)
        #print("------------------- mam OR ------------------------")
      ##########################################################
      elif( instruction.name == "NOT"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "bool"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'NOT' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb1
  
            if "@" in val1:
              if(val1.split("@")[0].lower() == "bool"):
                val1=val1.split("@")[1]

            if(val1 != "true" and val1 != "false"):
              print("ERROR: Invalid types of operands in 'NOT' instruction!")
              exit(53)

            if(typ1 == "bool"):
              if(val1 == "false"):
                res_bool = "true"
              else:
                res_bool = "false"
              write_value_to_var(instruction.argument1, res_bool, "bool")
            else:
              print("ERROR: Invalid types of operands in 'NOT' instruction!")
              exit(53)

          else:
            print("ERROR: Unknown variable in 'NOT' instruction!")
            exit(54)
        else:
          print("ERROR: Too much/less args in 'NOT' instruction!")
          exit(32)
        #print("------------------- mam NOT ------------------------")
      #########################################################################################
      elif( instruction.name == "INT2CHAR"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'INT2CHAR' instruction!")
              exit(53)
            # mam typ (bool) a hodnotu (true/false) symb1
          else:
            print("ERROR: Unknown variable in 'INT2CHAR' instruction!")
            exit(54)

          if "@" in val1:
            if(val1.split("@")[0].lower() == "int"):
              val1=int(val1.split("@")[1] ) 
          if( int(val1) > 126):
            print("ERROR: Ordinally value higher than 126 in 'INT2CHAR' instruction!")
            exit(58)
          if(typ1 == "int"):
            res = chr(int(val1))
            write_value_to_var(instruction.argument1, res, "string")
        else:
          print("ERROR: Too much/less args in 'INT2CHAR' instruction!")
          exit(32)
        #print("------------------- mam INT2CHAR ------------------------")
      ##########################################################
      elif( instruction.name == "STRI2INT"): 
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "string"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'STRI2INT' instruction!")
              exit(53)
            # mam typ (string) a hodnotu  symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                typ2=instruction.typ3
                val2=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'STRI2INT' instruction!")
              exit(53)
            # mam typ (int) a hodnotu  symb2
          else:
            print("ERROR: Unknown variable in 'STRI2INT' instruction!")
            exit(54)

          if "@" in val1:
            if(val1.split("@")[0].lower() == "string"):
              val1=val1.split("@")[1] 
          if "@" in val2:
            if(val2.split("@")[0].lower() == "int"):
              val2=int(val2.split("@")[1])

          if(typ1 == "string" and typ2 == "int"):
            if(len(val1) < int(val2)):
              print("ERROR: Length of string is less then index in 'STRI2INT' instruction!")
              exit(58)
            res = val1[int(val2):int(val2)+1]
            resalt = ord(res)
            write_value_to_var(instruction.argument1, resalt, "int")
        else:
          print("ERROR: Too much/less args in 'STRI2INT' instruction!")
          exit(32)
        
        #print("------------------- mam STRI2INT ------------------------")
      #########################################################################################
      elif( instruction.name == "READ"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.argument2 == "int" and instruction.typ2 == "type"):
              result_read = input("Insert numb:")
              if( not result_read.isdigit()):
                print("ERROR: Invalid type of inserted value in 'READ' instruction!")
                exit(53)
            elif(instruction.argument2 == "bool" and instruction.typ2 == "type"):
              result_read = input("Insert true/false:")
              if( result_read != "true" and result_read != "false"):
                print("ERROR: Invalid type of inserted value in 'READ' instruction!")
                exit(53)
            elif(instruction.argument2 == "string" and instruction.typ2 == "type"):
              result_read = input("Insert string:")
            else:
              print("ERROR: Unknown type in 'READ' instruction!")
              exit(53)
            write_value_to_var(instruction.argument1, result_read, instruction.argument2)
          else:
            print("ERROR: Unknown variable in 'READ' instruction!")
            exit(54)
        else:
          print("ERROR: Illegal format of input file ( read instruction )!")
          exit(32)
        #print("------------------- mam READ ------------------------")
      ##################################################
      elif( instruction.name == "WRITE"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if(instruction.typ1 == "var"):
            if(check_if_exists(instruction.argument1)==1):
              result = give_me_value(instruction.argument1)
              i = 0
              retazec = result
              for letter in retazec:
                if (letter == "\\"):
                  numb_specific = retazec[i+1:i+4]
                  asci_specific = chr(int(numb_specific))
                  numb_specific = "\\" + numb_specific
                  result = result.replace(numb_specific, asci_specific)
                i+=1
              print(result)
            else:
              print("ERROR: Illegal format of input file ( Unknown variable )!")
              exit(54)
          elif(instruction.typ1 == "int" or instruction.typ1 == "bool" or instruction.typ1 == "string"):
            if(instruction.typ1 != "string"):
              if "@" in instruction.argument1:
                print(instruction.argument1.split("@")[1])
              else:
                print(instruction.argument1)
            else:
              if "@" in instruction.argument1:
                stri=instruction.argument1.split("@")[1]
              else:
                stri = instruction.argument1
              i = 0
              retazec = stri
              for letter in retazec:
                if (letter == "\\"):
                  numb_specific = retazec[i+1:i+4]
                  asci_specific = chr(int(numb_specific))
                  numb_specific = "\\" + numb_specific
                  stri = stri.replace(numb_specific, asci_specific)
                i+=1
              print(stri)
          else:
            print("ERROR: Illegal format of input file ( write instruction )!")
            exit(32)
        else:
          print("ERROR: Illegal format of input file ( write instruction )!")
          exit(32)
        #print("------------------- mam WRITE ------------------------")
      #########################################################################################  TODO
      elif( instruction.name == "CONCAT"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if(check_if_exists(instruction.argument1)==1):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "string"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'CONCAT' instruction!")
              exit(53)
            # mam typ (string) a hodnotu  symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "string"):
                typ2=instruction.typ3
                val2=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'CONCAT' instruction!")
              exit(53)
            # mam typ (int) a hodnotu  symb2 
          else:
            print("ERROR: Unknown variable in 'CONCAT' instruction!")
            exit(54)

          if "@" in val1:
            if(val1.split("@")[0].lower() == "string"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'CONCAT' instruction!")
              exit(53)
          if "@" in val2:
            if(val2.split("@")[0].lower() == "string"):
              val2=int(val2.split("@")[1])
            else:
              print("ERROR: Invalid types of operands in 'CONCAT' instruction!")
              exit(53)

          if(typ1 == "string" and typ2 == "string"):
            res = val1 + val2
            write_value_to_var(instruction.argument1, res, "string")

        else:
          print("ERROR: Illegal format of input file ( concat instruction )!")
          exit(32)
        #print("------------------- mam CONCAT ------------------------")
       #######################################################
      elif( instruction.name == "STRLEN"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == ""):
          if(check_if_exists(instruction.argument1)==1):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "string"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'STRLEN' instruction!")
              exit(53)
            # mam typ (string) a hodnotu  symb1
          else:
            print("ERROR: Unknown variable in 'STRLEN' instruction!")
            exit(54)
          if "@" in val1:
            if(val1.split("@")[0].lower() == "string"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'STRLEN' instruction!")
              exit(53)
          if(typ1 == "string"):
            res = len(val1)
            write_value_to_var(instruction.argument1, res, "int")
          else:
            print("ERROR: Invalid types of operands in 'STRLEN' instruction!")
            exit(53)
        else:
          print("ERROR: Illegal format of input file ( strlen instruction )!")
          exit(32)
        #print("------------------- mam STRLEN ------------------------")
      #######################################################
      elif( instruction.name == "GETCHAR"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
                val1 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "string"):
                typ1=instruction.typ2
                val1=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'GETCHAR' instruction!")
              exit(53)
            # mam typ (string) a hodnotu  symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ2 = give_me_type(instruction.argument3)
                val2 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "int"):
                typ2=instruction.typ3
                val2=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'GETCHAR' instruction!")
              exit(53)
            # mam typ (int) a hodnotu  symb2
          else:
            print("ERROR: Unknown variable in 'GETCHAR' instruction!")
            exit(54)

          if "@" in val1:
            if(val1.split("@")[0].lower() == "string"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'GETCHAR' instruction!")
              exit(53)
          if "@" in val2:
            if(val2.split("@")[0].lower() == "int"):
              val2=int(val2.split("@")[1])
            else:
              print("ERROR: Invalid types of operands in 'GETCHAR' instruction!")
              exit(53)

          if(typ1 == "string" and typ2 == "int"):
            if(len(val1) < int(val2)):
              print("ERROR: Length of string is less then index in 'GETCHAR' instruction!")
              exit(58)
            res = val1[int(val2):int(val2)+1]
            write_value_to_var(instruction.argument1, res, "string")
        else:
          print("ERROR: Too much/less args in 'GETCHAR' instruction!")
          exit(32)
        #print("------------------- mam GETCHAR ------------------------")
      #######################################################
      elif( instruction.name == "SETCHAR"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            typ1 = give_me_type(instruction.argument1)
            val1 = give_me_value(instruction.argument1)
            # mam typ  (musi byt string) premennej
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ2 = give_me_type(instruction.argument2)
                val2 = give_me_value(instruction.argument2)
            elif(instruction.typ2 == "int"):
                typ2=instruction.typ2
                val2=instruction.argument2
            else:
              print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
              exit(53)
            # mam typ (int) a hodnotu  symb1
            if(instruction.typ3 == "var"):
              if(check_if_exists(instruction.argument3)):
                typ3 = give_me_type(instruction.argument3)
                val3 = give_me_value(instruction.argument3)
            elif(instruction.typ3 == "string"):
                typ3=instruction.typ3
                val3=instruction.argument3
            else:
              print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
              exit(53)
            # mam typ (string) a hodnotu  symb2
          else:
            print("ERROR: Unknown variable in 'SETCHAR' instruction!")
            exit(54)

          if(typ1 != "string" or typ2 != "int" or typ3 != "string"):
            print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
            exit(53)
          if "@" in val1:
            if(val1.split("@")[0].lower() == "string"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
              exit(53)

          if "@" in val2:
            if(val2.split("@")[0].lower() == "int"):
              val2=int(val2.split("@")[1])
            else:
              print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
              exit(53)

          if "@" in val3:
            if(val3.split("@")[0].lower() == "string"):
              val3=int(val3.split("@")[1])
            else:
              print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
              exit(53)

          if(typ1 == "string" and typ2 == "int" and typ3 == "string"):
            if(len(val3) > 1):
              val3 = val3[0]
            if(len(val1) < int(val2)):
              print("ERROR: Length of string is shorter then index in 'SETCHAR' instruction!")
              exit(58)
            val1 = val1[:int(val2)] + val3 + val1[int(val2)+1:]
            write_value_to_var(instruction.argument1, val1, "string")
          else:
            print("ERROR: Invalid types of operands in 'SETCHAR' instruction!")
            exit(53)

        else:
          print("ERROR: Too much/less args in 'SETCHAR' instruction!")
          exit(32)
        #print("------------------- mam SETCHAR ------------------------")
      #########################################################################################
      elif( instruction.name == "TYPE"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 == ""):
          if( check_if_exists(instruction.argument1) == 1 and instruction.typ1 == "var"):
            if(instruction.typ2 == "var"):
              if(check_if_exists(instruction.argument2)):
                typ1 = give_me_type(instruction.argument2)
            elif(instruction.typ2 == "int" or instruction.typ2 == "bool" or instruction.typ2 == "string"):
                typ1=instruction.typ2
            # mam typ (string) a hodnotu  symb2
            else:
              print("ERROR: Invalid types of operands in 'TYPE' instruction!")
              exit(53)
            # mam typ (int) a hodnotu  symb1
            write_value_to_var(instruction.argument1, typ1, "string")
          else:
            print("ERROR: Unknown variable in 'TYPE' instruction!")
            exit(54)
        else:
          print("ERROR: Too much/less args in 'TYPE' instruction!")
          exit(32)
        #print("------------------- mam TYPE ------------------------")
      #########################################################################################
      elif( instruction.name == "LABEL"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if( instruction.argument1 in labels_list):
            print("ERROR: Label already declared!")
            exit(52) # correct
          else:
            labels_list.append(instruction.argument1)  
        else:
          print("ERROR: Illegal format of input file ( Label instruction )!")
          exit(32)
        #print("------------------- mam LABEL ------------------------")
      ##########################################################
      elif( instruction.name == "JUMP"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if( instruction.argument1 in labels_list):
            glob_label = instruction.argument1
            ignore_while = True
            labels_list.remove(instruction.argument1)
            return 999
          else:
            ignore_while = True
            glob_label = instruction.argument1
        #print("------------------- mam JUMP ------------------------")
      ########################################################## TODO
      elif( instruction.name == "JUMPIFEQ"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if(instruction.typ2 == "var"):
            if(check_if_exists(instruction.argument2)):
              typ1 = give_me_type(instruction.argument2)
              val1 = give_me_value(instruction.argument2)
          elif(instruction.typ2 == "string" or instruction.typ2 == "int" or instruction.typ2 == "bool"):
              typ1=instruction.typ2
              val1=instruction.argument2
          else:
            print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
            exit(53)
          # mam typ (string) a hodnotu  symb1
          if(instruction.typ3 == "var"):
            if(check_if_exists(instruction.argument3)):
              typ2 = give_me_type(instruction.argument3)
              val2 = give_me_value(instruction.argument3)
          elif(instruction.typ3 == "string" or instruction.typ3 == "int" or instruction.typ3 == "bool"):
              typ2=instruction.typ3
              val2=instruction.argument3
          else:
            print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
            exit(53)
          # mam typ (int) a hodnotu  symb2

          if "@" in str(val1):
            if(val1.split("@")[0].lower() == "int"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
              exit(53)

          if "@" in str(val2):
            if(val2.split("@")[0].lower() == "int"):
              val2=val2.split("@")[1]
            else:
              print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
              exit(53)

          if(typ1 == "string" or typ1 == "bool"):
            if((typ1 == typ2) and (val1 == val2)):
              if( instruction.argument1 in labels_list):
                glob_label = instruction.argument1
                ignore_while = True
                labels_list.remove(instruction.argument1)
                return 999
              else:
                ignore_while = True
                glob_label = instruction.argument1
          else:
            if((typ1 == typ2) and (int(val1) == int(val2))):
              if( instruction.argument1 in labels_list):
                glob_label = instruction.argument1
                ignore_while = True
                labels_list.remove(instruction.argument1)
                return 999
              else:
                ignore_while = True
                glob_label = instruction.argument1

        else:
          print("ERROR: Too much/less args in 'JUMPIFEQ' instruction!")
          exit(32)
        #print("------------------- mam JUMPIFEQ ------------------------")
      ##########################################################
      elif( instruction.name == "JUMPIFNEQ"):
        if(instruction.argument1 != "" and instruction.argument2 != "" and instruction.argument3 != ""):
          if(instruction.typ2 == "var"):
            if(check_if_exists(instruction.argument2)):
              typ1 = give_me_type(instruction.argument2)
              val1 = give_me_value(instruction.argument2)
          elif(instruction.typ2 == "string" or instruction.typ2 == "int" or instruction.typ2 == "bool"):
              typ1=instruction.typ2
              val1=instruction.argument2
          else:
            print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
            exit(53)
          # mam typ (string) a hodnotu  symb1
          if(instruction.typ3 == "var"):
            if(check_if_exists(instruction.argument3)):
              typ2 = give_me_type(instruction.argument3)
              val2 = give_me_value(instruction.argument3)
          elif(instruction.typ3 == "string" or instruction.typ3 == "int" or instruction.typ3 == "bool"):
              typ2=instruction.typ3
              val2=instruction.argument3
          else:
            print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
            exit(53)
          # mam typ (int) a hodnotu  symb2

          if "@" in str(val1):
            if(val1.split("@")[0].lower() == "int"):
              val1=val1.split("@")[1] 
            else:
              print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
              exit(53)

          if "@" in str(val2):
            if(val2.split("@")[0].lower() == "int"):
              val2=val2.split("@")[1]
            else:
              print("ERROR: Invalid types of operands in 'JUMPIFEQ' instruction!")
              exit(53)

          if(typ1 == "string" or typ1 == "bool"):
            if((typ1 == typ2) and (val1 == val2)):
              if( instruction.argument1 in labels_list):
                glob_label = instruction.argument1
                ignore_while = True
                labels_list.remove(instruction.argument1)
                return 999
              else:
                ignore_while = True
                glob_label = instruction.argument1
          else:
            if((typ1 == typ2) and (int(val1) != int(val2))):
              if( instruction.argument1 in labels_list):
                glob_label = instruction.argument1
                ignore_while = True
                labels_list.remove(instruction.argument1)
                return 999
              else:
                ignore_while = True
                glob_label = instruction.argument1

        else:
          print("ERROR: Too much/less args in 'JUMPIFEQ' instruction!")
          exit(32)
        #print("------------------- mam JUMPIFNEQ ------------------------")
      #########################################################################################
      elif( instruction.name == "DPRINT"):
        if(instruction.argument1 != "" and instruction.argument2 == "" and instruction.argument3 == ""):
          if(instruction.typ1 == "var"):
            if(check_if_exists(instruction.argument1)):
              val2 = give_me_value(instruction.argument1)
          elif(instruction.typ1 == "int" or instruction.typ1 == "bool" or instruction.typ1 == "string"):
              val2=instruction.argument1
          else:
            print("ERROR: Invalid types of operands in 'DPRINT' instruction!")
            exit(53)
          if "@" in val2:
            val2=val2.split("@")[1]
          print(val2, file=sys.stdout)
        else:
          print("ERROR: Too much/less args in 'DPRINT' instruction!")
          exit(32)
        #print("------------------- mam DPRINT ------------------------")
      ##########################################################
      else:
        print("ERROR: Illegal format of input file ( Unknown instruction )!")
        exit(32) # chyba lexikální nebo syntaktické analýzy textových elementů a atributů ve vstupním XML
                   # souboru  (např. chybný lexém pro řetězcový literál, neznámý operační kód apod.).




    
