

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity crop is
    Port ( 
            clk                      : in STD_LOGIC;
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
            m_axis_croped_tdata      : out STD_LOGIC_VECTOR (15 downto 0);
            m_axis_croped_tvalid     : out STD_LOGIC;
            m_axis_croped_tready     : in STD_LOGIC;
            m_axis_croped_tlast      : out STD_LOGIC;
            m_axis_croped_tuser      : out STD_LOGIC;
            x                        : in std_logic_vector(11 downto 0);
            y                        : in std_logic_vector(11 downto 0);
            width                    : in std_logic_vector(11 downto 0);
            height                   : in std_logic_vector(11 downto 0);
            xCntr                    : out std_logic_vector(11 downto 0);
            yCntr                    : out std_logic_vector(11 downto 0)
            );
end crop;

architecture arch of crop is
    signal s_width                  : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_height                 : std_logic_vector(11 downto 0):=(others=>'0');
    signal x_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
    signal y_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_x                      : std_logic_vector(11 downto 0):=(others=>'0');
    signal s_y                      : std_logic_vector(11 downto 0):=(others=>'0');
begin

    s_axis_tready       <= m_axis_tready;
    m_axis_tuser        <= s_axis_tuser;
    m_axis_tlast        <= s_axis_tlast;
    m_axis_tvalid       <= s_axis_tvalid;
    m_axis_tdata        <= s_axis_tdata;

    xCntr   <= x_cntr;
    yCntr   <= y_cntr;

    process(clk) 
    begin
    if (rising_edge(clk)) then
        m_axis_croped_tdata        <= (others=>'0');
        m_axis_croped_tvalid       <= '0';
        m_axis_croped_tuser        <= '0';
        m_axis_croped_tlast        <= '0';
        if (s_axis_tvalid = '1') then
            if (m_axis_tready = '1') then

                if (s_axis_tlast = '1') then
                    x_cntr          <= (others=>'0');
                    y_cntr          <= y_cntr + '1';
                else
                    x_cntr          <= x_cntr + '1';
                end if;

                if (s_axis_tuser = '1') then
                    x_cntr          <= (others=>'0');
                    y_cntr          <= (others=>'0');
                    s_x             <= x;
                    s_y             <= y;
                    s_width         <= width;
                    s_height        <= height;
                end if;

                if (x_cntr >= s_x) then
                    if (x_cntr < (s_x + s_width)) then
                        if (y_cntr >= s_y) then
                            if (y_cntr < (s_y + s_height)) then
                                m_axis_croped_tdata        <= s_axis_tdata;
                                m_axis_croped_tvalid       <= '1';
                            end if;
                        end if;
                    end if;
                end if;

                if (x_cntr = s_x) then
                    if (y_cntr = s_y) then
                        m_axis_croped_tuser         <= '1';
                    end if;
                end if;

                if (x_cntr = (s_x + s_width - 1)) then
                    m_axis_croped_tlast             <= '1';
                end if;

            end if;
        end if;

    end if;
    end process;


end arch;
