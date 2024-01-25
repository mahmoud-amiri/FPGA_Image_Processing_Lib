----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/22/2021 09:48:45 AM
-- Design Name: 
-- Module Name: chromaResampler - arch
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

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity chromaResampler is
    Port ( iClk                     : in STD_LOGIC;
           s_axis_tdata             : in STD_LOGIC_VECTOR (15 downto 0);
           s_axis_tvalid            : in STD_LOGIC;
           s_axis_tready            : out STD_LOGIC;
           s_axis_tlast             : in STD_LOGIC;
           s_axis_tuser             : in STD_LOGIC;
           m_axis_tdata             : out STD_LOGIC_VECTOR (23 downto 0);
           m_axis_tvalid            : out STD_LOGIC;
           m_axis_tready            : in STD_LOGIC;
           m_axis_tlast             : out STD_LOGIC;
           m_axis_tuser             : out STD_LOGIC);
end chromaResampler;

architecture arch of chromaResampler is
signal Y1           : std_logic_vector(7 downto 0);
signal Y1_r         : std_logic_vector(7 downto 0);
signal Y2           : std_logic_vector(7 downto 0);
signal Cb           : std_logic_vector(7 downto 0);
signal Cb_r         : std_logic_vector(7 downto 0);
signal Cr           : std_logic_vector(7 downto 0);
signal state        : std_logic := '0';
signal state_r      : std_logic := '0';
signal state_r2     : std_logic := '0';
signal valid_out    : std_logic;
signal valid_out_r  : std_logic;
signal tlast_r      : std_logic;
signal tlast_r2     : std_logic;
signal tuser_r      : std_logic;
signal tuser_r2     : std_logic;

begin

s_axis_tready       <= m_axis_tready;

process(iClk) 
begin
if (rising_edge(iClk)) then
    if(s_axis_tvalid = '1') then

        if(state = '0') then
            Y1 <= s_axis_tdata(7 downto 0);
            Cb <= s_axis_tdata(15 downto 8);
        else
            Y2 <= s_axis_tdata(7 downto 0);
            Cr <= s_axis_tdata(15 downto 8);
        end if;
        state <= not state;
        if (s_axis_tlast = '1') then
            state <= '0';
        end if;
    end if;
    state_r         <= state;
    state_r2        <= state_r;
    Y1_r            <= Y1;
    Cb_r            <= Cb;

    if (state_r2 = '0') then
        m_axis_tdata(7 downto 0)        <= Y1_r;
        -- m_axis_tdata(15 downto 8)       <= Cb_r;
        -- m_axis_tdata(23 downto 16)      <= Cr;
        m_axis_tdata(15 downto 8)       <= Cr;
        m_axis_tdata(23 downto 16)      <= Cb_r;
    else
        m_axis_tdata(7 downto 0)        <= Y2;
        -- m_axis_tdata(15 downto 8)       <= Cb_r;
        -- m_axis_tdata(23 downto 16)      <= Cr;
        m_axis_tdata(15 downto 8)       <= Cr;
        m_axis_tdata(23 downto 16)      <= Cb_r;
    end if;

    valid_out       <= s_axis_tvalid;
    valid_out_r     <= valid_out;
    m_axis_tvalid   <= valid_out_r;
    tlast_r         <= s_axis_tlast;
    tlast_r2        <= tlast_r;
    m_axis_tlast    <= tlast_r2;
    tuser_r         <= s_axis_tuser;
    tuser_r2        <= tuser_r;
    m_axis_tuser    <= tuser_r2;
end if;
end process;


end arch;
