----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		11.05.2017														 |
--Názov súboru: 	cell_generator.vhdl 										 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use work.lightsout_pack.all;

entity cell_generator is
	Port 
	( 
		cell_gen_cursor : out std_logic_vector(24 downto 0);
		cell_gen_cells_ON : out std_logic_vector(24 downto 0);
		cell_gen_cells :in std_logic_vector(24 downto 0); 
		cell_gen_clk :in std_logic;
		cell_gen_reset : in std_logic;
		cell_gen_key : IN  std_logic_vector(4 downto 0)
	);
end cell_generator;

architecture Behavioral of cell_generator is
   component cell
		generic 
		(
			func_mask              : mask_t := (others => '1') 
		);
		Port
		(
			INVERT_REQ_IN : IN  std_logic_vector(3 downto 0) := (others => '0');
			INVERT_REQ_OUT : OUT  std_logic_vector(3 downto 0);
			KEYS : IN  std_logic_vector(4 downto 0) := (others => '0');
			SELECT_REQ_IN : IN  std_logic_vector(3 downto 0) := (others => '0');
			SELECT_REQ_OUT : OUT  std_logic_vector(3 downto 0);
			INIT_ACTIVE : IN  std_logic := '0';
			ACTIVE : OUT  std_logic;
			INIT_SELECTED : IN  std_logic := '0';
			SELECTED : OUT  std_logic;
			CLK : IN  std_logic := '0';
			RESET : IN  std_logic := '0'
		);
    end component;

	signal select_request : std_logic_vector(99 downto 0);
	signal invert_request : std_logic_vector(99 downto 0);
	signal active_cells : std_logic_vector(24 downto 0);
	signal selected_cells : std_logic_vector(24 downto 0);
	signal init_selected_cells : std_logic_vector(24 downto 0) := "0000000000001000000000000";
	constant CONST_TOP    : NATURAL := 0; 
	constant CONST_LEFT   : NATURAL := 1;
	constant CONST_RIGHT  : NATURAL := 2; 
	constant CONST_BOTTOM : NATURAL := 3; 
	signal x : integer := 0;
	signal y : integer := 0;
begin
	cell_gen_cursor <= active_cells;
	cell_gen_cells_ON <= selected_cells;
	
	create_y: 
	for y in 0 to 4 generate
	begin
		create_x: 
		for x in 0 to 4 generate
		begin
			genericmap: cell generic map
			(
				func_mask => getmask(x, y, 5, 5)
			)
			port map
			(
				CLK =>  cell_gen_clk,
				RESET => cell_gen_reset,
				KEYS => cell_gen_key,
				ACTIVE => active_cells(y * 5 + x),
				SELECTED => selected_cells(y * 5 + x),
				INIT_ACTIVE => cell_gen_cells(y * 5 + x),
				INIT_SELECTED => init_selected_cells(y * 5 + x),
				INVERT_REQ_IN(CONST_LEFT) => invert_request(((x - 1) mod 5) * 4 + (y mod 5) * 20 + CONST_RIGHT),
				INVERT_REQ_IN(CONST_RIGHT) => invert_request(((x + 1) mod 5) * 4 + (y mod 5) * 20 + CONST_LEFT),
				INVERT_REQ_IN(CONST_TOP) => invert_request((x mod 5) * 4 + ((y - 1) mod 5) * 20 + CONST_BOTTOM),
				INVERT_REQ_IN(CONST_BOTTOM) => invert_request((x mod 5) * 4 + ((y + 1) mod 5) * 20 + CONST_TOP),
				SELECT_REQ_IN(CONST_LEFT) => select_request(((x - 1) mod 5) * 4 + (y mod 5) * 20 + CONST_RIGHT),
				SELECT_REQ_IN(CONST_RIGHT) => select_request(((x + 1) mod 5) * 4 + (y mod 5) * 20 + CONST_LEFT),
				SELECT_REQ_IN(CONST_TOP) => select_request((x mod 5) * 4 + ((y - 1) mod 5) * 20 + CONST_BOTTOM),
				SELECT_REQ_IN(CONST_BOTTOM) => select_request((x mod 5) * 4 + ((y + 1) mod 5) * 20 + CONST_TOP),
				INVERT_REQ_OUT => invert_request(((x mod 5) * 4 + (y mod 5) * 20 + CONST_BOTTOM) downto ((x mod 5) * 4 + (y mod 5) * 20 + CONST_TOP)),
				SELECT_REQ_OUT => select_request(((x mod 5) * 4 + (y mod 5) * 20 + CONST_BOTTOM) downto ((x mod 5) * 4 + (y mod 5) * 20 + CONST_TOP))
			);	
		end generate;
	end generate;
end Behavioral;
