----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		17.03.2017														 |
--Názov súboru: 	bcd.vhdl 													 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;

entity bcd is
	Port (
		CLK		 : IN std_logic;
		RESET	 : IN std_logic;
		NUMBER3  : BUFFER std_logic_vector(3 downto 0);
		NUMBER2  : BUFFER std_logic_vector(3 downto 0);
		NUMBER1  : BUFFER std_logic_vector(3 downto 0)
	);
end bcd;

architecture Behavioral of bcd is	

begin
	process(CLK, RESET)
		begin
		if (RESET = '1') then
			NUMBER3 <= "0000";
			NUMBER2 <= "0000";
			NUMBER1 <= "0000";		
		elsif (CLK'event) and (CLK='1') then
			if (NUMBER1 <= "1000") then
				NUMBER1 <= NUMBER1 + "0001";
			else
				NUMBER1 <= "0000";
				if (NUMBER2 <= "1000") then
					NUMBER2 <= NUMBER2 + "0001";
				else
					NUMBER2 <= "0000";
					if (NUMBER3 <= "1000") then
						NUMBER3 <= NUMBER3 + "0001" ;
					else
						NUMBER3 <= "0000";
					end if;
				end if;
			end if;
		end if;
	end process;
end Behavioral;
