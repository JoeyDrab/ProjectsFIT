-- fsm.vhd: Finite State Machine
-- Author(s): Jozef Drab (xdrabj00)
-- kod1 = 6904103968
-- kod2 = 2301367989

library ieee;
use ieee.std_logic_1164.all;
-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity fsm is
port(
   CLK         : in  std_logic;
   RESET       : in  std_logic;

   -- Input signals
   KEY         : in  std_logic_vector(15 downto 0);
   CNT_OF      : in  std_logic;

   -- Output signals
   FSM_CNT_CE  : out std_logic;
   FSM_MX_MEM  : out std_logic;
   FSM_MX_LCD  : out std_logic;
   FSM_LCD_WR  : out std_logic;
   FSM_LCD_CLR : out std_logic
);
end entity fsm;

-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of fsm is
   type t_state is (WAIT1, CRASH, TEST1, TEST2a, TEST2b, TEST3a, TEST3b, TEST4a, TEST4b, TEST5a, TEST5b, TEST6a, TEST6b,
					 TEST7a, TEST7b, TEST8a, TEST8b, TEST9a, TEST9b, TEST10a, TEST10b, TEST11, PRINT_MESSAGE, PRINT_CRASH, FINISH);
   signal present_state, next_state : t_state;

begin
-- -------------------------------------------------------
sync_logic : process(RESET, CLK)
begin
   if (RESET = '1') then
      present_state <= TEST1;
   elsif (CLK'event AND CLK = '1') then
      present_state <= next_state;
   end if;
end process sync_logic;

-- -------------------------------------------------------
next_state_logic : process(present_state, KEY, CNT_OF)
begin
   case (present_state) is
      -- - - - - - - - - - - - - - - - - - - - - - -
   when WAIT1 =>
      next_state <= TEST1;
   -- - - - - - - - - - - - - - - - - - - - - - -
    when CRASH =>
      next_state <= CRASH;
      if (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      end if;
	--------------------------------------------  
   when TEST1 =>
      next_state <= TEST1;
      if (KEY(6) = '1') then
         next_state <= TEST2a;
	  elsif (KEY(2) = '1') then
         next_state <= TEST2b;	 
		 
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
   when TEST2a =>
      next_state <= TEST2a;
      if (KEY(9) = '1') then
         next_state <= TEST3a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
   when TEST2b =>
      next_state <= TEST2b;
      if (KEY(3) = '1') then
         next_state <= TEST3b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST3a =>
      next_state <= TEST3a;
      if (KEY(0) = '1') then
         next_state <= TEST4a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST3b =>
      next_state <= TEST3b;
      if (KEY(0) = '1') then
         next_state <= TEST4b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST4a =>
      next_state <= TEST4a;
      if (KEY(4) = '1') then
         next_state <= TEST5a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST4b =>
      next_state <= TEST4b;
      if (KEY(1) = '1') then
         next_state <= TEST5b;	 
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST5a =>
      next_state <= TEST5a;
      if (KEY(1) = '1') then
         next_state <= TEST6a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST5b =>
      next_state <= TEST5b;
      if (KEY(3) = '1') then
         next_state <= TEST6b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST6a =>
      next_state <= TEST6a;
      if (KEY(0) = '1') then
         next_state <= TEST7a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if;
   ----------------------------
    when TEST6b =>
      next_state <= TEST6b;
      if (KEY(6) = '1') then
         next_state <= TEST7b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST7a =>
      next_state <= TEST7a;
      if (KEY(3) = '1') then
         next_state <= TEST8a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST7b =>
      next_state <= TEST7b;
      if (KEY(7) = '1') then
         next_state <= TEST8b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST8a =>
      next_state <= TEST8a;
      if (KEY(9) = '1') then
         next_state <= TEST9a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST8b =>
      next_state <= TEST8b;
      if (KEY(9) = '1') then
         next_state <= TEST9b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST9a =>
      next_state <= TEST9a;
      if (KEY(6) = '1') then
         next_state <= TEST10a;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST9b =>
      next_state <= TEST9b;
      if (KEY(8) = '1') then
         next_state <= TEST10b;
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST10a =>
      next_state <= TEST10a;
      if (KEY(8) = '1') then
         next_state <= TEST11;
		 
      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST10b =>
      next_state <= TEST10b;
      if (KEY(9) = '1') then
         next_state <= TEST11;

      elsif (KEY(15) = '1') then
         next_state <= PRINT_CRASH;
      elsif (KEY(15 downto 0) /= "0000000000000000") then
         next_state <= CRASH;
      end if; 
	----------------------------
	when TEST11 =>
		next_state <= TEST11;
		if (KEY(15) = '1') then
         next_state <= PRINT_MESSAGE;
		end if; 
	   -- - - - - - - - - - - - - - - - - - - - - - -
    when PRINT_CRASH =>
      next_state <= PRINT_CRASH;
      if (CNT_OF = '1') then
         next_state <= FINISH;
      end if;
	------------------------------------
   when PRINT_MESSAGE =>
      next_state <= PRINT_MESSAGE;
      if (CNT_OF = '1') then
         next_state <= FINISH;
      end if;
   -------------------------------------
   when FINISH =>
      next_state <= FINISH;
      if (KEY(15) = '1') then
         next_state <= TEST1; 
      end if;
   ------------------------------------
   when others =>
      next_state <= WAIT1;
   end case;
end process next_state_logic;

-- -------------------------------------------------------
output_logic : process(present_state, KEY)
begin
   FSM_CNT_CE     <= '0';
   FSM_MX_MEM     <= '0';
   FSM_MX_LCD     <= '0';
   FSM_LCD_WR     <= '0';
   FSM_LCD_CLR    <= '0';

   case (present_state) is

   -- - - - - - - - - - - - - - - - - - - - - - -
   when PRINT_CRASH =>
      FSM_CNT_CE     <= '1';
      FSM_MX_LCD     <= '1';
      FSM_MX_MEM     <= '0';
      FSM_LCD_WR     <= '1';
   -- - - - - - - - - - - - - - - - - - - - - - -
   when PRINT_MESSAGE =>
      FSM_CNT_CE     <= '1';
      FSM_MX_LCD     <= '1';
	  FSM_MX_MEM     <= '1';
      FSM_LCD_WR     <= '1';
   -- - - - - - - - - - - - - - - - - - - - - - -
   when FINISH =>
      if (KEY(15) = '1') then
         FSM_LCD_CLR    <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when others =>
	if (KEY(14 downto 0) /= "000000000000000") then
         FSM_LCD_WR     <= '1';
      end if;
      if (KEY(15) = '1') then
         FSM_LCD_CLR    <= '1';
      end if;
   end case;
end process output_logic;

end architecture behavioral;

