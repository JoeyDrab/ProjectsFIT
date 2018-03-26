-- cpu.vhd: Simple 8-bit CPU (BrainLove interpreter)
-- Copyright (C) 2017 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Jozef Drab <xdrabj00>
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
 port (
   CLK   : in std_logic;  -- hodinovy signal
   RESET : in std_logic;  -- asynchronni reset procesoru
   EN    : in std_logic;  -- povoleni cinnosti procesoru
 
   -- synchronni pamet ROM
   CODE_ADDR : out std_logic_vector(11 downto 0); -- adresa do pameti
   CODE_DATA : in std_logic_vector(7 downto 0);   -- CODE_DATA <- rom[CODE_ADDR] pokud CODE_EN='1'
   CODE_EN   : out std_logic;                     -- povoleni cinnosti
   
   -- synchronni pamet RAM
   DATA_ADDR  : out std_logic_vector(9 downto 0); -- adresa do pameti
   DATA_WDATA : out std_logic_vector(7 downto 0); -- mem[DATA_ADDR] <- DATA_WDATA pokud DATA_EN='1'
   DATA_RDATA : in std_logic_vector(7 downto 0);  -- DATA_RDATA <- ram[DATA_ADDR] pokud DATA_EN='1'
   DATA_RDWR  : out std_logic;                    -- cteni z pameti (DATA_RDWR='0') / zapis do pameti (DATA_RDWR='1')
   DATA_EN    : out std_logic;                    -- povoleni cinnosti
   
   -- vstupni port
   IN_DATA   : in std_logic_vector(7 downto 0);   -- IN_DATA obsahuje stisknuty znak klavesnice pokud IN_VLD='1' a IN_REQ='1'
   IN_VLD    : in std_logic;                      -- data platna pokud IN_VLD='1'
   IN_REQ    : out std_logic;                     -- pozadavek na vstup dat z klavesnice
   
   -- vystupni port
   OUT_DATA : out  std_logic_vector(7 downto 0);  -- zapisovana data
   OUT_BUSY : in std_logic;                       -- pokud OUT_BUSY='1', LCD je zaneprazdnen, nelze zapisovat,  OUT_WE musi byt '0'
   OUT_WE   : out std_logic                       -- LCD <- OUT_DATA pokud OUT_WE='1' a OUT_BUSY='0'
 );
end cpu;


-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is

 -- zde dopiste potrebne deklarace signalu
	type all_cpu_states is ( 
						  state_final,
						  state_start,
						  state_fetch,
						  state_decode,
						  state_load_inc_data,
						  state_load_dec_data,
						  state_insert_inc_data,
						  state_insert_dec_data,
						  state_key_load,
						  state_load_left,
						  state_load_right,
						  state_while_stat,
						  state_while_stat_end,
						  state_while_stat2,
						  state_while_loop_end,
						  state_while_loop_end2,
						  state_end,
						  state_inc_ptr,
						  state_dec_ptr,
						  state_inc_data,
						  state_dec_data,
						  state_data_null,
						  state_data_unnull,
						  state_print_data,
						  state_load_data_save,
						  state_finish_loop
						  );
	
	signal act_state: all_cpu_states;
	signal next_state: all_cpu_states;
	-------------------------------------------------------------------------
	--instructions
	signal inc_pc: std_logic := '0';
	signal dec_pc: std_logic := '0';
	signal pc_instruct: std_logic_vector(11 downto 0):= (others => '0');
	
	--data
	signal inc_data: std_logic := '0';
	signal dec_data: std_logic := '0';
	signal inc_pointer: std_logic := '0';
	signal dec_pointer: std_logic := '0';
	signal data_load: std_logic := '0';
	signal data_put: std_logic := '0';
	signal pointer_data: std_logic_vector(9 downto 0):= (others => '0');
	
	-- ignore loop
	signal ignore_inc_loop: std_logic := '0';
	signal ignore_dec_loop: std_logic := '0';
	signal ignore_inc_loop_end: std_logic := '0';
	signal ignore_dec_loop_end: std_logic := '0';
	signal do_while_loop: std_logic_vector(7 downto 0) := (others => '0');
	signal do_not_while_loop: std_logic_vector(7 downto 0) := (others => '0');
	
	 ------------------------------------------

