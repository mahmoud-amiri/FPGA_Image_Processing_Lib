
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity selector is
    port (
        iSwitch              : in std_logic;
        iClk                 : in std_logic;
        s_axi_streamA_tdata  : in std_logic_vector(15 downto 0);
        s_axi_streamA_tready : out std_logic;
        s_axi_streamA_tvalid : in std_logic;
        s_axi_streamA_tuser  : in std_logic;
        s_axi_streamA_tlast  : in std_logic;
        s_axi_streamB_tdata  : in std_logic_vector(15 downto 0);
        s_axi_streamB_tready : out std_logic;
        s_axi_streamB_tvalid : in std_logic;
        s_axi_streamB_tuser  : in std_logic;
        s_axi_streamB_tlast  : in std_logic;
        m_axi_tdata          : out std_logic_vector(15 downto 0);
        m_axi_tready         : in std_logic;
        m_axi_tvalid         : out std_logic;
        m_axi_tuser          : out std_logic;
        m_axi_tlast          : out std_logic
    );
end selector;

architecture Behavioral of selector is
    signal sSwitch : std_logic := '0';
begin
    m_axi_tdata          <= s_axi_streamA_tdata when (iSwitch = '0') else s_axi_streamB_tdata;
    s_axi_streamA_tready <= m_axi_tready;
    s_axi_streamB_tready <= m_axi_tready;
    m_axi_tvalid         <= s_axi_streamA_tvalid when (iSwitch = '0') else s_axi_streamB_tvalid;
    m_axi_tuser          <= s_axi_streamA_tuser when (iSwitch = '0') else s_axi_streamB_tuser;
    m_axi_tlast          <= s_axi_streamA_tlast when (iSwitch = '0') else s_axi_streamB_tlast;
end Behavioral;