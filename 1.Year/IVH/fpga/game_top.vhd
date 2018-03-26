----------------------------------------------------------------------------------
--																				 |
--Autor: 		Jozef Dráb	xdrabj00@fit.vutbr.cz								 |
--Datum: 		17.03.2017														 |
--Názov súboru: 	lightsout_pack.vhdl 										 |
--																				 |
----------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use work.vga_controller_cfg.all;
use work.clkgen_cfg.all;
use work.lightsout_pack.all;

architecture Behavioral of tlv_pc_ifc is
	signal top_clk : std_logic;
	signal top_number1 : std_logic_vector(3 downto 0);
	signal top_number2 :  std_logic_vector(3 downto 0);
	signal top_number3 :  std_logic_vector(3 downto 0);
	signal top_loaded_Map :  std_logic_vector (24 downto 0) := (others => '0');
	signal vga_col : std_logic_vector(11 downto 0);
	signal vga_mode  : std_logic_vector(60 downto 0); 
	signal vga_rgb : std_logic_vector(8 downto 0);
	signal vga_row : std_logic_vector(11 downto 0);
	signal kbrd_data_out : std_logic_vector(15 downto 0);
	signal kbrd_data_vld : std_logic;
	signal keys :  std_logic_vector(4 downto 0);
	signal top_cursor :  std_logic_vector(24 downto 0);
	signal top_cells_ON :  std_logic_vector(24 downto 0);
	signal top_reset : std_logic := '1';
	constant CONST_TOP    : NATURAL := 0; 
	constant CONST_LEFT   : NATURAL := 1;
	constant CONST_RIGHT  : NATURAL := 2; 
	constant CONST_BOTTOM : NATURAL := 3; 
	constant CONST_ENTER  : NATURAL := 4; 
	
begin
	-- ----------------------------------------------------------
	-- ------------- GLOBAL MODULES -----------------------------
	-- ----------------------------------------------------------

	-- VGA controller, delay 1 tact
	vga: entity work.vga_controller(arch_vga_controller) 
	generic map (REQ_DELAY => 1)
	port map (
		CLK    => CLK, 
		RST    => RESET,
		ENABLE => '1',
		MODE   => vga_mode,
	
		DATA_RED    => vga_rgb(8 downto 6),
		DATA_GREEN  => vga_rgb(5 downto 3),
		DATA_BLUE   => vga_rgb(2 downto 0),
		ADDR_COLUMN => vga_col,
		ADDR_ROW    => vga_row,
	
		VGA_RED   => RED_V,
		VGA_BLUE  => BLUE_V,
		VGA_GREEN => GREEN_V,
		VGA_HSYNC => HSYNC_V,
		VGA_VSYNC => VSYNC_V
	);
	-- Set graphical mode (640x480, 60 Hz refresh)
	setmode(r640x480x60, vga_mode);
	
	kbrd_ctrl: entity work.keyboard_controller(arch_keyboard)
	port map (
		CLK => SMCLK,
		RST => RESET,
	
		DATA_OUT => kbrd_data_out(15 downto 0),
		DATA_VLD => kbrd_data_vld,
		
		KB_KIN   => KIN,
		KB_KOUT  => KOUT
	);
		
	game_bcd: entity work.bcd 
	port map( 
		CLK => top_clk,
		RESET => top_reset,
		NUMBER1 => top_number1,
		NUMBER2 => top_number2,
		NUMBER3 => top_number3
	);
	
	cell_generator: entity work.cell_generator
	port map( 
		cell_gen_cursor => top_cursor,
		cell_gen_cells_ON => top_cells_ON,
		cell_gen_cells => top_loaded_Map,
		cell_gen_clk => CLK,
		cell_gen_reset => top_reset,
		cell_gen_key => keys
	);
	
	game_vga: entity work.vga 
	port map ( 
		vga_rgb => vga_rgb,
		vga_row => vga_row,
		vga_col => vga_col,
		vga_cells_ON => top_cursor,
		vga_cursor => top_cells_ON,
		vga_number1 => top_number1,
		vga_number2 => top_number2,
		vga_number3 => top_number3
	);

	-- cursor controller, move to CLK
	cursor: process
	variable in_access : std_logic := '0';
	begin		
		if CLK'event and CLK='1' then
			keys <= (others => '0'); 
			top_reset <= '0'; 
			top_clk <= '0';
			
			if in_access='0' then
				if kbrd_data_vld='1' then 
					in_access:='1';
					if kbrd_data_out(9)='1'then  -- 2
						keys <= (CONST_RIGHT => '1', others => '0');
					elsif kbrd_data_out(4)='1' then  -- 6
						keys <= (CONST_TOP => '1', others => '0');
					elsif kbrd_data_out(6)='1' then  -- 4
						keys <= (CONST_BOTTOM => '1', others => '0');
					elsif kbrd_data_out(1)='1'then  -- 8
						keys <= (CONST_LEFT => '1', others => '0');										
					elsif kbrd_data_out(5)='1' then   -- 5
						keys <= (CONST_ENTER => '1', others => '0');
						top_clk <= '1';
					
					elsif kbrd_data_out(12)='1' then   -- A
						top_reset <= '1';
						top_loaded_Map <= "0010001010100010101000100";
					elsif kbrd_data_out(13)='1' then   -- B
						top_reset <= '1';
						top_loaded_Map <= "0101001010101010010010101";
					elsif kbrd_data_out(15)='1' then   -- D
						top_reset <= '1';
						top_loaded_Map <= "0000000000000000000000000";				
					end if;
				end if;
			elsif kbrd_data_vld='0' then
				in_access:='0';
			end if;
		end if;																						
	end process;  
end Behavioral;
