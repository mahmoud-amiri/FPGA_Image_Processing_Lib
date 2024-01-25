----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/24/2021 05:20:01 PM
-- Design Name: 
-- Module Name: slice32to24 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity extend24to32 is
  Port ( 
    s_axi_tdata     :in std_logic_vector(23 downto 0);
    s_axi_tready    :out std_logic;
    s_axi_tvalid    :in std_logic;
    s_axi_tuser     :in std_logic;
    s_axi_tlast     :in std_logic;
    m_axi_tdata     :out std_logic_vector(31 downto 0);
    m_axi_tready    :in std_logic;
    m_axi_tvalid    :out std_logic;
    m_axi_tuser     :out std_logic;
    m_axi_tlast     :out std_logic
  );
end extend24to32;

architecture Behavioral of extend24to32 is

begin
    m_axi_tdata     <= X"00" & s_axi_tdata;
    s_axi_tready    <= m_axi_tready;
    m_axi_tvalid    <= s_axi_tvalid;
    m_axi_tuser     <= s_axi_tuser;
    m_axi_tlast     <= s_axi_tlast;
end Behavioral;
