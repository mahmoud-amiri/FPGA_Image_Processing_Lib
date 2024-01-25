

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity camera_status_check is
    Port ( 
            ref_clk                  : in STD_LOGIC;
            camera_clk               : in std_logic;
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
            width                    : out std_logic_vector(11 downto 0);
            height                   : out std_logic_vector(11 downto 0);
            camera_clk_lock          : out std_logic
            );
end camera_status_check;

architecture arch of camera_status_check is
signal vid_width                : std_logic_vector(11 downto 0):=(others=>'0');
signal vid_height               : std_logic_vector(11 downto 0):=(others=>'0');
signal x_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
signal y_cntr                   : std_logic_vector(11 downto 0):=(others=>'0');
signal camera_clk_cntr          : std_logic_vector(31 downto 0);
signal camera_clk_cntr_r        : std_logic_vector(31 downto 0);
signal camera_clk_toggle        : std_logic;
signal camera_clk_toggle_r      : std_logic;
signal camera_clk_toggle_r2     : std_logic;
signal camera_clk_toggle_r3     : std_logic;
signal timer                    : std_logic_vector(11 downto 0);
begin

s_axis_tready       <= m_axis_tready;
m_axis_tuser        <= s_axis_tuser;
m_axis_tlast        <= s_axis_tlast;
m_axis_tvalid       <= s_axis_tvalid;
m_axis_tdata        <= s_axis_tdata;
width               <= vid_width;
height              <= vid_height;

process(camera_clk) 
begin
if (rising_edge(camera_clk)) then
    camera_clk_toggle   <= not camera_clk_toggle;
end if;
end process;

process(ref_clk) 
begin
if (rising_edge(ref_clk)) then

    camera_clk_toggle_r         <= camera_clk_toggle;
    camera_clk_toggle_r2        <= camera_clk_toggle_r;
    camera_clk_toggle_r3        <= camera_clk_toggle_r2;

    if (camera_clk_toggle_r2 = '0' and camera_clk_toggle_r3 = '1') then
        camera_clk_cntr         <= camera_clk_cntr + '1';
    end if;

    if (timer < X"0FF") then
        timer   <= timer + '1';
    else
        camera_clk_cntr_r   <= camera_clk_cntr;
        if (camera_clk_cntr /= camera_clk_cntr_r) then
            camera_clk_lock <= '1';
        else
            camera_clk_lock <= '0';
            x_cntr          <= (others=>'0');
            vid_width       <= (others=>'0');
            y_cntr          <= (others=>'0');
            vid_height      <= (others=>'0');
        end if;
        timer <= X"000";
    end if;

    if (s_axis_tvalid = '1') then
        if (m_axis_tready = '1') then

            if (s_axis_tlast = '1') then
                x_cntr          <= (others=>'0');
                vid_width       <= x_cntr + '1';
                y_cntr          <= y_cntr + '1';
            else
                x_cntr          <= x_cntr + '1';
            end if;

            if (s_axis_tuser = '1') then
                x_cntr          <= (others=>'0');
                vid_width       <= x_cntr + '1';
                y_cntr          <= (others=>'0');
                vid_height      <= y_cntr;
            end if;

        end if;
    end if;
end if;
end process;


end arch;
