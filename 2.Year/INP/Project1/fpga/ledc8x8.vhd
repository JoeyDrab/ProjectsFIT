-----_________________________________________-----
-----____________INP Projekt C. 1_____________-----
-----_______________Jozef Drab________________-----
-----________xdrabj00@stud.fit.vutbr.cz_______-----
-----_______________xdrabj00__________________-----
-----_________________________________________-----
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity ledc8x8 is
    port(
      SMCLK, RESET: in std_logic;
      ROW, LED: out std_logic_vector(0 to 7)
    );
end ledc8x8;

architecture behv of ledc8x8 is
  
  signal active_row    : std_logic_vector (7 downto 0)   		:= "10000000";
  signal active_leds   : std_logic_vector (7 downto 0)   		:= "11111111";
  
  signal citac		   : std_logic_vector (7 downto 0)		;
  signal f         	   : std_logic                   		;
  
begin
-----------------------------------------------------------------------
process(SMCLK, RESET) 
	begin
		if (RESET = '1') then
			citac <= "00000000";
		elsif 	(SMCLK'event) and (SMCLK = '1') then
			citac <= citac +1;
		end if;			
end process;
-----------------------------------------------------------------------
	
f <= '1' when citac = X"FF" else '0';	
-----------------------------------------------------------------------
process(RESET, f, SMCLK) --rot
	begin
		if (RESET = '1') then
			active_row <= "10000000";
		elsif (SMCLK'event) and (SMCLK = '1') and (f = '1') then	
			active_row <= active_row(0) & active_row(7 downto 1);
		end if;	
end process ;
-----------------------------------------------------------------------
process(active_row) 
begin
	if (RESET = '1') then 
		active_leds <= "10000000";
	elsif (SMCLK'event) and (SMCLK = '1') then
			case active_row is
				when "10000000" => active_leds <= "00001111";
				when "01000000" => active_leds <= "11101111";
				when "00100000" => active_leds <= "11101111";
				when "00010000" => active_leds <= "01100001";
				when "00001000" => active_leds <= "10010110";
				when "00000100" => active_leds <= "11110110";
				when "00000010" => active_leds <= "11110110";
				when "00000001" => active_leds <= "11110001";
				when others     => active_leds <= "11111111";
			end case;		
	end if;
end process;

  LED  <= active_leds;
  ROW  <= active_row;

end behv;
