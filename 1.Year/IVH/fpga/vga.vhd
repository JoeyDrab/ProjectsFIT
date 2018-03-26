----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		17.03.2017														 |
--Názov súboru: 	vga.vhdl 													 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity vga is
    Port 
	( 
		vga_rgb : out std_logic_vector(8 downto 0);
		vga_row : in std_logic_vector(11 downto 0);
		vga_col : in std_logic_vector(11 downto 0);
		vga_cells_ON : in std_logic_vector(24 downto 0);
		vga_cursor : in std_logic_vector(24 downto 0);
		vga_number1 : in  std_logic_vector(3 downto 0);
		vga_number2 : in  std_logic_vector(3 downto 0);
		vga_number3 : in  std_logic_vector(3 downto 0)
	);
end vga;

architecture Behavioral of vga is
	signal col_aux : integer range 0 to 15;
	signal row_aux : integer range 0 to 15;
	signal score_number_1 : std_logic;
	signal score_number_2 : std_logic;
	signal score_number_3 : std_logic;
	type digit is array(0 to 16*10-1) of std_logic_vector(0 to 15);
    --					   |																																		0																																									     |																																		1																																									     |																																		2																																									     |																																		3																																									     |																																		4																																									     |																																		5																																									     |																																		6																																									     |																																		7																																									     |																																		8																																									     |																																		9																																									     |
	signal SCORE: digit := ( "0000000000000000","0001111111111000","0011111111111100","0011100000011100","0011000000001100","0011000000001100","0011000000001100","0011000000001100","0011000000001100","0011000000001100","0011000000001100","0011000000001100","0011100000011100","0011111111111100","0001111111111000","0000000000000000","0000000000000000","0000000000011100","0000000000111100","0000000001101100","0000000011001100","0000000110001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000001100","0000000000000000","0000000000000000","0011111111111000","0011111111111100","0000000000011100","0000000000001100","0000000000001100","0000000000011100","0001111111111100","0011111111111000","0011100000000000","0011000000000000","0011000000000000","0011100000000000","0011111111111100","0011111111111100","0000000000000000","0000000000000000","0011111111111000","0011111111111100","0000000000011100","0000000000001100","0000000000001100","0000000000011100","0011111111111100","0011111111111100","0000000000011100","0000000000001100","0000000000001100","0000000000011100","0011111111111100","0011111111111000","0000000000000000","0000000000000000","0000000110000000","0000001100000000","0000011000000000","0000110000000000","0001100000000000","0011000000110000","0011111111111100","0011111111111100","0000000000110000","0000000000110000","0000000000110000","0000000000110000","0000000000110000","0000000000110000","0000000000000000","0000000000000000","0011111111111100","0011111111111100","0011000000000000","0011000000000000","0011000000000000","0011000000000000","0011111111111000","0011111111111100","0000000000011100","0000000000001100","0000000000001100","0000000000011100","0011111111111100","0001111111111000","0000000000000000","0000000000000000","0000000111100000","0000011100000000","0000110000000000","0001100000000000","0011000000000000","0011000000000000","0011111111111000","0011111111111100","0011100000011100","0011000000001100","0011000000001100","0011100000011100","0011111111111100","0001111111111000","0000000000000000","0000000000000000","0011111111111100","0011111111111100","0000000000001100","0000000000001100","0000000000011000","0000000000110000","0000001111111000","0000000011000000","0000000110000000","0000001100000000","0000011000000000","0000110000000000","0001100000000000","0001100000000000","0000000000000000","0000000000000000","0001111111111000","0011100000011100","0011000000001100","0011000000001100","0011000000001100","0011100000011100","0001111111111000","0001111111111000","0011100000011100","0011000000001100","0011000000001100","0011000000001100","0011100000011100","0001111111111000","0000000000000000","0000000000000000","0001111111111000","0011111111111100","0011100000011100","0011000000001100","0011000000001100","0011100000011100","0011111111111100","0001111111111100","0000000000011100","0000000000001100","0000000000001100","0000000000011100","0011111111111100","0011111111111100","0000000000000000" );
	constant RED   : std_logic_vector (8 downto 0) := "111000000";
	constant BLUE  : std_logic_vector (8 downto 0) := "000011111";
	constant YELLOW  : std_logic_vector (8 downto 0) := "111111000";
	constant WHITE  : std_logic_vector (8 downto 0) := "111111111";
	
