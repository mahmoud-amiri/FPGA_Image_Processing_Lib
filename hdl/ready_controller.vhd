

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity ready_controller is
    Port ( 
            s_axis_tdata             : in STD_LOGIC_VECTOR (15 downto 0);
            s_axis_tvalid            : in STD_LOGIC;
            s_axis_tready            : out STD_LOGIC;
            s_axis_tlast             : in STD_LOGIC;
            s_axis_tuser             : in STD_LOGIC;
            m_axis_tdata             : out STD_LOGIC_VECTOR (15 downto 0);
            m_axis_tvalid            : out STD_LOGIC;
            m_axis_tready            : in STD_LOGIC;
            m_axis_tlast             : out STD_LOGIC;
            m_axis_tuser             : out STD_LOGIC;
            fake_ready               : in STD_LOGIC   
            );
end ready_controller;

architecture arch of ready_controller is
    signal s_width                  : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_height                 : std_logic_vector(11 downto 0):=(others=>'0');
    signal x_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
    signal y_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_x                      : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_y                      : std_logic_vector(11 downto 0):=(others=>'0');
begin

    s_axis_tready       <= m_axis_tready or fake_ready;
    m_axis_tuser        <= s_axis_tuser;
    m_axis_tlast        <= s_axis_tlast;
    m_axis_tvalid       <= s_axis_tvalid;
    m_axis_tdata        <= s_axis_tdata;

end arch;
