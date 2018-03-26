----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		17.03.2017														 |
--Názov súboru: 	lightsout_pack.vhdl 										 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;

package lightsout_pack is
	type mask_t is
		record
			top        		: std_logic;
			left        	: std_logic;
			right        	: std_logic;
			bottom        	: std_logic;
		end record;
	function getmask(x,y : natural; COLUMNS, ROWS : natural) return mask_t;

end lightsout_pack;

package body lightsout_pack is

	function getmask(x,y : natural; COLUMNS, ROWS : natural) return mask_t is	
	variable func_mask : mask_t;
	
	begin
		if (ROWS > 0 and ROWS-1 >= y and y >= 0  and COLUMNS-1 >= x and COLUMNS > 0 and x >= 0) then			
			if (x = 0) then
				func_mask.left := '0';
				func_mask.right := '1';
			elsif (x = COLUMNS-1) then
				func_mask.left := '1';
				func_mask.right := '0';	
			elsif (COLUMNS-1 = 0) then
				func_mask.left :='0';
				func_mask.right :='0';		
			else
				func_mask.left := '1';
				func_mask.right := '1';
			end if;
			
			if (y = 0) then
				func_mask.top := '0';
				func_mask.bottom := '1';
			elsif (y = ROWS-1) then
				func_mask.top := '1';
				func_mask.bottom := '0';	
			elsif (ROWS-1 = 0) then
				func_mask.top :='0';
				func_mask.bottom :='0';			
			else
				func_mask.top := '1';
				func_mask.bottom := '1';
			end if;
		else
			func_mask.top := '0';
			func_mask.left :='0';	
			func_mask.right :='0';
			func_mask.bottom := '0';
		end if;	
		
		return func_mask;
	end getmask;
 
end lightsout_pack;
