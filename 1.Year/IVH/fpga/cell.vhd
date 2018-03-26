----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		17.03.2017													   	 |
--Názov súboru: 	cell.vhdl 										 			 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.lightsout_pack.ALL;

entity cell is
    generic ( 
		func_mask 		: mask_t := (others => '1')
	);
	
    Port(
		INVERT_REQ_IN     : in   STD_LOGIC_VECTOR (3 downto 0);
		INVERT_REQ_OUT    : out  STD_LOGIC_VECTOR (3 downto 0);
		KEYS              : in   STD_LOGIC_VECTOR (4 downto 0);
		SELECT_REQ_IN     : in   STD_LOGIC_VECTOR (3 downto 0);
		SELECT_REQ_OUT    : out  STD_LOGIC_VECTOR (3 downto 0);
		INIT_ACTIVE       : in   STD_LOGIC;
		ACTIVE            : out  STD_LOGIC;
		INIT_SELECTED     : in   STD_LOGIC;
		SELECTED          : out  STD_LOGIC;
		CLK               : in   STD_LOGIC;
		RESET             : in   STD_LOGIC
    );
end cell;

architecture Behavioral of cell is

	constant CONST_TOP    	: NATURAL := 0; 
	constant CONST_LEFT   	: NATURAL := 1;
	constant CONST_RIGHT  	: NATURAL := 2; 
	constant CONST_BOTTOM 	: NATURAL := 3; 
	constant CONST_ENTER  	: NATURAL := 4; 
	signal cell_ON 	: STD_LOGIC;
	signal cell_cursor  	: STD_LOGIC;

begin
	ACTIVE <= cell_cursor;
	SELECTED <= cell_ON;

	main : process(CLK, RESET)
	begin
		if (RESET = '1') then
			cell_cursor   <= INIT_ACTIVE;
			cell_ON <= INIT_SELECTED;
			SELECT_REQ_OUT <= (others => '0');
			INVERT_REQ_OUT <= (others => '0');

		elsif rising_edge(CLK) then 		
			INVERT_REQ_OUT <= (others => '0');
			SELECT_REQ_OUT <= (others => '0');

			if (cell_ON = '0') then
				if ((INVERT_REQ_IN and (func_mask.BOTTOM & func_mask.RIGHT & func_mask.LEFT & func_mask.TOP)) /= "0000" ) then
					cell_cursor <= not cell_cursor;	
				end if;
				if ((SELECT_REQ_IN and (func_mask.BOTTOM & func_mask.RIGHT & func_mask.LEFT & func_mask.TOP)) /= "0000" ) then
					cell_ON <= not cell_ON;
				end if;	
			else
				if (KEYS(CONST_ENTER) = '1') then 
					cell_cursor <= not cell_cursor;
					INVERT_REQ_OUT <= (CONST_TOP => func_mask.TOP, CONST_LEFT => func_mask.LEFT, CONST_RIGHT  => func_mask.RIGHT, CONST_BOTTOM => func_mask.BOTTOM);
				elsif (KEYS(CONST_TOP) = '1' and func_mask.TOP = '1') then
					SELECT_REQ_OUT <= (CONST_TOP => '1', others => '0');
					cell_ON <= '0';
				elsif (KEYS(CONST_RIGHT) = '1' and func_mask.RIGHT = '1') then
					SELECT_REQ_OUT <= (CONST_RIGHT => '1', others => '0');
					cell_ON <= '0';	
				elsif (KEYS(CONST_LEFT) = '1' and func_mask.LEFT = '1') then
					SELECT_REQ_OUT <= (CONST_LEFT => '1', others => '0');
					cell_ON <= '0'; 		
				elsif (KEYS(CONST_BOTTOM) = '1' and func_mask.BOTTOM = '1') then
					SELECT_REQ_OUT <= (CONST_BOTTOM => '1', others => '0');
					cell_ON <= '0';			
				end if;
			end if;
		end if;	
	end process;
end Behavioral;