begin

 -- zde dopiste vlastni VHDL kod
automat_work : process(CLK, act_state, OUT_BUSY, DATA_RDATA, IN_VLD, CODE_DATA, do_not_while_loop, do_while_loop)
	begin
	DATA_EN <= '0';                    -- povoleni cinnosti
	CODE_EN <= '0';                    -- povoleni cinnosti
	IN_REQ  <= '0';                    -- pozadavek na vstup dat z klavesnice
	DATA_RDWR <= '0';                  -- cteni z pameti (DATA_RDWR='0') / zapis do pameti (DATA_RDWR='1')
	
	inc_data <= '0';
	dec_data <= '0';
	inc_pc <= '0';
	dec_pc <= '0'; 
	inc_pointer <= '0';
	dec_pointer <= '0';
	data_load <= '0';
	ignore_inc_loop <= '0';
	ignore_dec_loop <= '0';
	ignore_inc_loop_end <= '0';
	ignore_dec_loop_end <= '0';
	data_put <= '0';
	
		next_state <= state_start;
		case act_state is
			
			when state_start => 
				CODE_EN <= '1';
				next_state <= state_fetch;
			------------------------------------	
			when state_fetch =>
				if do_not_while_loop /= "00000000" then		
					if CODE_DATA = X"5B" then 
						if do_not_while_loop /= "0000001" then
							next_state <= state_load_left;
						else  
							next_state <= state_load_right;
						end if;
						ignore_dec_loop_end <= '1';
					elsif CODE_DATA = X"5D" then 
						ignore_inc_loop_end <= '1';
						next_state <= state_load_left;	
					else
						next_state <= state_load_left;
					end if;
				----------------------------------------
				elsif do_while_loop /= "00000000" then				
					if CODE_DATA = X"5B" then 
						ignore_inc_loop <= '1';
					elsif CODE_DATA = X"5D" then 
						ignore_dec_loop <= '1';
					end if;
					next_state <= state_load_right;
				----------------------------------------					
				else	
					case CODE_DATA is
						-- >
						when X"3E" =>
							next_state <= state_inc_ptr;
						-- <	
						when X"3C" =>
							next_state <= state_dec_ptr;
						-- +	
						when X"2B" =>
							next_state <= state_inc_data;
						-- -
						when X"2D" =>
							next_state <= state_dec_data;
						-- [
						when X"5B" =>
							next_state <= state_data_null;
						-- ]
						when X"5D" =>
							next_state <= state_data_unnull;
						-- .
						when X"2E" =>
							next_state <= state_print_data;
						-- ,
						when X"2C" =>
							next_state <= state_load_data_save;
						-- ~
						when X"7E" =>
							next_state <= state_finish_loop;
						-- NULL
						when X"00" =>
							next_state <= state_end;
							
						when others =>
							next_state <= state_load_right;
							
					end case;			
				end if;	
			------------------------------------
			when state_inc_ptr =>
				inc_pointer <= '1';
				next_state <= state_load_right;
			------------------------------------
			when state_dec_ptr =>
				dec_pointer <= '1';
				next_state <= state_load_right;
			------------------------------------
			when state_inc_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				next_state <= state_load_inc_data;
			------------------------------------
			when state_dec_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				next_state <= state_load_dec_data;
			------------------------------------
			when state_data_null =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				next_state <= state_while_stat;
			------------------------------------
			when state_data_unnull =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				next_state <= state_while_stat_end;
			------------------------------------
			when state_print_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				next_state <= state_print_data;
				if OUT_BUSY = '0' then 
					next_state <= state_load_right;
					data_put <= '1';
				end if;
			------------------------------------
			when state_load_data_save =>
				IN_REQ <= '1';
				next_state <= state_load_data_save;
				if IN_VLD = '1' then 
					IN_REQ <= '0';
					data_load <= '1';
					next_state <= state_key_load;
				end if;

			------------------------------------
			when state_finish_loop =>
				next_state <= state_while_loop_end;
			-----------------------------------------
				--next_state <= state_decode;
			
			-----------------------------------------
			when state_load_inc_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				inc_data <= '1';
				next_state <= state_insert_inc_data;
			------------------------------------
			when state_load_dec_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				dec_data <= '1';
				next_state <= state_insert_dec_data;
			------------------------------------
			when state_insert_inc_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				inc_data <= '1';
				next_state <= state_load_right;
			------------------------------------
			when state_insert_dec_data =>
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				dec_data <= '1';
				next_state <= state_load_right;
			------------------------------------
			when state_key_load => 
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				next_state <= state_load_right;
			------------------------------------
			when state_load_left =>
				dec_pc <= '1';
				next_state <= state_start;
			------------------------------------
			when state_load_right =>
				inc_pc <= '1';
				next_state <= state_start;
			------------------------------------
			when state_while_stat =>
				next_state <= state_while_stat2;
			------------------------------------
			when state_while_stat_end =>
				next_state <= state_while_loop_end;
			------------------------------------
			-- start loop
			when state_while_stat2 =>
				-- jump loop
				if DATA_RDATA = "00000000" then 
					ignore_inc_loop <= '1';
				end if;
				next_state <= state_load_right;
			------------------------------------
			-- end loop
			when state_while_loop_end =>
				if DATA_RDATA = "00000000" then
					next_state <= state_load_right;
				else
					ignore_inc_loop_end <= '1';
					next_state <= state_load_left; 							
				end if;
			------------------------------------
			when state_end =>
				next_state <= state_final;
			------------------------------------	
			when state_final =>
				next_state <= state_final;
			------------------------------------	
			when others => null;
			------------------------------------
		end case;
	end process;
	
