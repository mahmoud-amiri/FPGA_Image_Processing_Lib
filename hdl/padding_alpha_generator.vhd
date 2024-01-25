
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity padding_alpha_generator is
  port (
    s_axi_tdata  : in std_logic_vector(23 downto 0);
    s_axi_tready : out std_logic;
    s_axi_tvalid : in std_logic;
    s_axi_tuser  : in std_logic;
    s_axi_tlast  : in std_logic;
    m_axi_tdata  : out std_logic_vector(31 downto 0);
    m_axi_tready : in std_logic;
    m_axi_tvalid : out std_logic;
    m_axi_tuser  : out std_logic;
    m_axi_tlast  : out std_logic;
    iClk         : in std_logic;
    x1           : in std_logic_vector(11 downto 0);
    x2           : in std_logic_vector(11 downto 0);
    y1           : in std_logic_vector(11 downto 0);
    y2           : in std_logic_vector(11 downto 0)
  );
end padding_alpha_generator;

architecture arch of padding_alpha_generator is
  signal xCntr    : std_logic_vector(11 downto 0) := X"000";
  signal yCntr    : std_logic_vector(11 downto 0) := X"000";
  signal xOpacity : std_logic;
  signal yOpacity : std_logic;
  signal opacity  : std_logic_vector(7 downto 0);
begin
  process (iClk)
  begin
    if (rising_edge(iClk)) then
      if (m_axi_tready = '1' and s_axi_tvalid = '1') then
        xCntr <= xCntr + '1';
        if (xCntr < x1) then
          xOpacity <= '0';
        elsif (xCntr < x2) then
          xOpacity <= '1';
        else
          xOpacity <= '0';
        end if;

        if (yCntr < y1) then
          yOpacity <= '0';
        elsif (yCntr < y2) then
          yOpacity <= '1';
        else
          yOpacity <= '0';
        end if;
      end if;

      if (s_axi_tlast = '1') then
        xCntr <= (others => '0');
        yCntr <= yCntr + '1';
      end if;

      if (s_axi_tuser = '1') then
        yCntr <= (others => '0');
      end if;
    end if;

  end process;
  opacity <= X"FF" when ((xOpacity and yOpacity) = '1') else X"00";

  m_axi_tdata  <= opacity & s_axi_tdata;
  s_axi_tready <= m_axi_tready;
  m_axi_tvalid <= s_axi_tvalid;
  m_axi_tuser  <= s_axi_tuser;
  m_axi_tlast  <= s_axi_tlast;
end arch;