begin
	col_aux <= conv_integer(vga_col(3 downto 0));
	row_aux <= conv_integer(vga_row(3 downto 0));   
    score_number_1 <= SCORE(conv_integer(vga_number1) * 16 + row_aux)(col_aux);
    score_number_2 <= SCORE(conv_integer(vga_number2) * 16 + row_aux)(col_aux);
    score_number_3 <= SCORE(conv_integer(vga_number3) * 16 + row_aux)(col_aux);
    vga_rgb <= 
        RED 	when vga_cursor(0) = '1' and vga_row(11 downto 4) = "00000101" and vga_col(11 downto 4) = "00001001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(0) = '1' and vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED 	when vga_cursor(1) = '1' and vga_row(11 downto 4) = "00000101" and vga_col(11 downto 4) = "00001101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(1) = '1' and vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED 	when vga_cursor(2) = '1' and vga_row(11 downto 4) = "00000101" and vga_col(11 downto 4) = "00010001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(2) = '1' and vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(3) = '1' and vga_row(11 downto 4) = "00000101" and vga_col(11 downto 4) = "00010101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(3) = '1' and vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(4) = '1' and vga_row(11 downto 4) = "00000101" and vga_col(11 downto 4) = "00011001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(4) = '1' and vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000001" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(5) = '1' and vga_row(11 downto 4) = "00001001" and vga_col(11 downto 4) = "00001001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(5) = '1' and vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(6) = '1' and vga_row(11 downto 4) = "00001001" and vga_col(11 downto 4) = "00001101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(6) = '1' and vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(7) = '1' and vga_row(11 downto 4) = "00001001" and vga_col(11 downto 4) = "00010001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(7) = '1' and vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(8) = '1' and vga_row(11 downto 4) = "00001001" and vga_col(11 downto 4) = "00010101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(8) = '1' and vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(9) = '1' and vga_row(11 downto 4) = "00001001" and vga_col(11 downto 4) = "00011001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(9) = '1' and vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000010" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(10) = '1' and vga_row(11 downto 4) = "00001101" and vga_col(11 downto 4) = "00001001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(10) = '1' and vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(11) = '1' and vga_row(11 downto 4) = "00001101" and vga_col(11 downto 4) = "00001101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(11) = '1' and vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(12) = '1' and vga_row(11 downto 4) = "00001101" and vga_col(11 downto 4) = "00010001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(12) = '1' and vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(13) = '1' and vga_row(11 downto 4) = "00001101" and vga_col(11 downto 4) = "00010101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(13) = '1' and vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(14) = '1' and vga_row(11 downto 4) = "00001101" and vga_col(11 downto 4) = "00011001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(14) = '1' and vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000011" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(15) = '1' and vga_row(11 downto 4) = "00010001" and vga_col(11 downto 4) = "00001001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(15) = '1' and vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(16) = '1' and vga_row(11 downto 4) = "00010001" and vga_col(11 downto 4) = "00001101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(16) = '1' and vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(17) = '1' and vga_row(11 downto 4) = "00010001" and vga_col(11 downto 4) = "00010001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(17) = '1' and vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(18) = '1' and vga_row(11 downto 4) = "00010001" and vga_col(11 downto 4) = "00010101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(18) = '1' and vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(19) = '1' and vga_row(11 downto 4) = "00010001" and vga_col(11 downto 4) = "00011001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(19) = '1' and vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000100" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(20) = '1' and vga_row(11 downto 4) = "00010101" and vga_col(11 downto 4) = "00001001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(20) = '1' and vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000010" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(21) = '1' and vga_row(11 downto 4) = "00010101" and vga_col(11 downto 4) = "00001101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(21) = '1' and vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000011" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(22) = '1' and vga_row(11 downto 4) = "00010101" and vga_col(11 downto 4) = "00010001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(22) = '1' and vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000100" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(23) = '1' and vga_row(11 downto 4) = "00010101" and vga_col(11 downto 4) = "00010101" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(23) = '1' and vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000101" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        RED   	when vga_cursor(24) = '1' and vga_row(11 downto 4) = "00010101" and vga_col(11 downto 4) = "00011001" and vga_col(3 downto 0) /= "1111" and vga_row(3 downto 0) /= "1111" else
        BLUE  	when vga_cells_ON(24) = '1' and vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111" else
        YELLOW  when vga_row(11 downto 6) = "000101" and vga_col(11 downto 6) = "000110" and vga_col(5 downto 1) /= "11111" and vga_row(5 downto 1) /= "11111"  else
        WHITE 	when score_number_1 = '1' and (vga_col(11 downto 4) = "00010010") and (vga_row(11 downto 4) = "00011000") else
        WHITE 	when score_number_2 = '1' and (vga_col(11 downto 4) = "00010001") and (vga_row(11 downto 4) = "00011000") else
        WHITE 	when score_number_3 = '1' and (vga_col(11 downto 4) = "00010000") and (vga_row(11 downto 4) = "00011000") else "000000000";
end Behavioral;