cpu_work : process( CLK, RESET,next_state, EN, IN_DATA, DATA_RDATA, inc_data, dec_data, data_put, data_load)
begin
		-- anulacia RESET
	if(RESET = '1') then
		act_state <= state_start;
	elsif (CLK'event) and (CLK = '1') then
		if(EN = '1') then
            act_state <= next_state;
        end if;
		-------------------------------------------------------
		OUT_WE <= '0';
		if inc_data = '1' then 
			DATA_WDATA <= DATA_RDATA + 1;
		elsif dec_data = '1' then
			DATA_WDATA <= DATA_RDATA - 1;
		elsif data_put = '1' then
			OUT_DATA <= DATA_RDATA;
			OUT_WE <= '1';
		elsif data_load = '1' then
			DATA_WDATA <= IN_DATA;
		end if;
		-------------------------------------------------------
	end if;
end process;

instruct_and_data: process (RESET, CLK, pc_instruct, pointer_data, inc_pointer, dec_pointer, inc_pc, dec_pc) 
	begin
		if RESET = '1' then
			pointer_data <= (others => '0');
			pc_instruct  <= (others => '0');
			CODE_ADDR <= (others => '0');
		-------------------------------------------------------
		elsif (CLK'event) and (CLK = '1') then
			-- Posun Dat
			if (inc_pointer = '1') then
				pointer_data <= pointer_data + 1;
				DATA_ADDR <= pointer_data + 1;
			elsif (dec_pointer = '1') then
				pointer_data <= pointer_data - 1;
				DATA_ADDR <= pointer_data - 1;
			end if;
        -------------------------------------------------------
			--Posun Instrukcie
			if (inc_pc = '1') then
				pc_instruct <= pc_instruct + 1 ;
				CODE_ADDR <= pc_instruct + 1;
			elsif (dec_pc = '1') then
				pc_instruct <= pc_instruct - 1;
				CODE_ADDR <= pc_instruct - 1;
			end if;
		-------------------------------------------------------
		end if;
end process;

jump_loop: process(CLK, RESET, ignore_inc_loop, ignore_dec_loop, ignore_inc_loop_end, do_not_while_loop) 
	begin
		if RESET = '1' then
			do_while_loop <= "00000000";
			do_not_while_loop <= "00000000";
		elsif (CLK'event) and (CLK = '1') then
			if ignore_inc_loop = '1' then
				do_while_loop <= do_while_loop + '1';
			elsif ignore_dec_loop = '1' then
				do_while_loop <= do_while_loop - '1';
			end if;
			-------------------------------------------------------
			if ignore_inc_loop_end = '1' then
				do_not_while_loop <= do_not_while_loop + '1';
			elsif ignore_dec_loop_end = '1' then
				do_not_while_loop <= do_not_while_loop - '1';
			end if;
		end if;
end process;
	
end behavioral;
 
